# Message Sender

## Overview
The Message Sender project is designed to construct and send messages, both fragmented and non-fragmented, while logging the process. This project utilizes C++ and leverages Google Test for unit testing.

## Project Structure

| Directory/File       | Description                                         |
|----------------------|-----------------------------------------------------|
| `build/`             | Directory for build artifacts, including logs.     |
| `include/`           | Contains header files for the project.             |
| ├── `Logger.h`      | Header file for the Logger class.                  |
| └── `Message.h`     | Header file for the Message class.                 |
| `src/`              | Contains source files for the project.             |
| ├── `Logger.cpp`    | Implementation of the Logger class.                 |
| ├── `Message.cpp`   | Implementation of the Message class.                |
| └── `main.cpp`      | Main entry point of the application.                |
| `unittests/`        | Contains unit tests for the project.               |
| └── `MessageTest.cpp`| Unit tests for the Message class using Google Test.|
| `Makefile`          | Makefile to build the project and run tests.       |
| `README.md`         | Documentation for the project.                      |


## Files
- **include/Logger.h**: Header file for the Logger class that manages logging functionality.
- **include/Message.h**: Header file for the Message class responsible for message construction and sending.
- **src/Logger.cpp**: Implementation of the Logger class.
- **src/Message.cpp**: Implementation of the Message class.
- **src/main.cpp**: Main entry point of the application.
- **unittests/MessageTest.cpp**: Unit tests for the Message class using Google Test.

## Makefile
The provided Makefile allows you to build the project and run unit tests. Below are the key targets:

- **all**: Builds the main executable (`message-sender`).
- **test**: Compiles and runs unit tests (`message-sender-test`).
- **clean**: Removes generated executables and log directory.
- **debug**: Builds the project with debugging information.

### Logging
The application will generate log files in the `build/log` directory. Each log file will contain the messages that are "sent" (logged) during execution.

### Usage
1. **Build the project**:
   ```bash
   make
2. **Run the executable**:
   ```bash
    ./message-sender

3. **Run tests**:
   ```bash
    make test
    ./message-sender-test

4. **Clean the build**:
   ```bash
    make clean

## Requirements
- C++17 compatible compiler (e.g., g++)
- Google Test framework
