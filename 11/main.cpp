#include <fstream>
#include <iostream>
#include <string>
#include "field.hpp"

std::ifstream input;
std::string buf;

int main(int argc, char** argv){
    int flashes{0};
    input.open("input");
    {
        int i{0}, j{0};
        char inchar;
        while (!input.eof())
        {
            inchar = input.get();
            if (inchar == '\n'){
                ++i;
                j = 0;
                continue;
            } 
            field[i][j] = atoi(&inchar);
            ++j;
        }
    }
    input.close();
    printfield();

    for(int runs{0}; runs < 100; ++runs){
        // printfield();
        flashes += step();
    }

    std::cout << "Flashes: " << std::dec << flashes << '\n';

    // printfield();
}