#include "Message.h"

// Constructor for the Message class
/**
 * @brief Constructs a Message object with specified parameters.
 * 
 * @param numMessages Number of messages to be sent.
 * @param payloadLength Length of each message payload.
 * @param channelWidth Width of the channel for message transmission.
 * 
 * @throws std::invalid_argument if numMessages is less than or equal to 0,
 *         payloadLength is negative, or channelWidth is less than or equal to 0.
 * @throws std::invalid_argument if channelWidth is less than the combined
 *         size of header and footer, or if the payload length does not fit.
 */Message::Message(int numMessages, int payloadLength, int channelWidth)
    : mNumMessages(numMessages), mPayloadLength(payloadLength), mChannelWidth(channelWidth),
      logger(numMessages, payloadLength, channelWidth) {

    if (numMessages <= 0 || payloadLength < 0 || channelWidth <= 0 ) {
        throw std::invalid_argument("Error: Input must be greater than zero.");
    }

    if (channelWidth < kHeaderSize + kFooterSize) {
        throw std::invalid_argument("Error: Channel width must be greater than the combined header and footer size.");
    }

    if (channelWidth == kHeaderSize + kFooterSize && payloadLength > 0) {
        throw std::invalid_argument("Error: Payload length will not fit in the channel width.");
    }

}

/**
 * @brief Sends all messages specified by mNumMessages.
 */
void Message::sendAllMessages() {
    for (int id = 1; id <= mNumMessages; id++) {
        sendMessageById(id);
    }
}

/**
 * @brief Sends and logs a message identified by messageId.
 * 
 * This method does not perform actual sending; instead, it assumes that logging the message
 * is equivalent to "sending" it. If the message exceeds the channel width, it is fragmented.
 * 
 * @param messageId Identifier for the message being sent.
 */
void Message::sendMessageById(int messageId) {
    std::vector<uint8_t> payload(mPayloadLength, 0xFF);
    int totalMessageLength = kHeaderSize + mPayloadLength + kFooterSize;
    int payloadPerFragment = mChannelWidth - kHeaderSize - kFooterSize;

    if (totalMessageLength <= mChannelWidth) {
        std::vector<uint8_t> message = constructNonFragmentedMessage(messageId, payload);
        logger.logMessage(messageId, 1, message);
    } else {
        std::vector<std::vector<uint8_t>> fragments = constructFragmentedMessage(messageId, payload, payloadPerFragment);
        for (size_t fragmentId = 0; fragmentId < fragments.size(); fragmentId++) {
            logger.logMessage(messageId, fragmentId + 1, fragments[fragmentId]);
        }
    }
}

/**
 * @brief Constructs a non-fragmented message.
 * 
 * @param messageId Identifier for the message being constructed.
 * @param payload The payload data to include in the message.
 * @return A vector containing the constructed message.
 */
std::vector<uint8_t> Message::constructNonFragmentedMessage(int messageId, const std::vector<uint8_t>& payload) {
    // Initialize the message vector with the channel width and fill with zeros
    std::vector<uint8_t> message(mChannelWidth, 0);

    // Header
    std::memset(message.data(), kPreambleByte, kPreambleSize);  // Fill the preamble section with the pre-defined byte
    uint8_t SMDSxByte = (messageId - 1) % 4; // Ensure SMDSx byte is in the range [0, 3]
    message[kPreambleSize] = SMDSxByte; 
    message[kPreambleSize + 1] = kSFDByte; 

    // Payload
    std::memcpy(message.data() + kHeaderSize, payload.data(), mPayloadLength);

    // Footer
    uint32_t footer = kNonFragmentedFooter; // Fill the footer section with the pre-defined non-fragmented byte
    std::memcpy(message.data() + kHeaderSize + mPayloadLength, &footer, kFooterSize); 

    return message; 
}

/**
 * @brief Constructs a fragmented message.
 * 
 * @param messageId Identifier for the message being constructed.
 * @param payload The payload data to include in the message.
 * @param payloadPerFragment Maximum payload size for each fragment.
 * @return A vector of vectors, each representing a fragment of the message.
 */
std::vector<std::vector<uint8_t>> Message::constructFragmentedMessage(int messageId, const std::vector<uint8_t>& payload, int payloadPerFragment) {
    std::vector<std::vector<uint8_t>> fragments;

    // Calculate the number of fragments needed based on the total payload length
    int numFragments = (mPayloadLength + payloadPerFragment - 1) / payloadPerFragment;

    // Loop to create each fragment
    for (int fragmentId = 1; fragmentId <= numFragments; ++fragmentId) {
        std::vector<uint8_t> fragment(mChannelWidth, 0);

        // Calculate the starting offset for the current fragment's payload
        int offset = (fragmentId - 1) * payloadPerFragment;

        // Determine the size of the payload for the current fragment
        int currentPayloadSize = std::min(payloadPerFragment, mPayloadLength - offset);

        // Header
        std::memset(fragment.data(), kPreambleByte, kPreambleSize);
        uint8_t SMDSxByte = (messageId - 1) % 4;
        fragment[kPreambleSize] = SMDSxByte;

        if (fragmentId == 1) {
            fragment[kPreambleSize + 1] = kSFDByte; // First fragment gets the SFD byte
        } else {
            fragment[kPreambleSize + 1] = (fragmentId - 2) % 4; // Subsequent fragments get their ID, ensures it is in [0,3] range
        }

        // Payload
        std::memcpy(fragment.data() + kHeaderSize, payload.data() + offset, currentPayloadSize);

        // Footer
        // Determine footer type based on whether it is the last fragment
        uint32_t footer = (fragmentId == numFragments) ? kNonFragmentedFooter : kFragmentedFooter;  
        std::memcpy(fragment.data() + kHeaderSize + currentPayloadSize, &footer, kFooterSize);

        // Add fragment to the list of fragments
        fragments.push_back(fragment);
    }

    return fragments;
}
