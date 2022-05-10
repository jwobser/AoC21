#include <iostream>
#include <fstream> 

int main(int argc, char** argv){
    std::ifstream input{"depths"};

    if (!input) return 1;

    int window[3];
    int window_current {0}, window_prev;
    int depth, prev_depth{0};
    int count_increasing {0};

    // Load first window
    for (int i = 0; i < 3; ++i){
        input >> window[i];
        window_current += window[i];
    }

    int i{0};
    while(input){
        window_prev = window_current;
        window_current -= window[i];
        input >> window[i];
        window_current += window[i];
        i = (i + 1) % 3;
        if (window_current > window_prev) count_increasing++;
    }

    std::cout << count_increasing << std::endl;
    return 0;

}