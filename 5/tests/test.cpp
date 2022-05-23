#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "../include/catch.hpp"

#include "../lines.hpp"
#include "../points.hpp"

short getstep(int a, int b){
    return (b>a) - (a > b);
}

TEST_CASE("Check step function", "[Helper]"){
    int a{10};
    int b{10};
    REQUIRE(getstep(a,b) == 0);
    a = 20;
    REQUIRE(getstep(a,b) == -1);
    a = 0;
    REQUIRE(getstep(a,b) == 1);
}

TEST_CASE("Check Vertical", "[Line]"){
    Point a{10,10};
    Point b{10,5}; 
    Line line{a,b};
    REQUIRE(line.isvertical());
}

TEST_CASE("Check Hoizontal", "[Line]"){
    Point a{10,10};
    Point b{5,10}; 
    Line line{a,b};
    REQUIRE(line.ishorizontal());
}

TEST_CASE("Check Diagonals", "[Line]"){
    Point a{10,10};
    Point b{15,15}; 
    Line line{a,b};
    REQUIRE(line.isdiagonal());
    REQUIRE_FALSE(line.ishorizontal());
    REQUIRE_FALSE(line.isvertical());
}

TEST_CASE("Correct Coverage", "[Line]"){
    Point a{1,1};
    Point b{1,3};
    Line line{a,b};

    REQUIRE(line.isvertical());
    int field[5][5] =\
    {{0,0,0,0,0},
     {0,0,0,0,0},
     {0,0,0,0,0},
     {0,0,0,0,0},
     {0,0,0,0,0} };

    int x = line.start.x;
     for(int y = line.start.y; y <= line.end.y; ++y){
         field[y][x] += 1;
     }

     REQUIRE(field[0][1] == 0);
     REQUIRE(field[1][1] == 1);
     REQUIRE(field[2][1] == 1);
     REQUIRE(field[3][1] == 1);
     REQUIRE(field[4][1] == 0);

     Point c{1,1};
     Point d{3,1};
     Line line2{c,d};

     REQUIRE(line2.ishorizontal());
     int y = line2.start.y;
     for(int x = line2.start.x; x <= line2.end.x; ++x){
         field [y][x] += 1;
     }


     REQUIRE(field[1][0] == 0);
     REQUIRE(field[1][1] == 2);
     REQUIRE(field[1][2] == 1);
     REQUIRE(field[1][3] == 1);
     REQUIRE(field[1][4] == 0);



}