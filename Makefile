CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pthread -I.
LDFLAGS = -lgtest -lgtest_main -lpthread

OBJS = unit.o player.o field.o hill.o fortress.o functions.o inicialisation.o

all: test

test: tests.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o test

.PHONY: all clean