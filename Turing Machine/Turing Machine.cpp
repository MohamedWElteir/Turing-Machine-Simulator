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

    // Input the number of string symbols
    cout << "Enter the number of string symbols:" << endl;
    cin >> numberOfStringAlphabet;

    // Input the string symbols
    cout << "Enter the string symbols:" << endl;
    for (int i = 0; i < numberOfStringAlphabet; i++) {
        cin >> stringSymbols[i];
    }

    // Input the number of machine symbols
    cout << "Enter the number of machine alphabet:" << endl;
    cin >> numberOfMachineAlphabet;

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
        return std::string(stringSymbols).find(c) != std::string::npos || c == '#';
        })) {
        std::cout << "The input string contains symbols that are not in the string alphabet." << std::endl;
        exit(1);
    }
	// Input the current head
	cout << "Enter the current head:" << endl;
	cin >> currentHead;

    int currentState = 0;
    while (true) {

        // Set the current symbol and transition
        char transition[5];
        char currentSymbol = input[currentHead];

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
        int nextState = (int)(transition[2] - '0');
        char nextSymbol = transition[3];

        // Write the next symbol
        input[currentHead] = nextSymbol;

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
            std::cout << "Exited with status NO" << std::endl;
            std::cout << "The final string is: " << input << std::endl;
            std::cout << "The final position of the head is: " << currentHead << std::endl;
            exit(1);
        default:
            std::cout << "The machine has halted due to the head going out of bounds." << std::endl;
        }
    }
	
    }

    
