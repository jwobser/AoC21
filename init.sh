#!/bin/sh

touch main.cpp
mkdir tests
mkdir include
mkdir build
touch Makefile
touch tests/test.cpp
ln ../catch.hpp ./tests/catch.hpp

cat <<EOT >>main.cpp
#include <fstream>
#include <iostream>
#include <string>

std::ifstream input;
std::string buf;

int main(int argc, char** argv){
    input.open("input");
    input >> buf;
    std::cout << "First line of input:\n";
    std::cout << buf << std::endl;
}
EOT

cat <<EOT >>tests/test.cpp
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"

TEST_CASE("Check step function", "[Helper]"){
    bool a{true};
    REQUIRE(a);
    REQUIRE_FALSE(!a);
}
EOT

cat <<EOT >>Makefile
CXXFLAGS = -g --std=c++20
TESTFLAGS = --std=c++20
#CXX = clang++

main:  main.cpp
	\$(CXX) \$(CXXFLAGS) main.cpp -o build/main.a

clean:
	rm -rf build/*.a

test: tests/test.cpp
	\$(CXX) \$(TESTFLAGS) tests/test.cpp -o tests/test.a
EOT

git init
git add main.cpp tests/test.cpp Makefile
echo "tests/catch.hpp" >> .gitignore
echo ".gitignore" >> .gitignore
echo "*.a" >> .gitignore
echo "build/" >> .gitignore
git commit -m "Initial Commit"