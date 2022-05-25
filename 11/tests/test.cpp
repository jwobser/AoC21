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