#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Simulator {
private:
    
    uint32_t registers[12];

    bool flagN;
    bool flagZ;
    bool flagC;
    bool flagV;

    void flagPrintHandler(bool setFlags, std::string cmd, uint32_t r1, uint32_t r2, uint32_t result, std::fstream& output){

        if (setFlags){

            flagZ = (result == 0) ? 1 : 0;
            flagN = (result < 0) ? 1 : 0;

            printToFile(cmd+"S", r1, r2, result, output);

        } else {

            printToFile(cmd, r1, r2, result, output);

        }

    }

    void printToFile(std::string cmd, uint32_t r1, uint32_t r2, uint32_t result, std::fstream& output){


        std::ostringstream field1;
        field1 << "0x" << std::hex << r1;

        std::ostringstream field2;
        field2 << "0x" << std::hex << r2 << ":";

        std::ostringstream field3;
        field3 << "0x" << std::hex << result;

        output << std::setw(8) << std::left << cmd;
        output << std::setw(16) << std::right << field1.str();
        output << std::setw(16) << std::right << field2.str();
        output << std::setw(16) << std::right << field3.str() << std::endl;
        output << "N: " << flagN << " " << "Z: " << flagZ << std::endl;

    }

    int add(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        bool overflow = false;

        uint32_t result = r1 + r2;

        flagPrintHandler(setFlags, "ADD", r1, r2, result, output);

        return result;

    }

    void sub(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        bool overflow = false;

        u_int32_t difference = r1 - r2;

        if ( (difference>r1)||(difference>r2)) {

            overflow = true;

        }

        flagPrintHandler(setFlags, "ADD", r1, r2, difference, output);

    }

    void asr(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 >> r2;

        //set bit 32 to value of bit 31
        flagPrintHandler(setFlags, "ASR", r1, r2, result, output);

    }

    void lsr(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 >> r2;

        flagPrintHandler(setFlags, "LSR", r1, r2, result, output);

    }

    void asl(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 << r2;
        
        flagPrintHandler(setFlags, "ASL", r1, r2, result, output);

    }

    void lsl(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 << r2;

        flagPrintHandler(setFlags, "LSL", r1, r2, result, output);

    }

    void bitwiseAnd(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 & r2;

        flagPrintHandler(setFlags, "AND", r1, r2, result, output);

    }

    void bitwiseNot(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = ~r1;
        
        flagPrintHandler(setFlags, "NOT", r1, r2, result, output);

    }

    void bitwiseOr(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 | r2;

        flagPrintHandler(setFlags, "ORR", r1, r2, result, output);

    }

    void bitwiseXor(bool setFlags, uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        uint32_t result = r1 ^ r2;

        flagPrintHandler(setFlags, "XOR", r1, r2, result, output);
    
    }

public:

    Simulator(){

        flagN = 0;
        flagZ = 0;
        flagC = 0;
        flagV = 0;

    }

    void processLine(std::string cmd, uint32_t a, uint32_t b, std::fstream& output){

        if (cmd == "ADD"){

            add(0, 0, a, b, output);

        } else if (cmd == "ADDS"){

            add(1, 0, a, b, output);

        } else if (cmd == "SUB"){

            sub(0, 0, a, b, output);

        } else if (cmd == "SUBS"){

            sub(1, 0, a, b, output);

        } else if (cmd == "ASR"){  //Arithmetic Shift Right

            asr(0, 0, a, b, output);

        } else if (cmd == "ASRS"){

            asr(1, 0, a, b, output);

        } else if (cmd == "LSR"){ //Logical Shift Right

            lsr(0, 0, a, b, output);

        } else if (cmd == "LSRS"){

            lsr(1, 0, a, b, output);

        } else if (cmd == "ASL"){ //Arithmetic Shift Left

            asl(0, 0, a, b, output);

        } else if (cmd == "ASLS"){

            asl(1, 0, a, b, output);

        } else if (cmd == "LSL"){ //Logical Shift left

            lsl(0, 0, a, b, output);

        } else if (cmd == "LSLS"){

            lsl(1, 0, a, b, output);

        } else if (cmd == "AND"){ //Bitwise operations

            bitwiseAnd(0, 0, a, b, output);

        } else if (cmd == "ANDS"){

            bitwiseAnd(1, 0, a, b, output);

        } else if (cmd == "NOT"){

            bitwiseNot(0, 0, a, b, output);

        } else if (cmd == "NOTS"){

            bitwiseNot(1, 0, a, b, output);

        } else if (cmd == "ORR"){

            bitwiseOr(0, 0, a, b, output);

        } else if (cmd == "ORRS"){

            bitwiseOr(1, 0, a, b, output);

        } else if (cmd == "XOR"){

            bitwiseXor(0, 0, a, b, output);

        } else if (cmd == "XORS"){

            bitwiseXor(1, 0, a, b, output);

        }

    }

};
