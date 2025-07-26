CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

all: main

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o main

main.o: main.cpp vec3.h 
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

.PHONY: clean
clean:
	rm -f main.o main