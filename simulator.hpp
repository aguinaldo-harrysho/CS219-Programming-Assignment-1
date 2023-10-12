#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Simulator {
private:
    
    uint32_t registers[12];

    bool n;
    bool z;
    bool c;
    bool v;

    int add(uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        bool overflow = false;

        uint32_t sum = r1 + r2;

        if (((sum < r1)||(sum<r2)) && (r1>0) && (r2>0)){

            overflow = true;

        }

        std::ostringstream field1;
        field1 << "0x" << std::hex << r1;

        std::ostringstream field2;
        field2 << "0x" << std::hex << r2 << ":";

        std::ostringstream field3;
        field3 << "0x" << std::hex << sum;



        output << "ADD\t";
        output << std::setw(16) << std::right << field1.str();
        output << std::setw(16) << std::right << field2.str();
        output << std::setw(16) << std::right << field3.str();
        output << std::endl;

        output << "Overflow:\t";

        if (overflow){

            output << "Yes\n\n";

        } else {

            output << "No\n\n";

        }

        return sum;

    }

    void sub(uint32_t rd, uint32_t r1, uint32_t r2, std::fstream& output){

        bool overflow = false;

        u_int32_t difference = r1 - r2;



    }

    void asr(){



    }

    void lsr(){



    }

    void lsl(){



    }

    void bitwiseAnd(){



    }

    void bitwiseNot(){



    }

    void bitwiseOr(){



    }

    void bitwiseXor(){



    }




public:

    Simulator(){

        n = 0;
        z = 0;
        c = 0;
        v = 0;

    }

    void processLine(std::string cmd, uint32_t a, uint32_t b, std::fstream& output){

        if (cmd == "ADD"){

            add(0, a, b, output);

        }

    }

};
