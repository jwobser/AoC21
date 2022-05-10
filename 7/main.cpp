#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <cmath>

std::ifstream input;

void clearbuf(char* buf, int size){
    for (int i = 0; i < size; ++i){
        buf[i] = 0;
    }
}

int fuelcost(int, int);

void loadfish(std::vector<int>& positions){
    char buf[10];
    clearbuf(buf, 10);
    int i {0};
    int temp{0};
    while (!input.eof()){
       input.get(buf[i]);
       switch (buf[i]){
           case '\n':

           case ',':
            buf[i] = 0;
            positions.push_back(atoi(buf));
            clearbuf(buf, 10);
            i = 0;
            break;

           default:
            ++i;
       }
    }
}

int main(int argc, char** argv){
    input.open("input");
    if (!input) return 1;

    std::vector<int> positions;
    loadfish(positions);

    int min, max;
    min = max = positions[0];
    for(auto& x : positions){
        if (x < min) min = x;
        if (x > max) max = x;
    }


    long distance, mindistance{__LONG_MAX__};
    for(int target = min; target < max; target++){
        distance = 0;
        for(auto& x: positions){
            distance += fuelcost(x, target);
        }
        if (distance < mindistance){
            mindistance = distance;
        } else {
            break;
        }

    }

    std::cout << mindistance << std::endl;
}

int fuelcost(int pos, int target){
    int distance = abs(target - pos);
    return ((distance + 1) * distance) / 2; 
}