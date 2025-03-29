CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -lgtest -lgtest_main -pthread

# Core game components
CORE_SRCS = player.cpp unit.cpp field.cpp hill.cpp fortress.cpp \
            functions.cpp getcommands.cpp inicialisation.cpp
CORE_OBJS = $(CORE_SRCS:.cpp=.o)

# Output library
CORE_LIB = libgamecore.a

# Test source
TEST_SRCS = tests.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Test executable
TEST_EXEC = game_tests

# Default target
all: $(CORE_LIB) $(TEST_EXEC)

# Build core game library
$(CORE_LIB): $(CORE_OBJS)
	ar rcs $@ $^

# Build test executable
$(TEST_EXEC): $(TEST_OBJS) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Pattern rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test target
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean build files
clean:
	rm -f $(CORE_OBJS) $(TEST_OBJS) $(CORE_LIB) $(TEST_EXEC)

.PHONY: all test clean