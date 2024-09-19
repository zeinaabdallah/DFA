#include "Logger.h"

/**
 * @brief Constructs a Logger object and opens the log file.
 * 
 * This constructor creates a directory named "log" (if it does not already exist) and opens
 * a log file with a dynamically generated name based on the provided parameters.
 * 
 * @param numMessages The number of messages to be logged.
 * @param payloadLength The length of the payload in the messages.
 * @param channelWidth The width of the channel used for the messages.
 */
Logger::Logger(int numMessages, int payloadLength, int channelWidth) {
    mkdir("log", 0755);
    std::string fileName = generateLogFileName(numMessages, payloadLength, channelWidth);
    logFile.open(fileName, std::ios_base::app);  // Open log file in append mode
    if (!logFile.is_open()) {
        std::cerr << "Unable to open log file: " << fileName << std::endl;
    }
}

/**
 * @brief Destructor for the Logger class.
 * 
 * This destructor ensures that the log file is properly closed when the Logger object
 * goes out of scope or is destroyed.
 */
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

/**
 * @brief Logs a message with the given message ID and fragment ID.
 * 
 * This method writes the message ID, fragment ID, and the content of the message
 * in hexadecimal format to the log file.
 * 
 * @param messageId Identifier for the message being logged.
 * @param fragmentId Identifier for the fragment of the message.
 * @param message The content of the message to be logged.
 */
void Logger::logMessage(int messageId, int fragmentId, const std::vector<uint8_t>& message) {
    logFile << messageId << ", " << fragmentId << ", ";
    for (const auto& byte : message) {
        logFile << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << ' ';
    }
    logFile << std::endl;
}

/**
 * @brief Generates a log file name based on the parameters provided.
 * 
 * The log file name includes the number of messages, payload length, and channel width
 * to create a unique file name for each logging session.
 * 
 * @param numMessages The number of messages to be logged.
 * @param payloadLength The length of the payload in the messages.
 * @param channelWidth The width of the channel used for the messages.
 * @return A string representing the generated log file name.
 */
std::string Logger::generateLogFileName(int numMessages, int payloadLength, int channelWidth) {
    std::stringstream ss;
    ss << "log/messages_" << numMessages << "_" << payloadLength << "_" << channelWidth << ".log";
    return ss.str();
}
