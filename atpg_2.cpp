#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

struct Gate {
    string type;
    string g_name;
    vector<string> inputs;
    string output;
};

struct Module {
    vector<string> inputs;
    vector<string> outputs;
    vector<Gate> gates;
};

struct Node {
    string name;
    string type;
    Node *next = NULL;
};

struct Fault {
    string node;
    string type;
    int value;
};

Module parseVerilog(const string &filename) {
    ifstream file(filename);
    string line;
    regex inputRegex(R"(input\s+([a-zA-Z0-9_,\s]+);)");
    regex wireRegex(R"(wire\s+([a-zA-Z0-9_,\s]+);)");
    regex outputRegex(R"(output\s+([a-zA-Z0-9_,\s]+);)");
    regex gateRegex(R"((nand|and|or|xor|xnor|nor|not|buf)\s+([a-zA-Z0-9_]+)\(([^)]+)\);)");

    Module module;

    while (getline(file, line)) {
        smatch match;

        if (regex_search(line, match, inputRegex)) {
            string inputsStr = match[1].str();
            stringstream inputsStream(inputsStr);
            string input;
            while (getline(inputsStream, input, ',')) {
                module.inputs.push_back(input);
            }
        } else if (regex_search(line, match, wireRegex)) {
            string wiresStr = match[1].str();
            stringstream wiresStream(wiresStr);
            string wire;
            while (getline(wiresStream, wire, ',')) {
                module.outputs.push_back(wire);
            }
        } else if (regex_search(line, match, outputRegex)) {
            string outputsStr = match[1].str();
            stringstream outputsStream(outputsStr);
            string output;
            while (getline(outputsStream, output, ',')) {
                module.outputs.push_back(output);
            }
        } else if (regex_search(line, match, gateRegex)) {
            Gate gate;
            gate.type = match[1].str();
            gate.g_name = match[2].str();
            string portsStr = match[3].str();
            stringstream portsStream(portsStr);
            string port;
            while (getline(portsStream, port, ',')) {
                if (gate.inputs.empty()) {
                    gate.output = port;
                } else {
                    gate.inputs.push_back(port);
                }
            }
            module.gates.push_back(gate);
        }
    }

    return module;
}

void createFaultList(Module &module, set<Fault> &faultList) {
    for (const auto &input : module.inputs) {
        faultList.insert({input, "SA0", 0});
        faultList.insert({input, "SA1", 1});
    }

    for (const auto &gate : module.gates) {
        faultList.insert({gate.output, "SA0", 0});
        faultList.insert({gate.output, "SA1", 1});
        for (const auto &input : gate.inputs) {
            faultList.insert({input, "SA0", 0});
            faultList.insert({input, "SA1", 1});
        }
    }
}

bool evaluateGate(const Gate &gate, const unordered_map<string, int> &values) {
    if (gate.type == "and") {
        for (const auto &input : gate.inputs) {
            if (values.at(input) == 0) return 0;
        }
        return 1;
    } else if (gate.type == "nand") {
        for (const auto &input : gate.inputs) {
            if (values.at(input) == 0) return 1;
        }
        return 0;
    } else if (gate.type == "or") {
        for (const auto &input : gate.inputs) {
            if (values.at(input) == 1) return 1;
        }
        return 0;
    } else if (gate.type == "nor") {
        for (const auto &input : gate.inputs) {
            if (values.at(input) == 1) return 0;
        }
        return 1;
    } else if (gate.type == "xor") {
        int result = 0;
        for (const auto &input : gate.inputs) {
            result ^= values.at(input);
        }
        return result;
    } else if (gate.type == "xnor") {
        int result = 0;
        for (const auto &input : gate.inputs) {
            result ^= values.at(input);
        }
        return !result;
    } else if (gate.type == "not") {
        return !values.at(gate.inputs[0]);
    } else if (gate.type == "buf") {
        return values.at(gate.inputs[0]);
    }
    return 0;
}

bool propagateFault(Module &module, unordered_map<string, int> &values, const Fault &fault) {
    values[fault.node] = fault.value;
    bool faultEffect = false;
    for (const auto &gate : module.gates) {
        if (gate.inputs.empty()) continue;
        bool gateOutput = evaluateGate(gate, values);
        if (gateOutput != values[gate.output]) {
            values[gate.output] = gateOutput;
            faultEffect = true;
        }
    }
    return faultEffect;
}

vector<string> generateTestVector(Module &module, const Fault &fault) {
    queue<unordered_map<string, int>> bfsQueue;
    bfsQueue.push({});

    while (!bfsQueue.empty()) {
        auto values = bfsQueue.front();
        bfsQueue.pop();

        for (const auto &input : module.inputs) {
            if (values.find(input) == values.end()) {
                for (int val = 0; val <= 1; ++val) {
                    auto newValues = values;
                    newValues[input] = val;
                    bfsQueue.push(newValues);
                }
                break;
            }
        }

        if (values.size() == module.inputs.size()) {
            if (propagateFault(module, values, fault)) {
                vector<string> testVector;
                for (const auto &input : module.inputs) {
                    testVector.push_back(to
                    _string(values[input]));
                }
                return testVector;
            }
        }
    }
    return ;
}

int main() {
    string filename = "c17.v";
    Module module = parseVerilog(filename);

    set<Fault> faultList;
    createFaultList(module, faultList);

    for (const auto &fault : faultList) {
        vector<string> testVector = generateTestVector(module, fault);
        if (!testVector.empty()) {
            cout << "Test vector for fault " << fault.node << " " << fault.type << ": ";
            for (const auto &bit : testVector) {
                cout << bit;
            }
            cout << endl;
        } else {
            cout << "No test vector found for fault " << fault.node << " " << fault.type << endl;
        }
    }

    return 0;
}
