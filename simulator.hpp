#include <iostream>
#include <fstream>

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

        output << "ADD\t";
        output << std::hex << std::setw(16) << std::right << "0x"+std::to_string(r1);
        output << std::hex << std::setw(16) << std::right << "0x"+std::to_string(r2)+":";
        output << std::hex << std::setw(16) << std::right << "0x"+std::to_string(sum);
        output << std::endl;

        output << "Overflow:\t";

        if (overflow){

            output << "Yes\n\n";

        } else {

            output << "No\n\n";

        }

        return sum;

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
