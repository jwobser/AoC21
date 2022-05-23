#include <fstream>
#include <iostream>
#include "points.hpp"
#include "lines.hpp"
#include <vector>
#include <compare>


void resetfield(uint8_t* field);
int countfield(uint8_t* field);
short getstep(int a, int b);


int main(int argc, char** argv){
    std::ifstream input;
    input.open("input");
    if(!input) return - 1;

    std::vector<Line> lines;
    lines.reserve(600);

    while (!input.eof()){
        lines.emplace_back(getline(input));
    }

    std::cout << "Lines ingested: " << lines.size() << '\n';

    uint8_t field[1000][1000];
    resetfield((uint8_t*)field);

    for(const Line& line: lines){
        const short sx {getstep(line.start.x, line.end.x)};
        const short sy {getstep(line.start.y, line.end.y)};
        for(int y{line.start.y}, x{line.start.x}; x != line.end.x + sx || y != line.end.y + sy; x+=sx, y+=sy){
            field[y][x] += 1;
        }
    }

    int overlap{0};
    overlap = countfield((uint8_t*) field);

    std::cout << "overlaps: " << overlap << std::endl;
}

void resetfield(uint8_t* field){
    auto limit = field + (1000)*(1000);
    while (field < limit){
        *field++ = 0;
    }
}

int countfield(uint8_t* field){
    int retval{0};
    auto limit = field + (1000)*(1000);
    while (field < limit){
        if(*field > 1) ++retval;
        ++field;
    }
    return retval;
}

short getstep(int a, int b){
    return (a<b) - (a > b);
}