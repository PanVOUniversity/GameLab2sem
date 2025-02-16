PROJECT = game

LIBPROJECT = $(PROJECT).a

TESTPROJECT = test

CXX = g++

A = ar

AFLAGS = rsv

CCXFLAGS = -I. -std=c++17 -Wall -Wextra -g -pthread

LDXXFLAGS = $(CCXFLAGS) -L. -l:$(LIBPROJECT)

LDGTESTFLAGS = $(LDXXFLAGS) -lgtest -lgtest_main -lpthread

DEPS = $(wildcard *.h)

OBJ = main.o

# Test object files (just the test file for now)
TEST-OBJ = tests.o

.PHONY: default

default: all

# Rule to compile .cpp files to .o files
%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CCXFLAGS)

# Create static library
$(LIBPROJECT): $(OBJ)
	$(A) $(AFLAGS) $@ $^

# Build the test executable
$(TESTPROJECT): $(LIBPROJECT) $(TEST-OBJ)
	$(CXX) -o $@ $(TEST-OBJ) $(LDGTESTFLAGS)

# Build the test executable without running it
build-tests: $(TESTPROJECT)

# Run the tests
run-tests: $(TESTPROJECT)
	./$(TESTPROJECT)

# Build all targets (excluding running tests)
all: $(LIBPROJECT) build-tests

# Clean up object files
clean:
	rm -f *.o

# Clean up all build artifacts
cleanall: clean
	rm -f $(LIBPROJECT)
	rm -f $(TESTPROJECT)