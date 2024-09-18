# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Wpedantic -Wno-unused-result

INC_DIR = ../include
# Source files and directories
SRC_DIR = ../src
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MessageSender.cpp $(SRC_DIR)/Logger.cpp

# Output executable
TARGET = message-sender

# Default rule to build the project
all: $(TARGET)

# Linking rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(TARGET) $(SRCS)

# Clean rule to remove the generated executable
clean:
	rm -f $(TARGET)

# Optional rule for debugging
debug: CXXFLAGS += -g
debug: $(TARGET)

.PHONY: all clean debug
