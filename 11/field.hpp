#include <iostream>
#include <climits>

int flashneighbors(int,int);

static const int height{10};
static const int width{10};
static const int flashflag = INT_MAX & (1 << (8 * (sizeof(int))-2));
int field[height][width];

void printfield(){
    for(int i = 0, j = 0; i < height;){
        std::cout << field[i][j];
        if (++j == width){
            std::cout << '\n';
            ++i;
            j = 0;
        }
    }
    std::cout << '\n';
}

void incrementfield(){
    for(int i = 0, j = 0; i < height;){
        field[i][j] += 1;
        if (++j == width){
            ++i;
            j = 0;
        }
    }
}

void initfield(){
    for(int i = 0, j = 0; i < height;){
        field[i][j] = 0;
        if (++j == width){
            ++i;
            j = 0;
        }
    }
}

int handleflashing(){
    int count{0};
    int a;
    for (int i{0}, j{0};true;++j){
        if(j == width){
            ++i;
            j = 0;
            if(i == height) break;
        }
        a = field[i][j];
        if (a < 10) continue;
        if(a >= 10 && a < flashflag){
            ++count;
            field[i][j] |= flashflag;
            flashneighbors(i,j);
        }
    }
    return count;
}

int resetflashed(){
    int count{0};
    for(int i{0},j{0}; i < height;){
        if(field[i][j] >= flashflag){
            ++count;
            field[i][j] = 0;
        }
        if(++j == width){
            j = 0;
            ++i;
        }
    }
    return count;
}

int flashneighbors(int i, int j){
    // Lower and upper limits
    int yllim, yulim, xllim, xulim;
    int count{-1}; // number of neighbors flashed

    switch(i){
        case 0:
            yllim = 0;
            yulim = i + 1;
            break;
        case height - 1:
            yulim = height - 1;
            yllim = i - 1;
            break;
        default:
            yllim = i - 1;
            yulim = i + 1;
    }
    switch(j){
        case 0:
            xllim = 0;
            xulim = j + 1;
            break;
        case width - 1:
            xulim = width - 1;
            xllim = j - 1;
            break;
        default:
            xllim = j - 1;
            xulim = j + 1;
    }

    /* Pre-decrement target cell so we don't have to handle it
    as a special case in the loop */
    field[i][j] -= 1;

    // Iterate over all neighbors
    for(int y{yllim},x{xllim}; y < yulim || x <= xulim; ++x){
        if(x > xulim){
            x = xllim;
            ++y;
        }
        field[y][x] += 1;
        if (field[y][x] >= 10) ++count;
    }

    return count;
}