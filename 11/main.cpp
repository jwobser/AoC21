#include <fstream>
#include <iostream>
#include <string>

std::ifstream input;
std::string buf;

int main(int argc, char** argv){
    input.open("input");
    input >> buf;
    std::cout << "First line of input:\n";
    std::cout << buf << std::endl;
}
