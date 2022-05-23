CXXFLAGS = -g --std=c++20
TESTFLAGS = --std=c++20
#CXX = clang++


main:  main.cpp lines.hpp points.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o main

lint: 
	clang-tidy *.cpp *.hpp

clean:
	rm -f main main.a main2 main.single test basin.o

test: tests/test.cpp lines.hpp points.hpp
	$(CXX) $(TESTFLAGS) tests/test.cpp -o tests/test