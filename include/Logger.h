#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <sys/stat.h> 

class Logger {
public:
    // Constructor that takes dynamic file name
    Logger(int numMessages, int payloadLength, int channelWidth);

    // Destructor to close the log file
    ~Logger();

    // Log a message with ID, fragment ID, and message content
    void logMessage(int messageId, int fragmentId, const std::vector<uint8_t>& message);

private:
    std::ofstream logFile;

    // Method to generate the log file name dynamically
    std::string generateLogFileName(int numMessages, int payloadLength, int channelWidth);
};

#endif // LOGGER_H
