CXXFLAGS = -g --std=c++20
#CXX = clang++

basin.o: basin.cpp basin.hpp
	$(CXX) $(CXXFLAGS) -c  basin.cpp -o basin.o

main: basin.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp basin.o -o main

lint: 
	clang-tidy *.cpp *.hpp

clean:
	rm -f main main.a main2 main.single test basin.o