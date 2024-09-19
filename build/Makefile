# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Wpedantic -Wno-unused-result

INC_DIR = ../include
SRC_DIR = ../src
UNITTESTS_DIR = ../unittests

SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Message.cpp $(SRC_DIR)/Logger.cpp
UNITTEST_SRCS = $(UNITTESTS_DIR)/MessageTest.cpp $(SRC_DIR)/Message.cpp $(SRC_DIR)/Logger.cpp

# Output executable
TARGET = message-sender
TEST_TARGET = message-sender-test

LOG_DIR = log

# LIBS = -lgtest -lgtest_main -pthread

# Default rule to build the project
all: $(TARGET)

# Linking rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(TARGET) $(SRCS) 


test: $(UNITTEST_SRCS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(TEST_TARGET) $(UNITTEST_SRCS) -L/usr/lib/x86_64-linux-gnu -lgtest -lgtest_main -pthread 

# Clean rule to remove the generated executable
clean:
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)
	rm -rf $(LOG_DIR)

# Optional rule for debugging
debug: CXXFLAGS += -g
debug: $(TARGET)

.PHONY: all clean debug
