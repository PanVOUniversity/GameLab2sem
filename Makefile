# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.
LDFLAGS := -lgtest -lgtest_main -pthread
BUILD_DIR := build
SRC_DIR := code

# Targets
MAIN_TARGET := game_executable
LIB_TARGET := libgame.a
TEST_TARGET := run_tests

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(filter-out $(SRC_DIR)/test.cpp $(SRC_DIR)/tests.cpp $(SRC_DIR)/main.cpp, $(SRCS))
TEST_SRC := $(SRC_DIR)/tests.cpp
MAIN_SRC := $(SRC_DIR)/main.cpp

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
	rm -rf $(BUILD_DIR) $(LIB_TARGET) $(TEST_TARGET) $(MAIN_TARGET) game.a

# Explicit dependencies
$(BUILD_DIR)/cannon.o: $(SRC_DIR)/cannon.cpp $(SRC_DIR)/cannon.h $(SRC_DIR)/unit.h
$(BUILD_DIR)/field.o: $(SRC_DIR)/field.cpp $(SRC_DIR)/field.h
$(BUILD_DIR)/fortress.o: $(SRC_DIR)/fortress.cpp $(SRC_DIR)/fortress.h $(SRC_DIR)/hill.h $(SRC_DIR)/field.h
$(BUILD_DIR)/functions.o: $(SRC_DIR)/functions.cpp $(SRC_DIR)/functions.h $(SRC_DIR)/field.h $(SRC_DIR)/unit.h $(SRC_DIR)/player.h
$(BUILD_DIR)/getcommands.o: $(SRC_DIR)/getcommands.cpp $(SRC_DIR)/getcommands.h $(SRC_DIR)/player.h $(SRC_DIR)/field.h $(SRC_DIR)/functions.h
$(BUILD_DIR)/hill.o: $(SRC_DIR)/hill.cpp $(SRC_DIR)/hill.h $(SRC_DIR)/field.h
$(BUILD_DIR)/inicialisation.o: $(SRC_DIR)/inicialisation.cpp $(SRC_DIR)/inicialisation.h $(SRC_DIR)/field.h $(SRC_DIR)/hill.h $(SRC_DIR)/player.h
$(BUILD_DIR)/player.o: $(SRC_DIR)/player.cpp $(SRC_DIR)/player.h $(SRC_DIR)/unit.h
$(BUILD_DIR)/unit.o: $(SRC_DIR)/unit.cpp $(SRC_DIR)/unit.h
$(BUILD_DIR)/tests.o: $(SRC_DIR)/tests.cpp $(wildcard $(SRC_DIR)/*.h)
$(BUILD_DIR)/AI.o: $(SRC_DIR)/AI.cpp $(SRC_DIR)/AI.h
$(BUILD_DIR)/archer.o: $(SRC_DIR)/archer.cpp $(SRC_DIR)/archer.h
$(BUILD_DIR)/bombedfield.o: $(SRC_DIR)/bombedfield.cpp $(SRC_DIR)/bombedfield.h
$(BUILD_DIR)/bombspell.o: $(SRC_DIR)/bombspell.cpp $(SRC_DIR)/bombspell.h
$(BUILD_DIR)/burnedfield.o: $(SRC_DIR)/burnedfield.cpp $(SRC_DIR)/burnedfield.h
$(BUILD_DIR)/cursespell.o: $(SRC_DIR)/cursespell.cpp $(SRC_DIR)/cursespell.h
$(BUILD_DIR)/engineer.o: $(SRC_DIR)/engineer.cpp $(SRC_DIR)/engineer.h
$(BUILD_DIR)/fireballspell.o: $(SRC_DIR)/fireballspell.cpp $(SRC_DIR)/fireballspell.h
$(BUILD_DIR)/hospitalfield.o: $(SRC_DIR)/hospitalfield.cpp $(SRC_DIR)/hospitalfield.h
$(BUILD_DIR)/infantry.o: $(SRC_DIR)/infantry.cpp $(SRC_DIR)/infantry.h
$(BUILD_DIR)/manaminefield.o: $(SRC_DIR)/manaminefield.cpp $(SRC_DIR)/manaminefield.h
$(BUILD_DIR)/morogspell.o: $(SRC_DIR)/morogspell.cpp $(SRC_DIR)/morogspell.h
$(BUILD_DIR)/priest.o: $(SRC_DIR)/priest.cpp $(SRC_DIR)/priest.h
$(BUILD_DIR)/shieldedfield.o: $(SRC_DIR)/shieldedfield.cpp $(SRC_DIR)/shieldedfield.h
$(BUILD_DIR)/spell.o: $(SRC_DIR)/spell.cpp $(SRC_DIR)/spell.h
$(BUILD_DIR)/teleportspell.o: $(SRC_DIR)/teleportspell.cpp $(SRC_DIR)/teleportspell.h