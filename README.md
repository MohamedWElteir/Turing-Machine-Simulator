# Turing Machine Simulator
This is a very simple implementation of a semi-decidable turing machine that reads from the user:
1- Number of machine states
2- Number of string symbols and the symbols as well as the machine's
3- The transition function (This is the 5-tuples of a turing machine, Must be provided to the machine with every possible combination of states and symbols in order to not hang.) The program takes the input as 5-tupled characters as follows:
(Q0,Σ0,Q1,Σ1,D) where
Q0 -> The current state that the machine is on
Σ0 -> The current string pointed by the head
Q1 -> The next state of the machine
Σ1 -> The next symbol to be written on cell by the head (As the head of a turing machine has the ability to read and write, hence making computations)
D -> The desition of the machine ( Can be one of 4 options: R for going one cell to the right, L for going one cell to the left, Y for halting and accepting hence 																		exiting with code 0 or N for halting and exiting but with code 1 (indiicating some error occured or the string was not accepted) )
4- The sequence of characters (The string to be tested)
5-The initial position of the head (As because the turing machine's head can be replaced manually to any desired position on the infinite tape)

#The program then computes on the string and outputs to the user the final string as well as the final position of the head.
