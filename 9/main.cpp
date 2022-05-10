#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <cmath>
#include <future>
#include <mutex>

// #include <format>

std::ifstream input;

static const unsigned int HEIGHT = 100;
static const unsigned int WIDTH = 100;
static std::vector<std::pair<int,int>> mins{};
std::mutex mutex_mins;
static std::atomic_ulong risklevel {0};
unsigned int field[HEIGHT][WIDTH];

void checkcorners();
void checkedges();
ulong findmins(int startrow, int endrow);

int main(int argc, char** argv){

    input.open("input");
    if (!input) return 1;

    {
        char inchar;
        int i{0},j{0};
        while(!input.eof()){
            input.get(inchar);
            if (inchar == '\n'){
                ++i;
                j = 0;
                continue;
            }
            field[i][j] = (inchar - 0x30);
            ++j;
        }
    }

    // Should be inclusive, so that you can make sure each row runs.
    // Will check the edges and corners with separate aysnc calls
    auto synclist = std::async(std::launch::async,findmins,1,33);
    auto sl2 = std::async(std::launch::async,findmins,33,66);
    auto sl3 = std::async(std::launch::async,findmins,66,99);
    auto sl4 = std::async(std::launch::async,checkedges);
    auto sl5 = std::async(std::launch::async,checkcorners);

    synclist.get();
    sl2.get();
    sl3.get();
    sl4.get();
    sl5.get();

    std::cout << risklevel << '\n';

    typedef std::pair<int,int> minpair; 
    std::sort(std::begin(mins),std::end(mins), [](minpair a, minpair b){return a.first < b.first;});

    for(auto& point : mins){
        std::cout <<  "(" << point.first <<  ", " << point.second << ")\n";
    }
    std::cout << "\n";
}

ulong findmins(int startrow, int endrow){
    auto& f = field;
        int val;
        for (int i = startrow;i<(endrow); ++i ){
            for(int j = 1; j < (WIDTH-1); ++j){
                val = f[i][j];
            
                if (f[i][j-1]> val && f[i][j+1] > val && f[i-1][j] > val && f[i+1][j] > val){
                    risklevel += (1 + val);
                    mutex_mins.lock();
                    mins.push_back(std::pair<int,int>{(i+1),(j+1)});
                    mutex_mins.unlock();
                }
            }
        }
        return risklevel;
}

void checkcorners(){
    using std::pair;
    int i,j,i2,j2,val;
    std::array<pair<int,int>,4> corners {pair(0,0),pair(0,WIDTH-1),pair(HEIGHT-1,0),pair(HEIGHT-1,WIDTH-1)};
    for(auto& x : corners){
        i = x.first;
        j = x.second;
        val = field[i][j];
        j2 = j + ((j==0)? 1 : -1);
        i2 = i + ((i==0)? 1 : -1);
        if (field[i][j2]> val && field[i2][j] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(std::pair<int,int>{(i+1),(j+1)});
            mutex_mins.unlock();
        } 
    }



}

void checkedges(){
    int val;
    int br{HEIGHT-1};
    int rc{WIDTH -1};

    // Top Edge
    for(int j = 1; j < (WIDTH - 1); ++j){
        val = field[0][j];
        if (field[0][j-1]> val && field[0][j+1] > val && field[1][j] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(std::pair<int,int>{(1),(j+1)});
            mutex_mins.unlock();
        } 
    }
    // Bottom Edge
    for(int j = 1; j < (WIDTH - 1); ++j){
        val = field[br][j];
        if (field[br][j-1]> val && field[br][j+1] > val && field[br-1][j] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(std::pair<int,int>{(br+1),(j+1)});
            mutex_mins.unlock();
        } 
    }
    // Left Edge
    for(int i = 1; i < (HEIGHT - 1); ++i){
        val = field[i][0];
        if (field[i-1][0] > val && field[i+1][0] > val && field[i][1] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(std::pair<int,int>{(i+1),(1)});
            mutex_mins.unlock();
        } 
    }

    // Right Edge
    for(int i = 1; i < (HEIGHT - 1); ++i){
        val = field[i][rc];
        if (field[i-1][rc] > val && field[i+1][rc] > val && field[i][rc-1] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(std::pair<int,int>{(i+1),(WIDTH)});
            mutex_mins.unlock();
        } 
    }
}