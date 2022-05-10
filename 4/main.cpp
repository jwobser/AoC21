#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>

#define HEIGHT 5
#define WIDTH 5

std::ifstream input;

struct Board{
    Board(){
        load();
    }

    bool isWinner(void) const{
        return checkrows() || checkcolumns();
    }

    void load(){
        for (int i = 0; i<HEIGHT; ++i){
            for (int j = 0; j < WIDTH; ++j){
                input >> numbers[i][j];
            }
        }
        // Discard Trailing Whitespace
        input >> std::ws;
    }

    void print() const{
        for (int i = 0; i<HEIGHT; ++i){
            for (int j = 0; j < WIDTH; ++j){
                std::cout << numbers[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    void printhits() const{
        for (int i = 0; i<HEIGHT; ++i){
            for (int j = 0; j < WIDTH; ++j){
                if (hits[i][j]){
                    std::cout << "X";
                } else {
                    std::cout << ".";
                };
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
 
    }

    void checkhit(int target){
        for (int i = 0; i<HEIGHT; ++i){
            for(int j = 0; j < WIDTH; ++j){
                if (numbers[i][j] == target){
                    hits[i][j] = true;
                }
            }
        }
    }

    int getNonDrawn(){
        int result{0};
        for (int i = 0; i<HEIGHT; ++i){
            for(int j = 0; j < WIDTH; ++j){
                if (!hits[i][j]){
                    result += numbers[i][j];
                }
            }
        }
        return result;
    }

    private:
        bool checkrows() const{
            int count{0};
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    if (hits[i][j]) ++count;
                }
                if (count == WIDTH){
                    return true;
                }
                count = 0;
            } 
            return false;
        }

        bool checkcolumns() const{
            int count{0};
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    if (hits[j][i]) ++count;
                }
                if (count == HEIGHT){
                    return true;
                }
                count = 0;
            } 
            return false;
        }

    bool hits[HEIGHT][WIDTH];
    unsigned short int numbers[HEIGHT][WIDTH];

};

void clearbuf(char* buf){
    for (int i = 0; i < 20; ++i){
        buf[i] = 0;
    }
}

int main(int argc, char** argv){
    input.open("input");
    if (!input) return 1;

    std::vector<int> draws;
    std::forward_list<Board> losers;

    char buf[20];
    clearbuf(buf);


    // Load draws
    int i {0};
    char next;
    int temp{0};
    bool load_next{true};
    while (load_next){
       input.get(buf[i]);
       switch (buf[i]){
           case '\n':
            load_next = false;

           case ',':
            buf[i] = 0;
            draws.emplace_back(atoi(buf));
            temp = atoi(buf); 
            // std::cout << "added " << temp << "\n";
            i = 0;
            break;

           default:
            ++i;
       }
    }

    while(!input.eof()){
        losers.emplace_front();
    }

    int numdraws{0}; 
    bool lastboard{false};


    for (auto target: draws){
        numdraws++;
        for(auto& x : losers){
            x.checkhit(target);
            if(lastboard && x.isWinner()){
                std::cout << "Second to last board: " << (target * x.getNonDrawn()) << "\n";
                x.print();
                x.printhits();
                std::cout << "Winning round: " << numdraws << "\n";
                std::cout << "Winning number: " << target << "\n";
            }
        }
        losers.remove_if([](const auto x){return x.isWinner();});
        if (!lastboard && std::distance(std::begin(losers), std::end(losers)) == 2) {
            lastboard = true;
        } 
    }


    std::cout << "Number of draws checked: " << numdraws << "\n";
    // std::cout << "Sum of Non-Hit tiles on last board: " << boards.end()->getNonDrawn() << std::endl;


    for(auto& x : losers){
        x.printhits();
    }
}