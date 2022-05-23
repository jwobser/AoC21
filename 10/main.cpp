#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include "parser.hpp"

std::ifstream input;

int main(int argc, char** argv){
    (void)argc; //unused
    (void)argv; //unused
    long int score{0};
    input.open("input");
    std::string buf;
    while(!input.eof()){
        buf.clear();
        input >> buf;
        char result = checkline(buf);
        score += getscore(result);
    }
    scoreincomplete();
    std::cout << "Score: " << score << '\n';
    std::cout << "Median incomplete score: " << getincomplete() << '\n';
}
