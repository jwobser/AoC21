#include <fstream>
#include <iostream>
#include <string>
#include "field.hpp"

std::ifstream input;
std::string buf;

int main(int argc, char** argv){
    (void)argc; // Unused
    (void)argv; // Unused
    int temp;
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

    int runs{0};
    while(temp != 100){
        temp = step();
        ++runs;
    }

    std::cout << "Flash sync step: " << runs << '\n';
}