#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <bits/stdc++.h>
using namespace std;

struct Gate // the structure to store the data of gate
{
    string type;
    string g_name;
    vector<string> inputs;
    vector<string> outputs;
};

struct Module // to store the whole circuit's basic information
{
    vector<string> inputs;
    vector<string> outputs; 
    vector<string> last_output;
    vector<Gate> gates;
};

struct Node // to store the node (primary, gate)
{
    string name;
    string type;
    Node *next = NULL;
};

Module parseVerilog(const string &filename) // function to fatch Verilog file and return the Module
{
    ifstream file(filename);
    string line;
    regex inputRegex(R"(input\s+([a-zA-Z0-9_,\s]+);)");
    regex wireRegex(R"(wire\s+([a-zA-Z0-9_,\s]+);)");
    regex outputRegex(R"(output\s+([a-zA-Z0-9_,\s]+);)");
    regex nandRegex(R"(nand\s+([()a-zA-Z0-9_,\s]+);)");
    regex andRegex(R"(and\s+([()a-zA-Z0-9_,\s]+);)");
    regex orRegex(R"(or\s+([()a-zA-Z0-9_,\s]+);)");
    regex xorRegex(R"(xor\s+([()a-zA-Z0-9_,\s]+);)");
    regex xnorRegex(R"(xnor\s+([()a-zA-Z0-9_,\s]+);)");
    regex norRegex(R"(nor\s+([()a-zA-Z0-9_,\s]+);)");
    regex notRegex(R"(not\s+([()a-zA-Z0-9_,\s]+);)");
    regex bufRegex(R"(buf\s+([()a-zA-Z0-9_,\s]+);)");

    Module module;

    while (getline(file, line))
    {
        smatch match;

        if (regex_search(line, match, inputRegex))
        {
            string inputsStr = match[1].str();

            stringstream inputsStream(inputsStr);
            string input;
            while (getline(inputsStream, input, ','))
            {
                module.inputs.push_back(input);
            }
        }
        else if (regex_search(line, match, wireRegex))
        {
            string inputsStr = match[1].str();
            stringstream inputsStream(inputsStr);
            string input;
            while (getline(inputsStream, input, ','))
            {
                module.outputs.push_back(input);
            }
        }
        else if (regex_search(line, match, outputRegex))
        {
            string outputsStr = match[1].str();
            stringstream outputsStream(outputsStr);
            string output;
            while (getline(outputsStream, output, ','))
            {
                module.outputs.push_back(output);
                module.last_output.push_back(output);
            }
        }
        else if (regex_search(line, match, nandRegex))
        {
            Gate gate;
            gate.type = "nand";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, andRegex))
        {
            Gate gate;
            gate.type = "and";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, xnorRegex))
        {
            Gate gate;
            gate.type = "xnor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, xorRegex))
        {
            Gate gate;
            gate.type = "xor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, norRegex))
        {
            Gate gate;
            gate.type = "nor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, orRegex))
        {
            Gate gate;
            gate.type = "or";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, notRegex))
        {
            Gate gate;
            gate.type = "not";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, bufRegex))
        {
            Gate gate;
            gate.type = "buf";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
    }

    return module;
}

void branching(Module &module)
{
    map<string, vector<string>> mp;
    map<string, int> gate_mp;

    int ind = 0;
    // Mapping created between gate name and gate index
    for (auto it : module.gates)
    {
        gate_mp[it.g_name] = ind;
        ind++;
    }

    // Created mapping between cbranh and it's corresponding gates
    for (auto it : module.gates)
    {
        for (auto it2 : it.inputs)
        {
            mp[it2].push_back(it.g_name);
        }
    }

    int name = 1;
    for (auto it : mp)
    {
        // Checking if a wire has a branch or not.
        if (it.second.size() >= 2)
        {
            int ind = 0;
            for (auto it2 : it.second)
            {
                Gate prev = module.gates[gate_mp[it2]];
                vector<string> prev_inp = prev.inputs;

                string ch = it.first + (char)((int)'a' + ind);
                for (int i = 0; i < prev_inp.size(); i++)
                {
                    if (prev_inp[i] == it.first)
                    {
                        module.gates[gate_mp[it2]].inputs[i] = ch;
                        module.outputs.push_back(ch);
                        break;
                    }
                }

                // Create a dummy gate to be inserted between gates
                Gate g;
                g.g_name = "branch" + to_string(name++);
                g.type = "dummy";
                g.inputs.push_back(it.first);
                g.outputs.push_back(ch);

                auto pos = module.gates.begin() + gate_mp[it2];
                module.gates.insert(pos, g);

                gate_mp.clear();
                int temp = 0;
                // Reassigning all the gate mappings
                for (auto it : module.gates)
                {
                    gate_mp[it.g_name] = temp;
                    temp++;
                }
                ind++;
            }
        }
    }
}

void connectNodes(Module &module) // To make connections between all nodes
{
    unordered_map<string, int> mp;
    unordered_map<string, int> gate_mp;
    int ind = 0;
    for (auto it : module.inputs)
    {
        mp[it] = ind++;
    }
    for (auto it : module.outputs)
    {
        mp[it] = ind++;
    }
    branching(module);
}

// Fuctions to compute the values of logic gate
bool computeXORGate(const vector<string> &inputs, unordered_map<string, int> &mp)
{
    bool output = false;
    for (const auto &input : inputs)
    {
        output = output ^ mp[input];
    }
    return output;
}
bool computeANDGate(const vector<string> &inputs, unordered_map<string, int> &mp)
{
    bool output = true;
    for (const auto &input : inputs)
    {
        output = output && mp[input];
    }
    return output;
}
bool computeORGate(const vector<string> &inputs, unordered_map<string, int> &mp)
{
    bool output = false;
    for (const auto &input : inputs)
    {
        output = output || mp[input];
    }
    return output;
}
bool computeNOTGate(bool inputs)
{
    return !inputs;
}
bool computebufGate(bool inputs)
{
    return inputs;
}

void compute(unordered_map<string, int> &mp, vector<Gate> &ge) // will compute the outputs of the circuit
{
    for (auto it : ge)
    {
        vector<string> inp = it.inputs;
        string typ = it.type;
        string st = it.outputs[0];

        if (typ == "or" && mp[st] == -1)
        {

            bool ans = computeORGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "nor" && mp[st] == -1)
        {
            bool ans = computeORGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "and" && mp[st] == -1)
        {
            bool ans = computeANDGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "nand" && mp[st] == -1)
        {
            bool ans = computeANDGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "xor" && mp[st] == -1)
        {
            bool ans = computeXORGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "xnor" && mp[st] == -1)
        {
            bool ans = computeXORGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "not" && mp[st] == -1)
            mp[st] = computeNOTGate(mp[inp[0]]);

        else if (typ == "buf" && mp[st] == -1)
            mp[st] = computebufGate(mp[inp[0]]);
        else
        {
            if (mp[st] == -1)
            {
                mp[st] = mp[inp[0]];
            }
        }
    }
}

void createFaultList(Module &module, set<pair<string, string>> &faultList)
{
    int totalFaults = module.inputs.size() + module.outputs.size();
    // vector<pair<string, string>> faultList;
    // vector<string> temp;

    // Add stuck-at-0 and stuck-at-1 faults for all gate inputs
    int print = 1;
    cout << "----------------Fault List(" << totalFaults * 2 << ")------------------" << endl;
    for (auto it : module.inputs)
    {
        cout << it << " - "
             << "SA0"
             << "\t";
        cout << it << " - "
             << "SA1"
             << "\t";

        if (print % 2 == 0)
            cout << endl;
        // faultList.push_back({it, "SA0" });
        // faultList.push_back({it, "SA0" });
        print++;
    }

    for (auto &gate : module.gates)
    {
        for (auto &output : gate.outputs)
        {

            cout << output << " - "
                 << "SA0"
                 << "\t";
            cout << output << " - "
                 << "SA1"
                 << "\t";

            if (print % 2 == 0)
                cout << endl;
            print++;
            // faultList.push_back({output, "SA0"});
            // faultList.push_back({output, "SA1"});

            if (gate.type == "or")
            {
                for (auto &input : gate.inputs)
                {
                    faultList.insert({input, "SA0"});
                }
            }
            else if (gate.type == "nor")
            {
                for (auto &input : gate.inputs)
                {
                    faultList.insert({input, "SA0"});
                }
            }
            else if (gate.type == "and")
            {
                for (auto &input : gate.inputs)
                {
                    faultList.insert({input, "SA1"});
                }
            }
            else if (gate.type == "nand")
            {
                for (auto &input : gate.inputs)
                {
                    faultList.insert({input, "SA1"});
                }
            }
            else if (gate.type == "dummy" || gate.type == "buf" || gate.type == "xor" || gate.type == "xnor")
            {
                for (auto &input : gate.inputs)
                {

                    faultList.insert({input, "SA0"});
                    faultList.insert({input, "SA1"});
                }
            }
        }
    }
    for (auto it : module.last_output)
    {
        faultList.insert({it, "SA0"});
        faultList.insert({it, "SA1"});
    }

    // faultList.erase(unique(faultList.begin(),faultList.end()),faultList.end());
}

void logiclevel(vector<Gate> &ge, vector<string> inputs)
{

    map<string, int> log;



    for (auto it : inputs)
    {
        log[it] = 0;
    }



    for (int k = 0; k < ge.size(); k++)
    {

        if (ge[k].type == "dummy")
        {
            log[ge[k].g_name] = log[ge[k].inputs[0]];
            log[ge[k].outputs[0]] = log[ge[k].inputs[0]];
        }

        else
        {
            int maxof = 0;
            for (int l = 0; l < ge[k].inputs.size(); l++)
            {
                maxof = max(log[ge[k].inputs[l]], maxof);
            }
            log[ge[k].g_name] = maxof + 1;
            log[ge[k].outputs[0]] = maxof + 1;

            cout << ge[k].g_name << " " << log[ge[k].g_name];
            cout << endl;
        }
    }
}

void SerialFaultSimulation(Module File, set<pair<string, string>> faultList, vector<string> &testvector)
{
    int totalCollapsedFault = faultList.size();
    set<pair<string, string>> detectedFaults, undetectedFaults;
    for (auto it : testvector)
    {
        undetectedFaults.clear();
        detectedFaults.clear();

        unordered_map<string, int> prefix, faulty, true_val;
        for (int i = 0; i < File.inputs.size(); i++)
        {
            int num = (int)(it[i] - '0');
            prefix[File.inputs[i]] = num;
        }
        for (auto it : File.outputs)
        {
            prefix[it] = -1;
        }
        true_val = prefix;

        compute(true_val, File.gates);

        // cout << "True Value Simulation: " << endl;
        // for(auto it6 : File.last_output)
        //         cout << it6 << " " << true_val[it6] << endl;
        // for (int v = 0; v < File.outputs.size(); v++)
        // {
        //     if (File.gates[v].type != "dummy")
        //         cout << File.gates[v].g_name << "("
        //              << File.gates[v].outputs[0] << ") = "
        //              << true_val[File.gates[v].outputs[0]] << endl;
        // }
        // cout << endl;
        // cout << "-------------------Fault Simulation---------------" << endl;

        // cout << "Detected" << endl;
        for (auto it3 : faultList)
        {

            string fault_name = it3.first;
            int fault_val = (int)(it3.second[it3.second.size() - 1]) - '0';
            // cout << fault_name << " SA" << fault_val << endl;
            // cout << "-----------------------------------------------" << endl;

            faulty = prefix;
            faulty[fault_name] = fault_val;

            compute(faulty, File.gates);

            // for(auto it6 : File.last_output)
            //     cout << it6 << " " << faulty[it6] << endl;

            // for (int v = 0; v < File.gates.size(); v++)
            // {
            //     if (File.gates[v].type != "dummy")
            //         cout << File.gates[v].g_name << "("
            //              << File.gates[v].outputs[0] << ") = "
            //              << true_val[File.gates[v].outputs[0]] << endl;
            // }

            bool check = false;
            for (auto it4 : File.last_output)
            {
                // cout << true_val[it4] << " " << faulty[it4];
                if (true_val[it4] != faulty[it4])
                {
                    // cout << it3.first << " " << it3.second << endl;
                    detectedFaults.insert(it3);
                    check = true;
                    break;
                }
            }
            if (!check)
            {
                undetectedFaults.insert(it3);
                // cout << "Undetected : ";
                // cout << it3.first << " " << it3.second << endl;
            }
            // cout << "-------------------------------------------------" << endl;
        }

        if (detectedFaults.size() != 0)
        {
            cout << "Using Test Vector: " << it << endl;
            cout << "Detected Faults(" << detectedFaults.size() << ")" << endl;
            for (auto it9 : detectedFaults)
                cout << it9.first << " " << it9.second << endl;
            cout << "----------------------------------" << endl;
        }
        if (detectedFaults.size() == totalCollapsedFault)
            return;
        faultList.clear();
        faultList = undetectedFaults;
    }
    if (undetectedFaults.size() == 0)
        cout << "There are no undetected faults" << endl;
    else
    {
        cout << "Undetected(" << undetectedFaults.size() << ")" << endl;
        for (auto it9 : undetectedFaults)
            cout << it9.first << " " << it9.second << endl;
    }
}

// Function to print the output
void storeTestVector(vector<int> &arr, int n, vector<string> &testVectors)
{
    string temp = "";
    for (int i = 0; i < n; i++)
    {
        temp += (to_string(arr[i]));
    }
    testVectors.push_back(temp);
}

// Function to generate all binary strings
void generateAllTestVector(int n, vector<int> &arr, int i, vector<string> &testVectors)
{
    if (i == n)
    {
        storeTestVector(arr, n, testVectors);
        return;
    }
    arr[i] = 0;
    generateAllTestVector(n, arr, i + 1, testVectors);

    arr[i] = 1;
    generateAllTestVector(n, arr, i + 1, testVectors);
}

int main()
{
    string file_name;
    cout << "Enter the file name you want to make circuit: ";
    cin >> file_name;

    cout << "----------------SERIAL FAULT SIMULATION------------------" << endl;
    Module module = parseVerilog(file_name); // fatching the verilog file
    // vector<Node *> nodes;
    connectNodes(module);
    unordered_map<string, int> mp, mp2;

    set<pair<string, string>> faultList;
    createFaultList(module, faultList);
    // faultList.erase(unique(faultList.begin(),faultList.end()),faultList.end());

    cout << endl
         << "----------------Collapsed Fault List(" << faultList.size() << ")------------------" << endl;
    int print = 1;
    for (auto &fault : faultList)
    {
        cout << fault.first << " - " << fault.second << "\t";
        if (print % 4 == 0)
            cout << endl;
        print++;
    }

    cout << endl
         << "----------------Logic Levalization------------------" << endl;
    logiclevel(module.gates, module.inputs);

    cout << "----------------Serial Fault Simulation------------------" << endl;
    int len = module.inputs.size();
    vector<int> arr(len);
    vector<string> testVectors;
    generateAllTestVector(len, arr, 0, testVectors);

    // for (auto it : testVectors)
    //     cout << it << " ";
    // cout << endl;

    // testVectors.push_back("11111");
    // testVectors.push_back("00001");
    // faultList.insert({"N1", "1"});
    // faultList.insert({"N10", "1"});
    // faultList.insert({"N11b", "1"});
    // faultList.insert({"N11", "1"});

    SerialFaultSimulation(module, faultList, testVectors);

    cout<< endl;
    cout << "----------------Parallel FAULT SIMULATION------------------" << endl;
    cout<<endl;
    cout << "----------------GENERATE PARALLEL TEST VECTORS------------------" << endl;

    
    
    vector<vector<string>> pindtv;
    vector<string> partv;
    int count=0;
    for(int k=0;k<testVectors.size();k++)
    {
        
        for (int i=0; i< testVectors[0].size();i++)
        {
            char a=testVectors[k][i];
            
            string s="";
            for(int j=0;j<faultList.size()+1;j++)
            {
                s+=a;
            }
            
            partv.push_back(s);
            count++;
        }

        
        if(count==testVectors[0].size()){
            pindtv.push_back(partv);
            partv={};
            count=0;
        }
    }


    for(auto it:pindtv){
        for(auto it2:it){
            cout<<it2<<endl;
        }
        cout<<endl;
    }
    cout << "----------------PARALLEL FAULT SIMULATIONS------------------" << endl;

    string str="";
    for(int j=0;j<faultList.size()+1;j++)
    {
        str+='0';
    }
        
    

    for (auto it : pindtv)
    {
        for(auto it2: it){

            unordered_map<string, int> prefix,true_val;
            for (int i = 0; i < module.inputs.size(); i++)
            {
                int num =  (int)(it2[i]);
                prefix[module.inputs[i]] = num;
            } 
            for (auto it : module.outputs)
            {
                prefix[it] = -1;
            }
            true_val = prefix;

            compute(true_val, module.gates);
            for(auto it: true_val){
                cout<<it.first<<"="<<it.second <<"\t";
            }
            cout<<endl;
            
        }
    }

    
    
    


    return 0;
}