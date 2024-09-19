#ifndef MESSAGE_SENDER_H
#define MESSAGE_SENDER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <cstdint>
#include "Logger.h"

// Constants for message structure
const int kHeaderSize = 8;
const int kFooterSize = 4;
const int kPreambleSize = 6;
const uint8_t kPreambleByte = 0x07;
const uint8_t kSFDByte = 0xD5;
const uint32_t kNonFragmentedFooter = 0xDDCCBBAA;
const uint32_t kFragmentedFooter = 0x44332211;

/**
 * @brief Class for constructing and sending messages.
 * 
 * The Message class is responsible for creating messages, both fragmented and non-fragmented,
 * and logging them. It validates input parameters and ensures that messages fit within the
 * specified channel width.
 */
class Message {
public:
    Message(int numMessages, int payloadLength, int channelWidth);
    void sendAllMessages();

private:
    int mNumMessages;
    int mPayloadLength;
    int mChannelWidth;
    Logger logger;

    void sendMessageById(int messageId);
    std::vector<uint8_t> constructNonFragmentedMessage(int messageId, const std::vector<uint8_t>& payload);
    std::vector<std::vector<uint8_t>> constructFragmentedMessage(int messageId, const std::vector<uint8_t>& payload, int payloadPerFragment);

};

#endif