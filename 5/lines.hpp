#pragma once
#include "points.hpp"
#include <iostream>
#include <fstream>

struct Line{
    Point start,end;

    void printline();
    bool isvertical() const;
    bool ishorizontal() const;
    bool isdiagonal() const;
};

Line getline(std::ifstream& input){
    Point start{getpoint(input)};
    char in;
    while(!isdigit(in = input.get())){ }
    input.putback(in);
    Point end{getpoint(input)};
    return Line{start,end};
}

void Line::printline(){
    std::cout << start.x << ", "\
    << start.y << " - "\
    << end.x << ", " << end.y << '\n';
}

bool Line::ishorizontal() const{
    if(start.y == end.y) return true;
    return false;
}

bool Line::isvertical() const{
    if(start.x == end.x) return true;
    return false;
}

bool Line::isdiagonal() const{
    if(start.x != end.x && start.y != end.y) return true;
    return false;
}