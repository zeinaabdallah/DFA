#include "Message.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>

// Function to validate if a given input string represents a valid positive number
bool isValidNumber(const char* input) {
    std::string str(input);
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

/**
 * The main function of the program.
 *
 * @param argc the number of command line arguments
 * @param argv an array of command line arguments
 *
 * @return an integer indicating the success or failure of the program
 *
 * @throws std::invalid_argument if the command line arguments are invalid
 */
int main(int argc, char* argv[]) {
    try {
        if (argc != 4) {
            throw std::invalid_argument("Usage: <numMessages> <messageLength> <channelWidth>");
        }

        // Validate if inputs are valid numbers
        if (!isValidNumber(argv[1]) || !isValidNumber(argv[2]) || !isValidNumber(argv[3])) {
            throw std::invalid_argument("Error: All inputs must be numeric and positive values.");
        }

        // Convert inputs to integers
        int numMessages = std::atoi(argv[1]);
        int messageLength = std::atoi(argv[2]);
        int channelWidth = std::atoi(argv[3]);

        Message sender(numMessages, messageLength, channelWidth);
        sender.sendAllMessages();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1; // Return a non-zero value to indicate failure
    }

    return 0;
}