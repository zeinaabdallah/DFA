#include <gtest/gtest.h>
#include "Message.h"

// Base test class for Message tests
class MessageTest : public ::testing::Test {
};

// Test case to check that valid input without fragmentation does not throw exceptions
TEST(MessageSenderTest, ValidInputWNoFragmentation) {
    EXPECT_NO_THROW({
        Message sender(5, 6, 20);
        sender.sendAllMessages();
    });
}

// Test case to check that valid input with fragmentation does not throw exceptions
TEST(MessageSenderTest, ValidInputWFragmentation) {
    EXPECT_NO_THROW({
        Message sender(1, 5, 15);
        sender.sendAllMessages();
    });
}

// Test case to check that a constructor with zero messages throws an exception
TEST(MessageSenderTest, ZeroNumMessages) {
    EXPECT_THROW({
        Message sender(0, 10, 20); // Zero messages
    }, std::invalid_argument);
}

// Test case to check that a small channel width throws an exception
TEST(MessageSenderTest, SmallChannelWidth) {
    EXPECT_THROW({
        Message sender(5, 10, 5); // Channel width not greater than header + footer
    }, std::invalid_argument);
}

// Test case to check that an empty payload with just enough channel width does not throw exceptions
TEST(MessageSenderTest, EmptyPayloadJustEnougChannel) {
    Message sender(1, 0, 12);
    EXPECT_NO_THROW(sender.sendAllMessages());
}

// Test case to check that a payload with just enough channel width throws an exception
TEST(MessageSenderTest, PayloadJustEnougChannel) {
    EXPECT_THROW({    
        Message sender(1, 10, 12);
    }, std::invalid_argument);
}

// Test case to check that large values for messages and payload do not throw exceptions
TEST(MessageSenderTest, LargeValues) {
    Message sender(10000, 1000, 1024);
    EXPECT_NO_THROW(sender.sendAllMessages());
}

// Test case to check that a negative payload value throws an exception
TEST(MessageSenderTest, NegativeInput) {
    EXPECT_THROW({    
        Message sender(2, -1, 14);
    }, std::invalid_argument);
}

// Main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
