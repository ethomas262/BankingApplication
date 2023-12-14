# Banking Application

## Overview
This C++ program is a simple Banking Application that demonstrates user authentication, account management, and basic transaction functionalities. It utilizes SHA256 hashing for password security and interacts with a hypothetical user authentication database.

## Prerequisites
- C++ compiler
- OpenSSL library for SHA256 hashing (link against `-lssl -lcrypto`)
- mongocxx driver for c++ 

## How to Use

1. **Compile the Code:**
   - Ensure you have a C++ compiler installed.
   - Link against the OpenSSL library during compilation (`-lssl -lcrypto`).
   - Compile the program.

2. **Run the Program:**
   - Execute the compiled binary, providing a username and password as command-line arguments.

3. **Program Usage:**
   - The program checks for the correct number of command-line arguments.
   - The authentication process is handled by the `authenticateUser` function, which interacts with a user authentication database.
   - Upon successful authentication, a `User` object is created, and example transactions (`withdraw_funds` and `view_funds`) are performed.

4. **Note:**
   - The `dbURL` in the code needs to be updated with the correct authentication database instance URL.
   - Ensure OpenSSL library is installed for SHA256 hashing.

## Important Points
- The code uses SHA256 hashing for password security.
- The authentication process is done through the `authenticateUser` function, which communicates with a user authentication database.
- User account management and transactions are exemplified through the `User` class.

## Dependencies
- C++ Standard Library
- OpenSSL Library (for SHA256 hashing)

## Additional Notes
- The authentication database URL in the code needs to be updated (`dbURL` variable).
- This code is a basic demonstration and should not be used in a production environment without further security considerations.

## License


## Acknowledgments
- The program uses SHA256 hashing for secure password handling.
- The structure of the code allows for further expansion and integration with a complete banking system.

