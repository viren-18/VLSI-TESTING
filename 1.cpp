#include <iostream>
#include <vector>

using namespace std;

// Function to generate all possible binary inputs
void generateBinaryInputs(vector<vector<int>>& posinputs, vector<int>& current, int n, int index) {
    if (index == n) {
        inputs.push_back(current);
        return;
    }

    // Set current bit to 0 and recurse
    current[index] = 0;
    generateBinaryInputs(inputs, current, n, index + 1);

    // Set current bit to 1 and recurse
    current[index] = 1;
    generateBinaryInputs(inputs, current, n, index + 1);
}

int main() {
    int numInputs;
    cout << "Enter the number of binary inputs: ";
    cin >> numInputs;

    // Initialize vector to hold all possible inputs
    vector<vector<int>> posinputs;

    // Temporary vector to hold current input
    vector<int> current(numInputs, 0);

    // Generate all possible binary inputs
    generateBinaryInputs(posinputs, current, numInputs, 0);

    // Display all generated inputs
    cout << "All possible binary inputs are:\n";
    for (const auto& input : inputs) {
        for (int bit : input) {
            cout << bit << " ";
        }
        cout << endl;
    }

    return 0;
}
