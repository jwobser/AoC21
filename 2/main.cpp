#include <iostream>
#include <fstream> 

int main(int argc, char** argv){
    std::ifstream input{"commands.txt"};

    if (!input) return 1;

    std::string direction;
    int magnitude{0};
    int lines{0};

    int depth{0};
    int aim{0};
    int distance{0};

    while (!input.eof()){
        input >> direction >> magnitude;
        ++lines;
        std::cout << direction << " " << magnitude << "\n";
        
        switch (direction.front())
        {
        case 'u':
            aim -= magnitude;
            break;
        case 'd':
            aim += magnitude;
            break;
        case 'f':
            distance += magnitude;
            depth += (aim * magnitude);
            break;
        
        default:
            break;
        }
        // if(input.eof()) break;
    }

    std::cout << "Lines processed: \t" << lines << "\n";
    std::cout << "Distance: \t" << distance << "\n";
    std::cout << "Depth: \t" << depth << "\n";
    std::cout << "Product: \t" << (depth * distance) << std::endl;


    return 0;

}