CXXFLAGS = -g --std=c++20 -Wall -Wextra
TESTFLAGS = --std=c++20
#CXX = clang++

main:  main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o build/main.a

clean:
	rm -rf build/*.a

test: tests/test.cpp
	$(CXX) $(TESTFLAGS) tests/test.cpp -o tests/test.a
