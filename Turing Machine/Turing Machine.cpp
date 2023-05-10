#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int numberOfStates;
    int numberOfStringAlphabet;
    int numberOfMachineAlphabet;
    char stringSymbols[100];
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
        cin >> stringSymbols[i];
    }

    // Input the number of machine symbols
    cout << "Enter the number of machine alphabet:" << endl;
    cin >> numberOfMachineAlphabet;
    if (numberOfMachineAlphabet <= 0)
    {
        cout << "The number of machine symbols must be greater than 0." << endl;
    }

    // Input the machine symbols
    machineSymbols.insert('L');
    machineSymbols.insert('R');
    machineSymbols.insert('Y');
    machineSymbols.insert('N');
    cout << "Enter the machine symbols:" << endl;
    for (int i = 0; i < numberOfMachineAlphabet; i++) {
        char symbol;
        cin >> symbol;
        if (machineSymbols.find(symbol) == machineSymbols.end()) { // check for duplicates
            machineSymbols.insert(symbol);
        }
        else {
            cout << "Duplicate symbol found. Please enter a different symbol." << endl;
            i--;
        }
    }

    // Input the transition table
    cout << "Enter the transition table:" << endl;
    for (int i = 0; i < numberOfStates * (numberOfStringAlphabet + numberOfMachineAlphabet); i++) {
        for (int j = 0; j < 5; j++) {
			cin >> transitionTable[i][j];
		}
}
	// Input the input string
	cout << "Enter the input string:" << endl;
	cin >> input;
    input.append("#");
    if (!std::all_of(input.begin(), input.end(), [stringSymbols](char c) {
        return string(stringSymbols).find(c) != string::npos || c == '#';
        })) {
        std::cout << "The input string contains symbols that are not in the string alphabet." << std::endl;
        exit(1);
    }
	// Input the current head
	cout << "Enter the current head:" << endl;
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
			std::cout << "The machine has halted due to an invalid number of states" << std::endl;
			exit(1);
		}
        else {
             nextState = (int)(transition[2] - '0');
             nextSymbol = transition[3];
        }
         // if there is a symbol that is not in the string alphabet or the machine alphabet, exit
        if (machineSymbols.find(nextSymbol) == machineSymbols.end() && string(stringSymbols).find(nextSymbol) == string::npos ) {
			std::cout << "The machine has halted due to an invalid symbol." << std::endl;
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
            break;
        case 'L':
            currentHead--;
            break;
        case 'Y':
            std::cout << "The final string is: " << input << std::endl;
            std::cout << "The final position of the head is: " << currentHead << std::endl;
            exit(0);
        case 'N':
            std::cout << "Exited with status: NO " << std::endl;
            std::cout << "The final string is: " << input << std::endl;
            std::cout << "The final position of the head is: " << currentHead << std::endl;
            exit(1);
        default:
            std::cout << "The machine has halted due to an invalid symbol." << std::endl;
            exit(1);
        }
    }
	
    }

    
