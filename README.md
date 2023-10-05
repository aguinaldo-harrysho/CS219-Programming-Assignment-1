# CS219-Programming-Assignment-1
--------------------------------------------
How to run code

1) Run Command: `make`
2) Run Command: `./armSim`
3) Program outputs to "output.txt"


--------------------------------------------
Result and Working Process

- Simulator Class:

    -Class which holds register values and flags, while providing methods to perform ARM commands

    -processLine() method accepts a file stream and command arguments. Interprets opcode and calls corresponding private method

    -add() method performs hex addition and prints directly to output file.



- Main:

    -Opens input file and reads line by line

    -Reads values into variables which are passed into the simulator