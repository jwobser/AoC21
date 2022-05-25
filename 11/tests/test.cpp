#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "../field.hpp"

TEST_CASE("Init Fields", "[Init]"){
    field[0][0] = 1;
    field[0][1] = 2;
    initfield();
    REQUIRE(field[0][0] == 0);
    REQUIRE(field[0][1] == 0);
}

TEST_CASE("Increment Fields", "[Field]"){
    initfield();
    field[0][2] = 2;
    field[1][1] = 1;
    incrementfield();
    field[0][2] = 3;
    field[1][1] = 2;
}

TEST_CASE("Handle Flashing", "[Field]"){
    initfield();
    field[0][0] = 10;
    field[0][1] = 10;
    incrementfield();
    int flashCount = handleflashing();
    REQUIRE(flashCount == 2);
}

TEST_CASE("Increment Neighbors", "[Flash]"){
    initfield();

    SECTION("Top Edge"){
        const int row{0}, column{5};
        field[row][column] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 0);
        // Make sure didn't modify self
        REQUIRE(field[row][column] == 10);
        // Check neighbors
        REQUIRE(field[row][column - 1] == 1);
        REQUIRE(field[row + 1][column - 1] == 1);
        REQUIRE(field[row + 1][column + 1] == 1);
        REQUIRE(field[row + 1][column + 1] == 1);
    }

    SECTION("Bottom Edge"){
        const int row{9}, column{5};
        field[row][column] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 0);
        // Make sure didn't modify self
        REQUIRE(field[row][column] == 10);
        // Check neighbors
        REQUIRE(field[row][column - 1] == 1);
        REQUIRE(field[row - 1][column - 1] == 1);
        REQUIRE(field[row - 1][column + 1] == 1);
        REQUIRE(field[row - 1][column + 1] == 1);
        REQUIRE(field[row - 2][column] == 0);
    }

    SECTION("Left Edge"){
        const int row{5}, column{0};
        field[row][column] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 0);
        // Make sure didn't modify self
        REQUIRE(field[row][column] == 10);
        // Check neighbors
        REQUIRE(field[row][column + 1] == 1);
        REQUIRE(field[row - 1][column] == 1);
        REQUIRE(field[row - 1][column + 1] == 1);
        REQUIRE(field[row - 1][column + 1] == 1);
    }

    SECTION("Right Edge"){
        const int row{5}, column{9};
        field[row][column] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 0);
        // Make sure didn't modify self
        REQUIRE(field[row][column] == 10);
        // Check neighbors
        REQUIRE(field[row - 1][column] == 1);
        REQUIRE(field[row - 1][column - 1] == 1);
        REQUIRE(field[row + 1][column] == 1);
    }

    SECTION("Center"){
        const int row{5}, column{5};
        field[row][column] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 0);
        // Make sure didn't modify self
        REQUIRE(field[row][column] == 10);
        // Check neighbors
        REQUIRE(field[row - 1][column] == 1);       // Up
        REQUIRE(field[row - 1][column - 1] == 1);   // Left
        REQUIRE(field[row + 1][column] == 1);       // Down
        REQUIRE(field[row][column + 1] == 1);       // Right
        REQUIRE(field[row - 1][column + 1] == 1);   // Diagonal
    }

    SECTION("Multiple"){
        const int row{5}, column{5};
        field[row][column] = 10;
        field[row][column + 1] = 10;
        field[row][column - 1] = 10;
        int count = flashneighbors(row,column);
        REQUIRE(count == 2);
    }
}

TEST_CASE("Set Flash Flag","[Flash]"){
    initfield();
    const int row{5}, column{5};
    field[row][column] = 10;
    field[row][column + 1] = 10;
    int count = handleflashing();
    REQUIRE(count == 2);
    REQUIRE(field[row][column] == (11 | flashflag));
    REQUIRE(field[row][column+1] == (11 | flashflag));
}

TEST_CASE("Reset Flashed", "[Flash]"){
    initfield();
    field[0][0] = flashflag;
    field[0][1] = flashflag;
    resetflashed();
    REQUIRE(field[0][0] == 0);
    REQUIRE(field[0][1] == 0);
}

TEST_CASE("Flashing", "[Flash]"){
    initfield();
    field[0][0] = 10;
    field[0][1] = 10;
    handleflashing();
    CHECK(field[0][0] >= flashflag);
    int count = resetflashed();
    REQUIRE(count == 2);
    REQUIRE(field[0][0] == 0);
    REQUIRE(field[0][1] == 0);
}

TEST_CASE("100 Flash Test", "[Flash]"){
    int flashes{0};
    initfield();
    for(int i{0}; i < 9; ++i ){
        flashes += step();
    }
    REQUIRE(flashes == 0);
    flashes += step();
    REQUIRE(flashes == 100);
}

TEST_CASE("5 Flash Test", "[Flash]"){
    int flashes{0};
    initfield();
    field[5][4] = 9;
    field[5][5] = 9;
    field[5][6] = 9;
    field[4][5] = 9;
    field[6][5] = 9;
    REQUIRE(flashes == 0);
    flashes += step();
    REQUIRE(flashes == 5);
    REQUIRE(field[5][5] == 0);
    REQUIRE(field[0][0] == 1);
    REQUIRE(field[4][4] == 4);
    REQUIRE(field[3][5] == 2);
}

TEST_CASE("Example Problem", "[Flash]"){
    int flashes{0};
    initfield();
    int field2[][10] = {
    {5,4,8,3,1,4,3,2,2,3},
    {2,7,4,5,8,5,4,7,1,1},
    {5,2,6,4,5,5,6,1,7,3},
    {6,1,4,1,3,3,6,1,4,6},
    {6,3,5,7,3,8,5,4,7,8},
    {4,1,6,7,5,2,4,6,4,5},
    {2,1,7,6,8,4,1,7,2,1},
    {6,8,8,2,8,8,1,1,3,4},
    {4,8,4,6,8,4,8,5,5,4},
    {5,2,8,3,7,5,1,5,2,6}
    };

    for(int i{0}; i < 100; ++i){
        field[0][i] = field2[0][i];
    }

    for(int i{0}; i < 100; ++i){
        flashes += step();
    }

    int field3[][10] = {
    {0,3,9,7,6,6,6,8,6,6},
    {0,7,4,9,7,6,6,9,1,8},
    {0,0,5,3,9,7,6,9,3,3},
    {0,0,0,4,2,9,7,8,2,2},
    {0,0,0,4,2,2,9,8,9,2},
    {0,0,5,3,2,2,2,8,7,7},
    {0,5,3,2,2,2,2,9,6,6},
    {9,3,2,2,2,2,8,9,6,6},
    {7,9,2,2,2,8,6,8,6,6},
    {6,7,8,9,9,9,8,7,6,6}
    };

    bool matches{true};
    for(int i{0}; i < 100; ++i){
        if(field[0][i] != field3[0][i]){
            matches = false;
        }
    }

    REQUIRE(matches);

    REQUIRE(flashes == 1656);

}