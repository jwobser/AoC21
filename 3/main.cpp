#include <iostream>
#include <fstream> 
#include <bitset>
// #include <array>
#include <list>
#include <string>

namespace lifesupport{
    enum system{OXYGEN, CO2};
}

// *** Prototypes ***
int chartoi(char*);
unsigned int countbits(std::list<std::bitset<12>> list, int bitPos);
void loadList(void);
void filterList(lifesupport::system type);
void printlist();

// *** Globals ***
int list_len{0};
std::ifstream input;
std::list<std::bitset<12>> values;
bool debugging = false;


int main(int argc, char** argv){
    input.open("input");

    if (argc > 1){
        std::string arg1 (argv[1]);
        if (arg1.compare("-v") == 0){
            debugging = true;
        }
    }

    if (!input) return 1;
    
    // Read values into array
    loadList();
    filterList(lifesupport::OXYGEN);

    printlist();


    int oxygen_rating = values.begin()->to_ulong();

    loadList();
    filterList(lifesupport::CO2);

    int CO2_rating = values.begin()->to_ulong();
    printlist();

    std::cout << "Result: " << (oxygen_rating * CO2_rating) << std::endl;


}


int chartoi(char* c){
    return (*c - 0x30);
}

void printlist(){
    if (debugging){
        for (auto x : values){
            std::cout << x << "\n";
        }
    }
}

void filterList(lifesupport::system type){
    for(int i = 0; i < 12; ++i){
        if (list_len == 1) return;
        int bCount = countbits(values, i);
        int mostCommon;
        if (bCount == (list_len / 2) && !(list_len & 1)){
            mostCommon = 1;
        } else { 
            mostCommon = bCount > (list_len / 2);
        }
        int leastCommon = !mostCommon;
        // std::cout << "Least common bit: " << leastCommon << "\t Most Common: " << mostCommon << "\n";
        if(type == lifesupport::OXYGEN){
            values.remove_if([i, mostCommon](auto x){return (list_len > 1)&& (x[11-i]!=mostCommon);});
        } else if (type == lifesupport::CO2){
            values.remove_if([i, leastCommon](auto x){return (list_len > 1)&& (x[11-i]!=leastCommon);});
        }
        std::cout << "List Length: " << list_len << "\n";

        if (debugging) printlist();
    }
}

void loadList(void){
    values.clear();
    list_len = 0;
    input.seekg(input.beg);
   char buf[13];
    std::bitset<12> bitsIn{0};
    while(!input.eof()){
        input.getline(buf, 13, '\n');
        for(int j = 0; j<12; ++j){
            bitsIn[11-j] = chartoi(&buf[j]);
        }
        values.emplace_back(bitsIn);
        ++list_len;
    }
}

unsigned int countbits(std::list<std::bitset<12>> list, int bitPos){
    list_len = 0;
    int count {0};
    for (auto x : list){
        if(x[11-bitPos]) ++count;
        ++list_len;
    }
    return count;
}