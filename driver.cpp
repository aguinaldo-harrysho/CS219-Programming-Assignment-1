#include <iostream>
#include <string>
#include <fstream>

#include "simulator.hpp"

int main(){

    std::fstream input;
    std::fstream output;

    input.open ("input.txt", std::fstream::in);
    output.open ("output.txt", std::fstream::out);

    std::string line;

    Simulator mySimulator;

    std::cout << "Begin Program" << "\n";

    while ( std::getline(input, line)){

        mySimulator.processLine(line, output);

    }

    input.close();

}
