#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Simulator {
private:
    
    uint32_t r[8]; //registers

    bool flagN;
    bool flagZ;
    bool flagC;
    bool flagV;

    /*
    void flagPrintHandler(bool isShiftOperation, bool setFlags, std::string cmd, uint32_t rn, uint32_t rm, uint32_t result){

        if (setFlags){

            flagZ = (result == 0) ? 1 : 0;

            if (isShiftOperation){

                uint32_t mask = 0x80000000;

                flagN = ( (result&mask) == 0x80000000) ? 1 : 0;

            } else {

                flagN = (result < 0) ? 1 : 0;    

            }

            printToFile(cmd+"S", rn, rm, result);

        } else {

            printToFile(cmd, rn, rm, result);

        }

    }
*/
    void setNZ(int d){

        uint32_t mask = 0x80000000;
        flagN = ( (r[d]&mask) == 0x80000000) ? 1 : 0;
        flagZ = ( r[d] == 0x0) ? 1 : 0;

    }

    void setV(int d, int sign1, int sign2){



    }

    void printToFile(std::string line, std::fstream& output){

        output << line <<std::endl;

        for (int i = 0; i < 8; i++){

            output << 'R' << i << ": 0x" << std::hex << r[i] << ' ';

        }
        output << std::endl;

        output << "N: " << flagN << ' ';
        output << "Z: " << flagZ << ' ';
        output << "C: " << flagC << ' ';
        output << "V: " << flagV << std::endl;

    }

    void mov(int d, uint32_t imm){

        r[d] = imm;

    }

    void asr(bool setFlags, int d, int n, int m){

        /*
        uint32_t result = 0;

        for (int i = 0; i < rm; i++){

            result = rn >> 1;

            uint32_t mask = rn & 0x80000000; // 0x80000000 if bit 32 is 1; 0x0 if bit 32 is 0
            
            result = result ^ mask; // set bit 32 of result to bit 32 of rn    

        }
        */


        for (int i = 0; i < m; i++){

            r[d] = r[n] >> 1;

            uint32_t mask = r[n] & 0x80000000; // 0x80000000 if bit 32 is 1; 0x0 if bit 32 is 0
            
            r[d] = r[d] ^ mask; // set bit 32 of result to bit 32 of rn    

        }

        if (setFlags){

            setNZ(d);

        }


    }

    void lsr(bool setFlags, int d, int n, int m){

        r[d] = r[n] >> m;

        if (setFlags){

            setNZ(d);

        }


    }

    void asl(bool setFlags, int d, int n, int m){

        bool carry = 0;

        uint32_t mask = r[n] & 0x80000000;

        if (mask != 0){

            carry = 1;

        }

        r[d] = r[n] << m;

        if (setFlags){

            setNZ(d);
            flagC = carry;

        }


    }

    void lsl(bool setFlags, int d, int n, int m){

        bool carry = 0;

        uint32_t mask = r[n] & 0x80000000;
        if (mask != 0){

            carry = 1;

        }

        r[d] = r[n] << m;

        if (setFlags){

            setNZ(d);
            flagC = carry;

        }


    }

    int add(bool setFlags, int d, int n, int m){

        bool overflow = false;

        int sum;
    
        sum = r[n] + r[m];
        r[d] = sum;

        uint32_t maskN32 = r[n] & 0x80000000;
        uint32_t maskM32 = r[m] & 0x80000000;
        uint32_t maskD32 = r[d] & 0x80000000;

        if (setFlags){

            setNZ(d);

            if (sum >= 0x7FFFFFFF){

                flagC = 1;

            } else {

                flagC = 0;

            }

            if ( (maskN32 == maskM32) && (maskD32 != maskN32)  ){

                flagV = 1;

            } else {

                flagV = 0;

            }

        }

        return r[d];

    }

    void sub(bool setFlags, bool saveValue, int d, int n, int m){

        bool overflow = false;

        u_int32_t difference = r[n] - r[m];

        r[d] = difference;

        if ( (difference>r[n])||(difference>r[m])) {

            overflow = true;

        }

        if (setFlags){

            setNZ(d);
            flagV = overflow;

        }


    }

    void bitwiseAnd(bool setFlags, bool saveValue, int d, int n, int m){

        r[d] = r[n] & r[m];

        if (setFlags){

            setNZ(d);

        }


    }

    void bitwiseNot(bool setFlags, int d, int n, int m){

        r[d] = ~r[n];

        if (setFlags){

            setNZ(d);

        }

    }

    void bitwiseOr(bool setFlags, int d, int n, int m){

        r[d] = r[n] | r[m];
        
        if (setFlags){

            setNZ(d);

        }

    }

    void bitwiseXor(bool setFlags, int d, int n, int m){

        r[d] = r[n] ^ r[m];

        if (setFlags){

            setNZ(d);

        }
    
    }

public:

    Simulator(){

        flagN = 0;
        flagZ = 0;
        flagC = 0;
        flagV = 0;

        for (int i = 0; i < 8; i++){

            r[i] = 0;

        }

    }

    void processLine(std::string line, std::fstream& output){

        std::stringstream input;
        input << line;

        std::string cmd; 
        std::string rd; 
        std::string rn; 
        std::string rm;
        input >> cmd >> rd >> rn >> rm;

        transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

        uint32_t imm;

        std::stringstream temp;
        char c;

        temp << rn;
        temp >> c >> c >> c >> std::hex >> imm;

        int d = rd[1] - 48;
        int n = rn[1] - 48;
        int m = rm[1] - 48;

        if (cmd == "MOV"){

            mov(d, imm);
        
        } else if (cmd == "ASR"){  //Arithmetic Shift Right

            asr(0, d, n, m);

        } else if (cmd == "ASRS"){

            asr(1, d, n, m);

        } else if (cmd == "LSR"){ //Logical Shift Right

            lsr(0, d, n, m);

        } else if (cmd == "LSRS"){

            lsr(1, d, n, m);

        } else if (cmd == "ASL"){ //Arithmetic Shift Left

            asl(0, d, n, m);

        } else if (cmd == "ASLS"){

            asl(1, d, n, m);

        } else if (cmd == "LSL"){ //Logical Shift left

            lsl(0, d, n, m);

        } else if (cmd == "LSLS"){

            lsl(1, d, n, m);

        } else if (cmd == "ADD"){

            add(0, d, n, m);

        } else if (cmd == "ADDS"){

            add(1, d, n, m);

        } else if (cmd == "SUB"){

            sub(0, 1, d, n, m);

        } else if (cmd == "SUBS"){

            sub(1, 1, d, n, m);

        }else if (cmd == "AND"){ //Bitwise operations

            bitwiseAnd(0, 1, d, n, m);

        } else if (cmd == "ANDS"){

            bitwiseAnd(1, 1, d, n, m);

        } else if (cmd == "NOT"){

            bitwiseNot(0, d, n, m);

        } else if (cmd == "NOTS"){

            bitwiseNot(1, d, n, m);

        } else if (cmd == "ORR"){

            bitwiseOr(0, d, n, m);

        } else if (cmd == "ORRS"){

            bitwiseOr(1, d, n, m);

        } else if (cmd == "XOR"){

            bitwiseXor(0, d, n, m);

        } else if (cmd == "XORS"){

            bitwiseXor(1, d, n, m);

        } else if (cmd == "CMP"){

            sub(1, 0, d, n, m);

        } else if (cmd == "TST"){

            bitwiseAnd(1, 0, d, n, m);

        }
        printToFile(line, output);

    }

};
