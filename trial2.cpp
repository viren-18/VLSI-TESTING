#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>
#include <bits/stdc++.h>
#include <algorithm>
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
    vector<Gate> gates;
};

struct Node // to store the node (primary, gate)
{
    string name;
    string type;
    Node *next = NULL;
};

Module parseVerilog(const string &filename) // function to fetch Verilog file and return the Module
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
    for (auto it : module.gates)
    {
        gate_mp[it.g_name] = ind;
        ind++;
    }

    for (auto it : module.gates)
    {
        for (auto it2 : it.inputs)
        {
            mp[it2].push_back(it.g_name);
        }
        // cout << endl;
    }
    int name = 1;
    for (auto it : mp)
    {
        if (it.second.size() >= 2)
        {
            int ind = 0;
            for (auto it2 : it.second)
            {
                // cout << module.gates[gate_mp[it2]].g_name << "  ";
                Gate prev = module.gates[gate_mp[it2]];
                vector<string> prev_inp = prev.inputs;
                // vector<string> prev_op = prev.outputs;

                string ch = it.first + (char)((int)'a' + ind);
                for (int i = 0; i < prev_inp.size(); i++)
                {
                    if (prev_inp[i] == it.first)
                    {

                        module.gates[gate_mp[it2]].inputs[i] = ch;
                        module.outputs.push_back(ch);
                        break;
                        // cout << module.gates[gate_mp[it2]].inputs[i] << endl;
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
                for (auto it : module.gates)
                {
                    gate_mp[it.g_name] = temp;
                    temp++;
                }

                ind++;
            }
            // cout << endl;
        }
    }
}

void connectNodes(vector<Node *> &nodes, Module &module) // to make connections between all nodes
{
    unordered_map<string, int> mp;
    unordered_map<string, int> gate_mp;
    int ind = 0;
    for (auto it : module.inputs)
    {
        Node *ne = new Node;
        ne->name = it;
        ne->type = "INPUT";
        ne->next = NULL;
        nodes.push_back(ne);
        mp[it] = ind++;
        // cout << it << " " << mp[it] << " " << ind << endl;
    }
    // cout << endl;
    for (auto it : module.outputs)
    {
        Node *ne = new Node;
        ne->name = it;
        ne->next = NULL;
        nodes.push_back(ne);
        mp[it] = ind++;
        // cout << it << " " << mp[it] << " " << ind << endl;
    }
    branching(module);
    // for (auto it : module.gates)
    // {
    //     string type_g = it.type;
    //     // cout << type_g << endl;
    //     vector<string> ip = it.inputs;
    //     // for(auto it: ip)
    //     // cout << it << " ";
    //     // cout << endl;
    //     string op = it.outputs[0];
    //     for (auto it1 : ip)
    //     {
    //         Node *node = nodes[mp[it1]];
    //         Node *ne = new Node();
    //         ne->name = op;
    //         ne->type = type_g;
    //         nodes[mp[op]]->type = type_g;
    //         ne->next = NULL;
    //         while (node->next != NULL)
    //             node = node->next;
    //         node->next = ne;
    //     }
    // }

    // for (auto it : nodes)
    // {
    //     cout << it->name << " ";
    // }
    // cout << endl;
}


void displaycircuit(vector<Node *> &nodes) // to display the circuit
{

    for (auto it : nodes)
    {
        Node *node = it;
        while (node)
        {
            cout << node->type << " ";
            cout << node->name << " -> ";
            node = node->next;
        }
        cout << "NULL" << endl;
    }
}

// fuctions to compute the values of logic gate
///--------------------------------------------------------------/

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
//--------------------------------------------------------------/

void compute(unordered_map<string, int> &mp, vector<Gate> &ge) // will compute the outputs of the circuit
{
    for (auto it : ge)
    {
        cout << it.g_name << endl;
        vector<string> inp = it.inputs;
        for (auto it2 : inp)
            cout << it2 << " ";
        cout << endl;
        string typ = it.type;
        string st = it.outputs[0];

        if (typ == "or")
        {
            bool ans = computeORGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "nor")
        {
            bool ans = computeORGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "and")
        {
            bool ans = computeANDGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "nand")
        {
            bool ans = computeANDGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "xor")
        {
            bool ans = computeXORGate(inp, mp);
            mp[st] = ans;
        }
        else if (typ == "xnor")
        {
            bool ans = computeXORGate(inp, mp);
            mp[st] = computeNOTGate(ans);
        }
        else if (typ == "not")
            mp[st] = computeNOTGate(mp[inp[0]]);

        else if (typ == "buf")
            mp[st] = computebufGate(mp[inp[0]]);
        else
            mp[st] = mp[inp[0]];
    }
}

int max1(int a,int b){
    if(a>b)
    return a;
    else
    return b;
}

void logiclevel(vector<Gate> &ge, vector<string> inputs){

    map<string,int> log;

    // for(int i=0; i<ge.size();i++)
    // cout<<ge[i].type<<" "<<ge[i].g_name<<" ";

    // cout<<endl;

    for(auto it:inputs){
    log[it]=0;
    }

    cout<<endl;

    // for(int k=0; k<ge.size();k++){
    // cout<<ge[k].g_name<<" "<<ge[k].type<<" ";
    //     for(int j=0;j<ge[k].inputs.size();j++){
    //         cout<<ge[k].inputs[j]<<" ";
    //     }

    //     cout<<ge[k].outputs[0];
    //     cout<<endl;
    // }

    for(int k=0;k<ge.size();k++){

        if(ge[k].type=="dummy")
        {   
            log[ge[k].g_name]=log[ge[k].inputs[0]];
            log[ge[k].outputs[0]]=log[ge[k].inputs[0]];
            
        }   

        else{
            int maxof=0;
            for(int l=0;l<ge[k].inputs.size();l++){
                maxof=max1(log[ge[k].inputs[l]],maxof);
            }
            log[ge[k].g_name]=maxof+1;
            log[ge[k].outputs[0]]=maxof+1;

             cout<<ge[k].g_name<<" "<<log[ge[k].g_name];
            cout<<endl;

        }
    }

}



void SerialFaultSimulation(string fault_name, int fault_val, Module File, unordered_map<string, int> &mp)
{
    cout << fault_name << " " << fault_val << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
    mp[fault_name] = fault_val;
    compute(mp, File.gates);
    for (auto j : mp)
    {
        cout << j.first << " = " << j.second << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------------------" << endl;
}

int main()
{
    string file_name;
    cout << "Enter the file name you want to make circuit: ";
    cin >> file_name;

    Module module = parseVerilog(file_name); // fatching the verilog file
    vector<Node *> nodes;
    connectNodes(nodes, module);
    unordered_map<string, int> mp;

    cout << endl;
    cout << "-------------Circuit Representation-------------" << endl;
    // displaycircuit(nodes);
    // cout << endl;

    // for (auto it : module.gates)
    // {
    //     cout << it.g_name << endl;
    //     for (auto it2 : it.inputs)
    //         cout << it2 << " ";
    //     cout << endl;
    // }

    cout << "----------------Input Section------------------" << endl;
    for (auto it : module.inputs)
    {
        cout << "Enter input for " << it << " :";
        int num;
        cin >> num;
        mp[it] = num;
    }
    // for (auto it : module.inputs)
    // {
    //     cout << it << " " << mp[it] << endl;
    // }
    // for (auto it : module.outputs)
    // {
    //     cout << it << " " << mp[it] << endl;
    // }
    for(auto it : module.gates)
    {
        cout << it.g_name << endl;
        for(auto it2: it.inputs)
            cout << it2 << " ";
        cout << endl;

        for(auto it2: it.outputs)
            cout << it2 << " ";
        cout << endl;
    }

    cout << "----------------Compute Section------------------" << endl;
    compute(mp, module.gates);

    cout << "Outputs: ";
    for (auto it : mp)
        cout << it.first << " : " << it.second << ", ";
    cout << endl;
    cout << endl;
    cout << "----------- (: Thank YOU :) ----------------" << endl;
    cout << endl;

    logiclevel(module.gates, module.inputs);

    return 0;
}