# Makefile for basic-text-rng-game
# C++ Text-based RPG Game with Combat System

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -pthread

# Source files
SOURCES = game.cpp classes.cpp combat.cpp utils.cpp
# Header files
HEADERS = classes.h combat.h utils.h
# Object files
OBJECTS = $(SOURCES:.cpp=.o)
# Executable
EXECUTABLE = game

# Phony targets
.PHONY: all build clean run help

# Default target
all: build

# Build the executable
build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Run the game
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Rebuild everything
rebuild: clean build

# Display help information
help:
	@echo "Available targets:"
	@echo "  make build      - Compile the game (default)"
	@echo "  make run        - Compile and run the game"
	@echo "  make clean      - Remove compiled files"
	@echo "  make rebuild    - Clean and rebuild the game"
	@echo "  make help       - Display this help message"
