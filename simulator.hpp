#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Simulator {
private:
    
    uint32_t Reg[8];

    bool flagN;
    bool flagZ;
    bool flagC;
    bool flagV;

    void flagPrintHandler(bool isShiftOperation, bool setFlags, std::string cmd, uint32_t rn, uint32_t rm, uint32_t result, std::fstream& output){

        if (setFlags){

            flagZ = (result == 0) ? 1 : 0;

            if (isShiftOperation){

                uint32_t mask = 0x80000000;

                flagN = ( (result&mask) == 0x80000000) ? 1 : 0;

            } else {

                flagN = (result < 0) ? 1 : 0;    

            }

            printToFile(cmd+"S", rn, rm, result, output);

        } else {

            printToFile(cmd, rn, rm, result, output);

        }

    }

    void printToFile(std::string cmd, uint32_t rn, uint32_t rm, uint32_t result, std::fstream& output){

        std::ostringstream field1;
        field1 << "0x" << std::hex << rn;

        std::ostringstream field2;
        field2 << "0x" << std::hex << rm << ":";

        std::ostringstream field3;
        field3 << "0x" << std::hex << result;

        output << std::setw(8) << std::left << cmd;
        output << std::setw(16) << std::right << field1.str();
        output << std::setw(16) << std::right << field2.str();
        output << std::setw(16) << std::right << field3.str() << std::endl;
        output << "N: " << flagN << " " << "Z: " << flagZ << std::endl;

    }

    int add(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        bool overflow = false;

        uint32_t result = rn + rm;

        flagPrintHandler(0, setFlags, "ADD", rn, rm, result, output);

        return result;

    }

    void sub(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        bool overflow = false;

        u_int32_t difference = rn - rm;

        if ( (difference>rn)||(difference>rm)) {

            overflow = true;

        }

        flagPrintHandler(0, setFlags, "ADD", rn, rm, difference, output);

    }

    void asr(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        /*
        uint32_t result = 0;

        for (int i = 0; i < rm; i++){

            result = rn >> 1;

            uint32_t mask = rn & 0x80000000; // 0x80000000 if bit 32 is 1; 0x0 if bit 32 is 0
            
            result = result ^ mask; // set bit 32 of result to bit 32 of rn    

        }
        */

       int32_t result = 0;


        for (int i = 0; i < rm; i++){

            result = rn >> 1;

            uint32_t mask = rn & 0x80000000; // 0x80000000 if bit 32 is 1; 0x0 if bit 32 is 0
            
            result = result ^ mask; // set bit 32 of result to bit 32 of rn    

        }

        flagPrintHandler(1, setFlags, "ASR", rn, rm, result, output);
    }

    void lsr(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn >> rm;

        flagPrintHandler(1, setFlags, "LSR", rn, rm, result, output);

    }

    void asl(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn << rm;
        
        flagPrintHandler(1, setFlags, "ASL", rn, rm, result, output);

    }

    void lsl(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn << rm;

        flagPrintHandler(1, setFlags, "LSL", rn, rm, result, output);

    }

    void bitwiseAnd(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn & rm;

        flagPrintHandler(0, setFlags, "AND", rn, rm, result, output);

    }

    void bitwiseNot(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = ~rn;
        
        flagPrintHandler(0, setFlags, "NOT", rn, rm, result, output);

    }

    void bitwiseOr(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn | rm;

        flagPrintHandler(0, setFlags, "ORR", rn, rm, result, output);

    }

    void bitwiseXor(bool setFlags, uint32_t rd, uint32_t rn, uint32_t rm, std::fstream& output){

        uint32_t result = rn ^ rm;

        flagPrintHandler(0, setFlags, "XOR", rn, rm, result, output);
    
    }

public:

    Simulator(){

        flagN = 0;
        flagZ = 0;
        flagC = 0;
        flagV = 0;

    }

    void processLine(std::string cmd, uint32_t a, uint32_t b, std::fstream& output){

        flagN = 0;
        flagZ = 0;

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
