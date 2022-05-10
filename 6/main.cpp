#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>

std::ifstream input;

void clearbuf(char* buf, int size){
    for (int i = 0; i < size; ++i){
        buf[i] = 0;
    }
}

void loadfish(unsigned long long* fish){
    char buf[20];
    clearbuf(buf, 20);
    int i {0};
    int temp{0};
    while (!input.eof()){
       input.get(buf[i]);
       switch (buf[i]){
           case '\n':

           case ',':
            buf[i] = 0;
            *(fish+atoi(buf)) += 1;
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
    int days{0};
    std::cout << "Please enter the number of days: ";
    std::cin >> days;

    unsigned long long lanternfish[7], newfish[3];
    for(int i=0; i < 7; ++i){
        lanternfish[i] = 0;
    }
    for(int i=0; i < 3; ++i){
        newfish[i] = 0;
    }

    // Load fish
    loadfish(lanternfish);
    for (int i = 0; i<7; ++i){
        std::cout << i << ": " << lanternfish[i] << "\n";
    }

    for(int j,i=0; i < (days - 0); ++i){
        j = i % 7;
        newfish[0] = newfish[1];        // fish joining day 6
        newfish[1] = newfish[2];        // day 7
        newfish[2] = lanternfish[j];    // newborns
        lanternfish[j] += newfish[0];
    }

    unsigned long long sum{0};
    for(int i = 0; i<7; ++i){
        sum += lanternfish[i];
    } 
    for(int i = 1; i<3; ++i){
        sum += newfish[i];
    } 

    std::cout << sum << std::endl;
}
