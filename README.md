# CS219-Programming-Assignment-1
--------------------------------------------
## How to run code

1) Run Command: `make` in the directory
2) Run Command: `./armSim`
3) Program outputs to `output.txt`

--------------------------------------------
Result and Working Process

### Simulator Class:

- Class which holds register values and flags, while providing methods to perform ARM commands

- `processLine()` accepts a file stream and command arguments. **Resets N, Z flags** and then interprets command. Then, calls corresponding opcode method

- `flagPrintHandler()` is called by opcode methods to set the N, Z flags based on the value of the result, if the command sets flags
    - Z is set if result is 0
    - N is set if result is less than 0
    - For bit shift operations, N is set if the 32nd bit is 1; otherwise, N is 0.

- `printToFile()` method is called by the flagPrintHandler() to print command, operands, result and N, Z flag values

- OPCODE methods
    - `add()` adds with arithmetic operator +
    - `sub()` subtracts with arithmetic operator -
        - may be changed in the future to perform subtraction using two's complement to provide flexibility in handling signed nums
    - Bit Shift Operations
        - Arithmetic Shift
            - Right: shifts the result one bit at a time until finished. Each sub-shift sets the 32nd bit based on the first operand
            - Left: uses operator `<<` for bit shift. Undefined bits are made 0.
        - Logical Shift
            - Uses `<<` , `>>` operators for bit shift. Undefined bits are always 0.
    - `and()` uses operator `&` for bitwise AND
    - `not()` uses operator `~` for bitwise NOT
    - `orr()` uses operator `|` for bitwise OR
    - `xor()` uses operator `^` for bitwise XOR

### Main:

- Opens input file and reads line by line

- Reads values into variables which are passed into the simulator


