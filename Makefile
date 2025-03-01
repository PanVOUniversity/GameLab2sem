CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pthread -I.
LDFLAGS = -lgtest -lgtest_main -lpthread

SRC = main.cpp player.cpp unit.cpp field.cpp
OBJ = $(SRC:.cpp=.o)
LIB = game.a

TEST_SRC = tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: $(LIB) test

$(LIB): $(OBJ)
	ar rsv $@ $^

test: $(TEST_OBJ) $(LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(LIB) test