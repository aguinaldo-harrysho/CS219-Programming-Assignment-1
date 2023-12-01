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

- `printToFile()` reprints the line processed, then prints all register and flag values

### OPCODE methods

    - `add()` adds with arithmetic operator +
        - Carry : if the non-truncated sum is greater than 0x7FFFFFFF
        - Overflow : mask values with 0x80000000 to get 32nd bit value. see if the sign bit of the result is different from those of the operands, if the operands' sign bits are the same 
    - `sub()` subtracts with arithmetic operator -
        - may be changed in the future to perform subtraction using two's complement to provide flexibility in handling signed nums
        - Overflow : if the result is greater than either operand
    - Bit Shift Operations
        - Carry : if shifting left and the operand has bit 32 set before the operation
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


