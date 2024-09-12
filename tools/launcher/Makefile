# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++03

# Libraries and includes
LIBS_LINUX = -lcurl -larchive
LIBS_MAC = -lcurl -larchive
LIBS_WINDOWS = -lcurl -larchive

# Output executable name
TARGET = wavesignal

# Source files
SRC = main.cpp

# Detect platform
UNAME_S := $(shell uname -s)

# Default target based on platform
all: $(TARGET)

# Linux target
ifeq ($(UNAME_S), Linux)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS_LINUX)
endif

# macOS target
ifeq ($(UNAME_S), Darwin)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS_MAC)
endif

# Windows target using MinGW
ifeq ($(OS), Windows_NT)
$(TARGET): $(SRC)
	x86_64-w64-mingw32-g++ $(CXXFLAGS) -o $(TARGET).exe $(SRC) $(LIBS_WINDOWS)
endif

# Clean up the generated files
clean:
	rm -f $(TARGET) $(TARGET).exe

# Run the program
run: all
	./$(TARGET)
