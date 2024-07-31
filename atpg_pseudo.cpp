#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


unordered_map<string, bool> PI;
unordered_map<string, pair<string, char>> circuit; 


bool getControllingValue(char gateType) {
    if (gateType == 'A') 
        return false;
    else if (gateType == 'O') 
        return true;
    else
        return false; 
}


bool invertValue(bool val) {
    return !val;
}


void Justify(const string& h, bool val) {
    cout << "Set line " << h << " to " << val << endl;

   
    if (PI.find(h) != PI.end()) {
        return;
    }


    char gateType = circuit[h].second;
    bool c = getControllingValue(gateType);
    bool i = invertValue(c);

    bool inval = val ^ i;

    if (inval == c) {
        for (const auto& input : circuit) {
            if (input.second.first == h) {
                Justify(input.first, inval);
            }
        }
    } else {
        for (const auto& input : circuit) {
            if (input.second.first == h) {
                Justify(input.first, inval);
                break;
            }
        }
    }
}

int main() {
  
    PI["A"] = true;
    PI["B"] = true;

    
    circuit["h"] = make_pair("A", 'A'); 

    Justify("h", false);
    cout<<PI["A"]<< " "<<PI["B"];

    return 0;
}
