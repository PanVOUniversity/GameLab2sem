# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.
LDFLAGS := -lgtest -lgtest_main -pthread
BUILD_DIR := build
SRC_DIR := .

# Targets
MAIN_TARGET := game_executable
LIB_TARGET := libgame.a
TEST_TARGET := run_tests

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(filter-out $(SRC_DIR)/test.cpp $(SRC_DIR)/tests.cpp $(SRC_DIR)/main.cpp, $(SRCS))
TEST_SRC := $(SRC_DIR)/tests.cpp
MAIN_SRC := main.cpp

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
TEST_OBJ := $(BUILD_DIR)/tests.o
MAIN_OBJ := $(BUILD_DIR)/main.o

.PHONY: all clean test run

all: $(BUILD_DIR) $(LIB_TARGET) $(MAIN_TARGET)

test: $(BUILD_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Ensure build directory exists before compiling
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Create object files in build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Main library target
$(LIB_TARGET): $(OBJS)
	ar rcs $@ $^

# Test executable
$(TEST_TARGET): $(TEST_OBJ) $(LIB_TARGET)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Main executable
$(MAIN_TARGET): $(MAIN_OBJ) $(LIB_TARGET)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR) $(LIB_TARGET) $(TEST_TARGET) $(MAIN_TARGET)

# Explicit dependencies
$(BUILD_DIR)/cannon.o: cannon.h unit.h
$(BUILD_DIR)/field.o: field.h
$(BUILD_DIR)/fortress.o: fortress.h hill.h field.h
$(BUILD_DIR)/functions.o: functions.h field.h unit.h player.h
$(BUILD_DIR)/getcommands.o: getcommands.h player.h field.h functions.h
$(BUILD_DIR)/hill.o: hill.h field.h
$(BUILD_DIR)/inicialisation.o: inicialisation.h field.h hill.h player.h
$(BUILD_DIR)/player.o: player.h unit.h
$(BUILD_DIR)/unit.o: unit.h
$(BUILD_DIR)/tests.o: $(wildcard *.h)
$(BUILD_DIR)/AI.o: AI.h