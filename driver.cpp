#include <iostream>
#include <string>
#include <fstream>

#include "simulator.hpp"

int main(){

    std::fstream input;
    std::fstream output;

    std::string cmd;
    uint32_t a;
    uint32_t b;

    Simulator mySimulator;

    input.open ("input.txt", std::fstream::in);
    output.open ("output.txt", std::fstream::out);

    std::cout << "Begin Program" << "\n";

    while ( input >> cmd >> std::hex >> a >> b ){

        //mySimulator.processLine(cmd, a, b, output);

    }

    input.close();

}
