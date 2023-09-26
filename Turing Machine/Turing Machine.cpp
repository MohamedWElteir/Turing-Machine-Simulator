#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>


using namespace std;

int main() {
    int numberOfStates;
    int numberOfStringAlphabet;
    int numberOfMachineAlphabet;
    set <char> stringSymbols;
    set<char> machineSymbols;
    char transitionTable[100][5];
    string input;
    int currentHead;

    // Input the number of states
    cout << "Enter the number of states:" << endl;
    cin >> numberOfStates;
    if (numberOfStates <= 0)
    {
        cout << "The number of states must be greater than 0." << endl;
        exit(1);
    }

    // Input the number of string symbols
    cout << "Enter the number of string symbols:" << endl;
    cin >> numberOfStringAlphabet;
    if (numberOfStringAlphabet <= 0)
    {
        cout << "The number of string symbols must be greater than 0." << endl;
        exit(1);
    }

    // Input the string symbols
    cout << "Enter the string symbols:" << endl;
    for (int i = 0; i < numberOfStringAlphabet; i++) {
        char symbol;
        cin >> symbol;
        if (symbol == 'L' || symbol == 'R' || symbol == 'Y' || symbol == 'N') {
            cout << "The symbol " << symbol << " is reserved for the machine alphabet. Please enter a different symbol." << endl;
            i--;
        }
        else if (symbol == '#') {
            cout << "The symbol " << symbol << " is reserved as a blank symbol. Please enter a different symbol." << endl;
            i--;
        }
        else if (stringSymbols.find(symbol) == stringSymbols.end()) { // check for duplicates
            stringSymbols.insert(symbol);
        }
        else {
            cout << "Duplicate symbol " << symbol << " found. Please enter a different symbol." << endl;
            i--;
        }

    }

    // Input the number of machine symbols
    cout << "Enter the number of machine alphabet:" << endl;
    cin >> numberOfMachineAlphabet;
    if (numberOfMachineAlphabet < 0)
    {
        cout << "The number of symbols can't be in negative." << endl;
        exit(1);
    }

    // Input the machine symbols
    machineSymbols.insert('L');
    machineSymbols.insert('R');
    machineSymbols.insert('Y');
    machineSymbols.insert('N');
    machineSymbols.insert('#');
    if (numberOfMachineAlphabet == 0) {}
    else {
        cout << "Enter the machine symbols:" << endl;
        for (int i = 0; i < numberOfMachineAlphabet; i++) {
            char symbol;
            cin >> symbol;
            // if the symbol is in the string alphabet, exit
            if (stringSymbols.find(symbol) != stringSymbols.end()) {
                cout << "The symbol " << symbol << " is already implemented in the string alphabet. Please enter a different symbol." << endl;
                i--;
            }
            else
                if (symbol == 'L' || symbol == 'R' || symbol == 'Y' || symbol == 'N' || symbol == '#') {
                    cout << "The symbol " << symbol << " is already implemented in the machine. Please enter a different symbol." << endl;
                    i--;
                }
                else
                    if (machineSymbols.find(symbol) == machineSymbols.end()) { // check for duplicates
                        machineSymbols.insert(symbol);
                    }
                    else {
                        cout << "Duplicate symbol " << symbol << " found. Please enter a different symbol." << endl;
                        i--;
                    }

        }
    }

    // Input the transition table
    cout << "Enter the transition table:" << endl;
    if (numberOfMachineAlphabet == 0) { numberOfMachineAlphabet = 1; }
    for (int i = 0; i < numberOfStates * (numberOfStringAlphabet + numberOfMachineAlphabet); i++) {
        for (int j = 0; j < 5; j++) {
            cin >> transitionTable[i][j];
        }
    }
    // Input the input string
    cout << "Enter the input string:" << endl;
    cin >> input;

    input = "#" + input + "#";
    if (!all_of(input.begin(), input.end(), [machineSymbols, stringSymbols](char c) {
        return (machineSymbols.find(c) != machineSymbols.end()) || (stringSymbols.find(c) != stringSymbols.end()) || c == '#';
        })) {
        cout << "The input string contains symbols that are not in the string alphabet." << endl;
        exit(1);
    }

    // Input the current head
    cout << "Enter the current head's position (1-based):" << endl;
    cin >> currentHead;

    int currentState = 0;
    int nextState;
    char transition[5];
    char currentSymbol;
    char nextSymbol;
    while (true) {

        // Set the current symbol
        currentSymbol = input[currentHead];

        // loop through the transition table to find the next state
        for (int i = 0; i < numberOfStates * (numberOfStringAlphabet + numberOfMachineAlphabet); i++) {
            if (transitionTable[i][0] == (char)(currentState + '0') && transitionTable[i][1] == currentSymbol) {
                for (int j = 0; j < 5; j++) {
                    transition[j] = transitionTable[i][j];
                }
                break;
            }
        }

        // Get the next state and symbol
        if (((int)(transition[2] - '0')) >= numberOfStates) {
            cout << "The machine has halted due to an invalid number of states" << endl;
            exit(1);
        }
        else {
            nextState = (int)(transition[2] - '0');
            nextSymbol = transition[3];
        }
        // if there is a symbol that is not in the string alphabet or the machine alphabet, exit
        if (machineSymbols.find(nextSymbol) == machineSymbols.end() && stringSymbols.find(nextSymbol) == stringSymbols.end()) {
            cout << "The machine has halted due to an invalid symbol from the transition function." << endl;
            exit(1);
        }
        else {
            // Write the next symbol
            input[currentHead] = nextSymbol;
        }

        // Update the current state
        currentState = nextState;

        // Move the head
        switch (transition[4]) {
        case 'R':
            currentHead++;
            if (currentHead >= input.length()) {
                input += '#';
            }
            break;
        case 'L':
            currentHead--;
            if (currentHead < 0) {
                input = '#' + input;
            }
            break;
        case 'Y':
            cout << "The final string is: " << input << endl;
            cout << "The final position of the head is: " << currentHead << endl;
            exit(0);
        case 'N':
            cout << "Exited with status: NO " << endl;
            cout << "The final string is: " << input << endl;
            cout << "The final position of the head is: " << currentHead << endl;
            exit(1);
        default:
            cout << "The machine has halted due to some error.(try to double check your transitions)" << endl;
            exit(1);
        }
    }

}