#include <iostream>
#include <C:\Users\thoma\VS\BankingAPP\BankingApplication\BankingApplication\User.hpp>
#include <C:\Users\thoma\VS\BankingAPP\BankingApplication\BankingApplication\USERAUTH.hpp>

std::string sha256(const std::string& input) {

    // Create a SHA256_CTX object
    SHA256_CTX sha256Context;
    SHA256_Init(&sha256Context);


    // Update the context with the input data
    SHA256_Update(&sha256Context, input.c_str(), input.length());


    // Finalize the hash and retrieve the result
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256Context);


    // Convert the hash to a hex string
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return ss.str();
}


std::string* authenticateUser(std::string dbURL, std::string userName, std::string password) {

    USER_AUTH_CONNECTION Authenticator(dbURL);
    std::string* result = nullptr;
    result = &Authenticator.findUser(userName, sha256(password));
    return result;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <UserName> <Password> " << std::endl;
        return 1; // Exit with an error code if arguments are incorrect
    }
    const std::string dbURL = "FIX ME: SPIN UP AUTH DB INSTANCE AND GET URL";


     std::string* id = authenticateUser(dbURL, argv[0], argv[1]);

     if (id->empty()) {
         printf("FIXME(2): Add control flow if user not found in database");
         return -1;
     }

   
    // Create a User object with the provided arguments
    User user(id);

    // Example usage of withdraw_funds and view_funds
    user.withdraw_funds(500.0); // Withdraw $500 from the user's account
    user.view_funds(); // Display the updated account balance

    return 0; // Exit the program successfully
}