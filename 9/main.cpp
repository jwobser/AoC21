#include <fstream>
#include <iostream>
#include <vector>
#include <forward_list>
#include <cmath>
#include <future>
#include <mutex>
#include "../include/bench.hpp"
#include <string>
#include <unordered_set>
#include <algorithm>
#include "basin.hpp"
#include <cassert>


std::ifstream input;


const unsigned int HEIGHT = 100;
const unsigned int WIDTH = 100;

uint8_t idxneighbor {0}; 
std::array<std::vector<FloodPoint>, 2> neighbors;

static std::vector<Basin::Basin> mins{};
std::mutex mutex_mins;
static std::atomic_ulong risklevel {0};
unsigned int field[HEIGHT][WIDTH];

void checkcorners();
void checkedges();
ulong findmins(int startrow, int endrow);
[[nodiscard]] int checkneighbors(FloodPoint center);


std::unordered_set<FloodPoint> basinpoints{10'000};

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

    assert(risklevel == 512);
    std::cout << risklevel << '\n';

    for(auto& v: neighbors){
        v.reserve(200);
    }

    {
        auto& b = mins[0];
        neighbors[idxneighbor].push_back(FloodPoint(b.center));

        int added;
        while(neighbors[idxneighbor].size() > 0){
            for(auto& p : neighbors[idxneighbor]){
                added = checkneighbors(p);
                b.basinSize += added;
                std::cout << "Added " << added << " points to basin. \n";
            }
            std::cout << "Neigbors checked: " << neighbors[idxneighbor].size() << '\n';
            neighbors[idxneighbor].clear();
            idxneighbor ^= 1;
        }
        std::cout << "Basin size: " << b.basinSize << '\n';
    }



    for(auto& b: mins){
        neighbors[0].clear();
        neighbors[1].clear();
        neighbors[idxneighbor].push_back(FloodPoint(b.center));

        while(neighbors[idxneighbor].size() > 0){
            for(auto& p : neighbors[idxneighbor]){
                b.basinSize += checkneighbors(p);
            }
            neighbors[idxneighbor].clear();
            idxneighbor ^= 1;
        }
    }

    for (auto& b: mins){
        std::cout << "Basin Centered at:"\
        << "("<< b.center.x + 1 << ", " << b.center.y + 1 << ") - size: "\
        << b.basinSize << "\n";
    }

    std::array<int,3> largestbasins = {0,0,0};
    for (auto& b : mins){
        auto bsize = b.basinSize;
        if(bsize < largestbasins[0]) continue;

        if(bsize > largestbasins[2]){
            largestbasins[0] = largestbasins [1];
            largestbasins[1] = largestbasins[2];
            largestbasins[2] = bsize;
            continue;
        }

        if(bsize > largestbasins[1]){
            largestbasins[0] = largestbasins[1];
            largestbasins[1] = bsize;
            continue;
        } 
        largestbasins[0] = bsize;
    }

    int product{1};
    for (const auto& x: largestbasins){
        product *= x;
        std::cout << x << '\n';
    }

    std::cout << "Number of basins: " << mins.size() << '\n';
    std::cout << "Number of points in basins: " << basinpoints.size() << '\n';
    std::cout << "Product of largest basins: " << largestbasins[0] * largestbasins [1] * largestbasins[2] << '\n';
    assert(product >=1117344);
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
                    mins.push_back(Point{(j),(i)});
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
            mins.push_back(Point{(i),(j)});
            mutex_mins.unlock();
        } 
    }
}



void checkedges(){
    int val;
    constexpr int br{HEIGHT-1};
    constexpr int rc{WIDTH -1};

    // Top Edge
    for(int j = 1; j < rc; ++j){
        val = field[0][j];
        if (field[0][j-1]> val && field[0][j+1] > val && field[1][j] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(Point{(0),(j)});
            mutex_mins.unlock();
        } 
    }
    // Bottom Edge
    for(int j = 1; j < rc; ++j){
        val = field[br][j];
        if (field[br][j-1]> val && field[br][j+1] > val && field[br-1][j] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(Point{(br),(j)});
            mutex_mins.unlock();
        } 
    }
    // Left Edge
    for(int i = 1; i < br; ++i){
        val = field[i][0];
        if (field[i-1][0] > val && field[i+1][0] > val && field[i][1] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(Point{(i),(0)});
            mutex_mins.unlock();
        } 
    }

    // Right Edge
    for(int i = 1; i < br; ++i){
        val = field[i][rc];
        if (field[i-1][rc] > val && field[i+1][rc] > val && field[i][rc-1] > val){
            risklevel += (1 + val);
            mutex_mins.lock();
            mins.push_back(Point{(i),rc});
            mutex_mins.unlock();
        } 
    }
}

[[nodiscard]] int checkneighbors(FloodPoint center){
    int x = center.x;
    int y = center.y;
    int val = field[y][x];
    int right,left,above,below;
    int retval{0};
    if (center.up){
        above = field[y-1][x];
        if(above !=9 && above > val){
            if (basinpoints.insert(FloodPoint(x,y-1,FloodPoint::Origin::bottom)).second){
                //std::cout << "Point added to basin \n";
                neighbors[idxneighbor ^ 1].push_back(FloodPoint(x,y-1, FloodPoint::Origin::bottom));
                retval += 1;
            }
        }
    }
    if (center.down){
        below = field[y+1][x];
        if(below !=9 && below > val){
            if (basinpoints.insert(FloodPoint(x,y+1,FloodPoint::Origin::top)).second){
                //std::cout << "Point added to basin \n";
                neighbors[idxneighbor ^ 1].push_back(FloodPoint(x,y+1, FloodPoint::Origin::top));
                retval += 1;
            }
        }
    }
    if (center.left){
        left = field[y][x-1];
        if(left !=9 && left > val){
            if (basinpoints.insert(FloodPoint(x-1,y,FloodPoint::Origin::right)).second){
                //std::cout << "Point added to basin \n";
                neighbors[idxneighbor ^ 1].push_back(FloodPoint(x-1,y, FloodPoint::Origin::right));
                retval += 1;
            }
        }
    }
    if (center.right){
        right = field[y][x+1];
        if(right !=9 && right > val){
            if (basinpoints.insert(FloodPoint(x+1,y,FloodPoint::Origin::left)).second){
                //std::cout << "Point added to basin \n";
                neighbors[idxneighbor ^ 1].push_back(FloodPoint(x+1,y, FloodPoint::Origin::left));
                retval += 1;
            }
        }
    }

    return retval;
}