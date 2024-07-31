#include <bits/stdc++.h>
using namespace std;

int No_Output = 0;
int No_input = 0;
vector<pair<vector<bool>, vector<pair<string, bool>>>> Detected_falut;
vector<string> types_wire = {"input", "wire", "output"};
vector<string> types_gate = {"nand", "and", "or", "xor", "buf", "not", "nor", "xnor", "dum"};
multimap<int, int> mpp;
set<pair<string, bool>> Collapse_fault;
vector<pair<string, bool>> vec_fault;
set<pair<string, bool>> Collapse_fault_List;
class Gate;
struct hash_pair
{

    template <class T1, class T2>

    size_t operator()(const pair<T1, T2> &p) const

    {

        auto hash1 = hash<T1>{}(p.first);

        auto hash2 = hash<T2>{}(p.second);

        if (hash1 != hash2)
        {

            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.

        return hash1;
    }
};
class Wire
{
public:
    string w_name;
    string w_type;
    vector<int> start;
    vector<int> end;
    vector<bool> value;
    int L;
    Wire()
    {
        L = -1;
    }
};

class Gate
{
public:
    string g_type;
    string g_name;
    vector<int> input_wires;
    vector<int> output_wires;
    int L;
    Gate()
    {
        L = -1;
    }
};

class Fault_gate_list
{
public:
    string g_name;
    vector<pair<pair<string, bool>, pair<string, bool>>> fault;
};

class Verilog_File
{
public:
    map<int, Gate> gate;
    map<int, Wire> wire;
};

Verilog_File File;
void Convert_string_into_word(string input, char del, vector<string> &words)
{
    stringstream ss(input);
    string word;

    while (getline(ss, word, del))
    {
        words.push_back(word);
    }
}

bool Convert_string_present(string input, char del, vector<string> types)
{
    stringstream ss(input);
    string word;

    while (getline(ss, word, del))
    {
        if (find(types.begin(), types.end(), word) != types.end())
            return 1;
    }
    return 0;
}

Verilog_File Convert_file(string file_name)
{
    ifstream file(file_name);
    string line;
    Verilog_File f;
    int wire_id = 0;
    int gate_id = 0;
    vector<string> words;

    while (getline(file, line, ';'))
    {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        Convert_string_into_word(line, ' ', words);
        if (words[0] == "//")
        {
            words.clear();
            continue;
        }
        words.clear();
        // cout<<line<<endl;
        // cout<<"33333333333333333333333333333333333"<<endl;
        if (Convert_string_present(line, ' ', types_wire) == 1)
        {
            line.erase(remove(line.begin() + 8, line.end(), ' '), line.end());
            Convert_string_into_word(line, ' ', words);
            // cout<<words[0]<<" "<<words[0].size()<<endl;
            // cout<<"3333   pandya jayesh gnahsyambhai"<<endl;
            if (words[0] == "input") //--------------------------input
            {

                // cout<<"1111111111111111111111111111111"<<endl;
                string input = words[1];

                words.clear();
                // cout<<"444  pandya jayesh gnahsyambhai"<<endl;
                Convert_string_into_word(input, ',', words);
                for (long long int i = 0; i < words.size(); i++)
                {
                    No_input++;
                    Wire w;
                    w.w_name = words[i];
                    w.w_type = types_wire[0];
                    w.L = 0;
                    w.start.push_back(0);
                    // w.w_id=++wire_id;
                    f.wire[++wire_id] = w;
                }
                // f.input.insert(f.input.end(), words.begin(), words.end());
            }
            else if (words[0] == "output")
            {
                // cout<<"222222222222222222222222222222222"<<endl;
                // cout<<"555   pandya jayesh gnahsyambhai"<<endl;
                string out = words[0];
                string output = words[1];
                words.clear();
                Convert_string_into_word(output, ',', words);
                if (out == "output") //-------------------------output
                {
                    No_Output = words.size();
                }
                for (long long int i = 0; i < words.size(); i++)
                {
                    Wire w;
                    w.w_name = words[i];
                    w.w_type = types_wire[2];
                    w.end.push_back(-1);
                    // w.w_id=++wire_id;
                    f.wire[++wire_id] = w;
                }
            }
            else
            {
                // cout<<"444444444444444444444444"<<endl;
                // cout<<"666   pandya jayesh gnahsyambhai"<<endl;
                string output = words[1];
                words.clear();
                Convert_string_into_word(output, ',', words);
                for (long long int i = 0; i < words.size(); i++)
                {
                    Wire w;
                    w.w_name = words[i];
                    w.w_type = types_wire[1];
                    // w.w_id=++wire_id;
                    f.wire[++wire_id] = w;
                }
            }
        }
        else if (Convert_string_present(line, ' ', types_gate) == 1)
        {
            Convert_string_into_word(line, '(', words);
            // cout<<line<<endl;
            // cout<<"33333333333333333333333333333333333"<<endl;
            //  cout<<words.size()<<endl;
            string temp = words[0];
            string temp1 = words[1];
            words.clear();
            temp1.erase(remove(temp1.begin(), temp1.end(), ' '), temp1.end());
            temp1.erase(remove(temp1.begin(), temp1.end(), ')'), temp1.end());

            Convert_string_into_word(temp, ' ', words);
            // cout<<"777   pandya jayesh gnahsyambhai"<<endl;
            Gate gate;

            gate.g_name = words[1];
            gate.g_type = words[0];
            // gate.g_id = ++gate_id;
            ++gate_id;
            words.clear();

            Convert_string_into_word(temp1, ',', words);

            for (long long int i = 0; i < words.size(); i++)
            {
                // Wire w;
                // w.w_name=words[i];
                // w.w_type=types_wire[0];
                // for(auto wire:f.wire){
                //     if(words[i]==wire.w_name){
                //         if(i==0){
                //             gate.output_wires.push_back(wire);
                //         }else{
                //             gate.input_wires.push_back(wire);
                //         }
                //     }
                // }
                for (long long int j = 0; j < f.wire.size(); j++)
                {
                    if (words[i] == f.wire[j + 1].w_name)
                    {
                        if (i == 0)
                        {
                            gate.output_wires.push_back(j + 1);
                            f.wire[j + 1].start.push_back(gate_id);
                        }
                        else
                        {
                            gate.input_wires.push_back(j + 1);
                            f.wire[j + 1].end.push_back(gate_id);
                        }
                    }
                }

                // if(f.wire.find(w)!=f.wire.end()){
                //     //gate.input_wires.push_back(w);
                // }else{
                //     w.w_type=types_wire[2];
                //     if(f.wire.find(w)!=f.wire.end()){
                //         //gate.input_wires.push_back(w);
                //     }else{
                //         w.w_type=types_wire[1];
                //         //gate.input_wires.push_back(w);
                //     }
                // }
                // if(i==0){
                //     gate.output_wires.push_back(w);
                // }else{
                //     gate.input_wires.push_back(w);
                // }
            }

            // gate.input_wires.insert(gate.input_wires.end(), words.begin() + 1, words.end());
            // gate.output_wires.push_back(words[0]);

            words.clear();
            // f.gate.insert(gate);
            f.gate[gate_id] = gate;
        }

        words.clear();
    }
    // cout<<"8888   pandya jayesh gnahsyambhai"<<endl;
    file.close();
    return f;
}

void Logic_levelization(int cond)
{
    long long int size = File.gate.size();
    for (long long int i = 0; i < size; i++)
    {
        long long int temp = File.gate[i + 1].input_wires.size();
        long long int level = 0;
        for (long long int j = 0; j < temp; j++)
        {
            int temp1 = File.wire[File.gate[i + 1].input_wires[j]].L;

            if (File.wire[File.gate[i + 1].input_wires[j]].end.size() > 1 && cond)
                temp1++;
            if (level < temp1)
            {
                level = temp1;
            }
        }
        File.gate[i + 1].L = level + 1;
        long long int temp2 = File.gate[i + 1].output_wires.size();
        for (long long int j = 0; j < temp2; j++)
        {
            File.wire[File.gate[i + 1].output_wires[j]].L = level + 1;
        }
    }
}
bool circuit_modification(Verilog_File &File)
{
    long long int num = 0;
    Logic_levelization(1);
    for (long long int i = 0; i < File.wire.size(); i++)
    {

        if (File.wire[i + 1].end.size() > 1)
        {
            num++;
            string temp = to_string(num);
            Gate d;
            d.g_type = types_gate[8];
            d.g_name = "DUMM" + temp;
            d.input_wires.push_back(i + 1);
            d.L = File.wire[i + 1].L + 1;
            for (long long int k = 0; k < File.wire[i + 1].end.size(); k++)
            {
                Wire w;
                w.w_type = types_wire[1];
                w.w_name = "Ex" + temp + to_string(k + 1);
                w.start.push_back(File.gate.size() + 1);
                w.end.push_back(File.wire[i + 1].end[k]);
                d.output_wires.push_back(File.wire.size() + 1);
                w.L = d.L;
                auto it = find(File.gate[File.wire[i + 1].end[k]].input_wires.begin(), File.gate[File.wire[i + 1].end[k]].input_wires.end(), i + 1);
                if (it != File.gate[File.wire[i + 1].end[k]].input_wires.end())
                    File.gate[File.wire[i + 1].end[k]].input_wires.erase(it);
                else
                    return false;
                File.gate[File.wire[i + 1].end[k]].input_wires.push_back(File.wire.size() + 1);
                File.wire[File.wire.size() + 1] = w;
            }
            File.wire[i + 1].end.clear();
            File.wire[i + 1].end.push_back(File.gate.size() + 1);
            File.gate[File.gate.size() + 1] = d;
        }
    }

    return true;
}

vector<bool> compute_and(long long int id)
{
    vector<bool> res;
    res.assign(Collapse_fault.size() + 1, true);

    long long int size = File.gate[id].input_wires.size();

    for (int i = 0; i < Collapse_fault.size() + 1; i++)
    {
        for (int j = 0; j < size; j++)
        {
            long long int temp = File.gate[id].input_wires[j];

            if (!File.wire[temp].value[i])
            {
                res[i] = false;
                // break;
            }
        }
    }

    return res;
}

vector<bool> compute_or(long long int id)
{
    vector<bool> res;
    res.assign(Collapse_fault.size() + 1, false);

    long long int size = File.gate[id].input_wires.size();

    for (int i = 0; i < Collapse_fault.size() + 1; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            long long int temp = File.gate[id].input_wires[j];

            if (File.wire[temp].value[i])
            {
                res[i] = true;
            }
        }
    }

    return res;
}

vector<bool> compute_xor(long long int id)
{
    vector<bool> res;
    res.assign(Collapse_fault.size() + 1, false);

    long long int size = File.gate[id].input_wires.size();

    for (int i = 0; i < Collapse_fault.size() + 1; i++)
    {
        for (auto j = 0; j < size; j++)
        {
            long long int temp = File.gate[id].input_wires[j];

            res[i] = File.wire[temp].value[i] ^ res[i];
        }
    }

    return res;
}

void compute_CUT()
{

    long long int size1 = mpp.size();
    for (auto i = mpp.begin(); i != mpp.end(); i++)
    {
        long long int id = i->second;

        if (File.gate[id].g_type == "nand")
        {
            // cout<<"************8"<<endl;
            vector<bool> temp = compute_and(id);
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            // cout<<File.gate[id].g_name;
            // cout<<"************8"<<temp<<endl;
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "nor")
        {
            vector<bool> temp = compute_or(id);
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "and")
        {
            vector<bool> temp = compute_and(id);

            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "or")
        {
            vector<bool> temp = compute_or(id);

            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "not")
        {
            int temp = File.gate[id].input_wires[0];
            vector<bool> t = File.wire[temp].value;
            for (int i = 0; i < t.size(); i++)
            {
                t[i] = !t[i];
            }
            int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(t.begin(), t.end());
        }
        else if (File.gate[id].g_type == "buf")
        {
            int temp = File.gate[id].input_wires[0];
            vector<bool> t = File.wire[temp].value;
            int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(t.begin(), t.end());
        }
        else if (File.gate[id].g_type == "xor")
        {
            vector<bool> temp = compute_xor(id);
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "xnor")
        {
            vector<bool> temp = compute_xor(id);
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "dum")
        {
            int temp = File.gate[id].input_wires[0];
            vector<bool> t = File.wire[temp].value;
            int size1 = File.gate[id].output_wires.size();
            for (long long int k = 0; k < size1; k++)
            {
                int temp1 = File.gate[id].output_wires[k];
                File.wire[temp1].value.assign(t.begin(), t.end());
            }
        }
    }
}

void parraller_fault_simulation()
{
    long long int size1 = mpp.size();
    for (auto i = mpp.begin(); i != mpp.end(); i++)
    {
        long long int id = i->second;

        if (File.gate[id].g_type == "nand")
        {
            // cout<<"hiiii"<<endl;
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;
                //  cout<<"hi"<<endl;
                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    // cout<<"hskkd"<<endl;
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos > Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }

            // cout<<"hiiii1"<<endl;
            vector<bool> temp = compute_and(id);
            // cout<<"hiiii2"<<endl;
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "nor")
        {
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;

                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos >= Collapse_fault.size() + 1)
                    {
                        break;
                    }
                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }
            vector<bool> temp = compute_or(id);
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "and")
        {
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;

                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos >= Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }
            vector<bool> temp = compute_and(id);

            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "or")
        {
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;

                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos >= Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }
            vector<bool> temp = compute_or(id);

            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "not")
        {

            int temp = File.gate[id].input_wires[0];
            bool val, val1;
            int pos = 0;
            for (auto k : Collapse_fault)
            {
                if (k.first == File.wire[File.gate[id].input_wires[0]].w_name)
                {
                    val = k.second;
                    break;
                }

                if (pos > Collapse_fault.size() + 1)
                {
                    break;
                }

                pos++;
            }

            if (pos < Collapse_fault.size() + 1)
            {
                File.wire[File.gate[id].input_wires[0]].value[pos] = val;
            }
            vector<bool> t = File.wire[temp].value;
            for (int i = 0; i < t.size(); i++)
            {
                t[i] = !t[i];
            }
            int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(t.begin(), t.end());
        }
        else if (File.gate[id].g_type == "buf")
        {
            int temp = File.gate[id].input_wires[0];
            bool val;
            int pos = 1;
            for (auto k : Collapse_fault)
            {
                if (k.first == File.wire[File.gate[id].input_wires[0]].w_name)
                {
                    val = k.second;
                    break;
                }

                if (pos > Collapse_fault.size() + 1)
                {
                    break;
                }

                pos++;
            }

            if (pos < Collapse_fault.size() + 1)
            {
                File.wire[File.gate[id].input_wires[0]].value[pos] = val;
            }
            vector<bool> t = File.wire[temp].value;
            int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(t.begin(), t.end());
        }
        else if (File.gate[id].g_type == "xor")
        {
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;

                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos > Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }
            vector<bool> temp = compute_xor(id);
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "xnor")
        {
            for (int j = 0; j < File.gate[id].input_wires.size(); j++)
            {
                // pair<string,int>f1;

                bool val, val1;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[File.gate[id].input_wires[j]].w_name)
                    {
                        val = k.second;
                        break;
                    }

                    if (pos > Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[File.gate[id].input_wires[j]].value[pos] = val;
                }
            }
            vector<bool> temp = compute_xor(id);
            for (int i = 0; i < temp.size(); i++)
            {
                temp[i] = !temp[i];
            }
            long long int temp1 = File.gate[id].output_wires[0];
            File.wire[temp1].value.assign(temp.begin(), temp.end());
        }
        else if (File.gate[id].g_type == "dum")
        {
            int temp = File.gate[id].input_wires[0];
            bool val, val1;
            int pos = 1;
            for (auto k : Collapse_fault)
            {
                if (k.first == File.wire[File.gate[id].input_wires[0]].w_name && k.second != File.wire[File.gate[id].input_wires[0]].value[0])
                {
                    val = k.second;
                    break;
                }

                if (pos > Collapse_fault.size() + 1)
                {
                    break;
                }

                pos++;
            }

            if (pos < Collapse_fault.size() + 1)
            {
                File.wire[File.gate[id].input_wires[0]].value[pos] = val;
            }

            vector<bool> t = File.wire[temp].value;
            int size1 = File.gate[id].output_wires.size();
            for (long long int k = 0; k < size1; k++)
            {
                int temp1 = File.gate[id].output_wires[k];
                File.wire[temp1].value.assign(t.begin(), t.end());
            }
        }
    }
}

void Collapse_fault_list(set<pair<string, bool>> &fault_list)
{
    long long int size1 = mpp.size();
    for (auto i = mpp.begin(); i != mpp.end(); i++)
    {

        long long int id = i->second;
        pair<string, int> f1;
        if (File.gate[id].g_type == "and")
        {
            for (auto j : File.gate[id].input_wires)
            {
                f1.first = File.wire[j].w_name;
                f1.second = 1;

                fault_list.insert(f1);
            }
        }
        else if (File.gate[id].g_type == "or")
        {
            for (auto j : File.gate[id].input_wires)
            {
                f1.first = File.wire[j].w_name;
                f1.second = 0;

                fault_list.insert(f1);
            }
        }
        else if (File.gate[id].g_type == "nand")
        {
            for (auto j : File.gate[id].input_wires)
            {
                f1.first = File.wire[j].w_name;
                f1.second = 1;

                fault_list.insert(f1);
            }
        }
        else if (File.gate[id].g_type == "nor")
        {
            for (auto j : File.gate[id].input_wires)
            {
                f1.first = File.wire[j].w_name;
                f1.second = 0;

                fault_list.insert(f1);
            }
        }
        else if (File.gate[id].g_type == "dum")
        {
            f1.first = File.wire[File.gate[id].input_wires[0]].w_name;
            f1.second = 0;

            fault_list.insert(f1);

            f1.first = File.wire[File.gate[id].input_wires[0]].w_name;
            f1.second = 1;

            fault_list.insert(f1);
        }
    }
}

bool generateBinary(vector<bool> &arr, int i)
{
    if (i == No_input)
    {
        pair<vector<bool>, vector<pair<string, bool>>> m;
        m.first = arr;
        for (long long int i = 0; i < No_input; i++)
        {
            vector<bool> arr1(Collapse_fault.size() + 1, arr[i]);
            File.wire[i + 1].value.assign(arr1.begin(), arr1.end());
            ;
            // cout << arr[i];
        }

        // cout << endl;
        compute_CUT();

        vector<bool> out;
        for (int i = 0; i < File.wire.size(); i++)
        {
            if (File.wire[i + 1].w_type == "output")
            {
                out.push_back(!File.wire[i + 1].value[0]);
            }
        }

        // for true value
        //    for (auto i : File.wire)
        //  {
        //      cout << i.second.w_name << " ";
        //      for (int j = 0; j < i.second.value.size(); j++)
        //      {
        //          cout << i.second.value[j];
        //      }

        //     cout << endl;
        // }
        // cout<<"hooo"<<endl;

        parraller_fault_simulation();
        //  cout<<"hooo"<<endl;

        

        int p1 = 0;

        for (int i = 0; i < File.wire.size(); i++)
        {
            if (File.wire[i + 1].w_type == "output")
            {
                bool val;
                int pos = 1;
                for (auto k : Collapse_fault)
                {
                    if (k.first == File.wire[i + 1].w_name && k.second != File.wire[i + 1].value[0])
                    {
                        val = k.second;
                        break;
                    }

                    if (pos > Collapse_fault.size() + 1)
                    {
                        break;
                    }

                    pos++;
                }

                if (pos < Collapse_fault.size() + 1)
                {
                    File.wire[i + 1].value[pos] = val;
                }
                p1++;
            }
        }

// for Final
        // for (auto i : File.wire)
        // {
        //     cout << i.second.w_name << " ";
        //     for (int j = 0; j < i.second.value.size(); j++)
        //     {
        //         cout << i.second.value[j];
        //     }

        //     cout << endl;
        // }

        // int p = 0;

        for (int i = 0; i < File.wire.size(); i++)
        {
            if (File.wire[i + 1].w_type == "output")
            {
                //   cout<<"hiii1"<<endl;
                int index = 1;
                for (int k = 0; k < File.wire[i + 1].value.size(); k++)
                {
                    //  cout<<"hiii2"<<endl;
                    if (File.wire[i + 1].value[0] != File.wire[i + 1].value[k + 1])
                    {

                        // auto it = next(Collapse_fault.begin(), k);

                        //    cout<<(*it).first<<" " <<(*it).second<<endl;

                        auto it1 = Collapse_fault_List.find(vec_fault[k]);

                        if (it1 != Collapse_fault_List.end())
                        {
                            m.second.push_back(*it1);
                            Collapse_fault_List.erase(it1);
                        }
                    }
                    index++;
                }

                // p++;
            }
        }

        cout << Collapse_fault_List.size() << endl;
        //   cout<<m.second.size()<<endl;
        //    Detected_falut.push_back(m);

        //  cout<<Collapse_fault.size()<<endl;
        if (m.second.size() != 0)
        {
            Detected_falut.push_back(m);
        }

        if (Collapse_fault_List.size() == 0)
        {
            return true;
        }

        return false;
    }

    arr[i] = 0;
    if (generateBinary(arr, i + 1))
        return true;
    // return true;

    arr[i] = 1;
    if (generateBinary(arr, i + 1))
        return true;

    return false;
    // return true;
}

void Print(Verilog_File &File)
{
    long long int size_gate = File.gate.size();
    long long int size_wire = File.wire.size();
    for (long long int i = 0; i < size_gate; i++)
    {
        cout << File.gate[i + 1].g_name << " " << File.gate[i + 1].L << endl;
    }
}

int main()
{

    string file_name;

    cout << "Enter File Name: ";
    cin >> file_name;
    cout << "<-------------  Parallel Fault Simulation --------------->" << endl
         << endl;
    File = Convert_file(file_name);
    Logic_levelization(0);
    cout << "<------------------ Logic Levalization -------------------->" << endl
         << endl;
    Print(File);
    // cout<<"dskrjfgi5gyebrugegryrtge"<<endl;
    if (!circuit_modification(File))
    {
        cout << "ERROR!!: circuit modification error happened.." << endl;
        // return 0;
    }
    for (auto i = File.gate.begin(); i != File.gate.end(); i++)
    {
        // mpp[i->second.L]=i->first;
        mpp.insert(pair<int, int>(i->second.L, i->first));
    }

    cout << "<--------- After Modification Logic Levalization -------->" << endl
         << endl;
    // Logic_levelization(1);
    Print(File);

    // bool arr[5] = {0, 1, 0, 1, 1};
    // for (long long int i = 0; i < No_input; i++)
    // {
    //     // bool t;
    //     // cout<<"Enter bool value: ";
    //     // cin>>t;
    //     File.wire[i + 1].value = arr[i];
    // }

    // compute_CUT(mpp);

    // Print(File);

    Collapse_fault_list(Collapse_fault_List);

    for (auto i : File.wire)
    {
        if (i.second.w_type == "output")
        {
            pair<string, bool> f1;
            f1.first = i.second.w_name;
            f1.second = 1;
            // cout<<"12"<<f1.first<<","<<f1.second<<endl;
            Collapse_fault_List.insert(f1);

            f1.first = i.second.w_name;
            f1.second = 0;
            Collapse_fault_List.insert(f1);
        }
    }

    for (auto j : Collapse_fault_List)
    {
        vec_fault.push_back(j);
    }

    Collapse_fault = Collapse_fault_List;

    cout << "<----------------  Collapse Fault List  ------------------>" << endl
         << endl;
    for (auto i : Collapse_fault_List)
    {
        cout << "(" << i.first << "," << i.second << ")"
             << " ";
    }
    cout << endl
         << endl;
    cout << "-------------> Collapse Ratio : ";
    float fault_collapse_ratio = (Collapse_fault.size()) / float(File.wire.size() * 2);
    cout
        << fault_collapse_ratio << endl;

    cout << endl;

    cout << "<-------------  Parallel Fault Simulation --------------->" << endl
         << endl;

    // vector<bool>arr;
    //
    // pair<vector<bool>, vector<pair<string, bool>>> m;

    // for (int i = 0; i < No_input; i++)
    // {
    //     bool ans;
    //     cin >> ans;
    //     arr.push_back(ans);
    //     vector<bool> arr1(Collapse_fault.size(), ans);
    //     File.wire[i + 1].value.assign(arr1.begin(), arr1.end());
    // }

    //    m.first=arr;
    //     for(auto i:arr1)
    //     {
    //         cout<<i;
    //     }

    // cout<<endl;

    // File.wire[1].value.assign(arr1.begin(),arr1.end());
    // for(int i=0;i<File.wire.size();i++)
    // {
    //     File.wire[i+1].value.assign(arr1.begin(),arr1.end());
    // }

    //  Detected_falut.push_back(m);

    // for (auto i : File.wire)
    // {
    //     cout << i.second.w_name << " ";
    //     for (int j = 0; j < i.second.value.size(); j++)
    //     {
    //         cout << i.second.value[j];
    //     }

    //     cout << endl;
    // }

    vector<bool> arr1(No_input);
    generateBinary(arr1, 0);

    // cout<<"hi";

    for (auto i : Detected_falut)
    {
        cout << "<------------------------------>" << endl;
        cout << "  Using Test Vector : ";
        for (auto j : i.first)
        {
            cout << j;
        }

        cout << endl
             << "  Detected Faults "
             << "(" << i.second.size() << "):" << endl;

        for (auto j : i.second)
        {
            cout << "  (" << j.first << "," << j.second << ")" << endl;
        }
        cout << endl
             << endl;
    }

    cout << "<-------------  Undetected Fault List --------------->" << endl
         << endl;

    // cout << endl;

    // vector<Fault_gate_list> fault;

    // Parallel_fault_simulation(fault);
    if (Collapse_fault_List.size() == 0)
    {
        cout << "All faults detected....no undetected faults.." << endl
             << endl;
    }
    else
    {
        for (auto i : Collapse_fault_List)
        {
            cout << "(" << i.first << "," << i.second << ")"
                 << " ";
        }
        cout << endl
             << endl;
    }

    cout << "-------------> Fault Covarage: ";
    float fault_covrage = (2 * File.wire.size() - Collapse_fault_List.size()) / float(2 * File.wire.size());
    cout << fault_covrage;
    // for (auto i : fault)
    // {
    //     cout << i.g_name << endl;
    //     for (auto j : i.fault)
    //     {
    //         cout << "(" << j.first.first << "," << j.first.second << ")"
    //              << " (" << j.second.first << "," << j.second.second << ")" << endl;
    //     }

    //     cout << endl
    //          << endl;
    // }

    // unordered_map<pair<string, bool>, bool, hash_pair> mp_fault_list;
    // reverse(fault.begin(), fault.end());
    // //   cout<<File.output[0]<<File.output[1];
    // for (auto i : File.wire)
    // {
    //     if (i.second.w_type == "output")
    //     {
    //         pair<string, bool> f1;
    //         f1.first = i.second.w_name;
    //         f1.second = !i.second.value;
    //         // cout<<"12"<<f1.first<<","<<f1.second<<endl;
    //         mp_fault_list[f1] = true;
    //     }
    // }

    // Find_Fault_List(mp_fault_list, fault);
    // cout << "{ ";
    // for (auto j : mp_fault_list)
    // {
    //     if (j.second == true)
    //         cout << "(" << (j.first).first << "," << (j.first).second << ")"
    //              << " ,";
    // }
    // cout << " }";

    // cout<<"34tf"<<endl;
    // cout<<File.gate[2].g_name<<" "<<File.gate[2].L<<endl;
    // cout<<"34tf"<<endl;

    return 0;
}