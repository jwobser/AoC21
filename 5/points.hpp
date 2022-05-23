#pragma once
#include <fstream>

struct Point{
    int x,y;
};

Point getpoint(std::ifstream& input){
    int x,y;
    if(!input.is_open()) throw std::ios_base::failure("File not opened");
    input >> x;
    if(input.get() != ',') throw std::ios_base::failure("Bad format");
    input >> y;
    return Point{x,y};
}