#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/stdx/make_unique.hpp>

class USER_AUTH_CONNECTION {
public:
    USER_AUTH_CONNECTION(const std::string& mongodb_url);
    std::string findUser(const std::string& userEmail, const std::string& hashedPassword);

private:
    mongocxx::client client;
};

USER_AUTH_CONNECTION::USER_AUTH_CONNECTION(const std::string& mongodb_url) : client(mongodb_url) {
    // Initialize the MongoDB C++ driver
    mongocxx::instance inst{};
}

std::string USER_AUTH_CONNECTION::findUser(const std::string& userEmail, const std::string& hashedPassword) {
    try {
        // Access the "users" collection in the "your_database" database
        auto collection = client["your_database"]["users"];

        // Create a BSON document for the query
        auto filter = bsoncxx::builder::stream::document{}
            << "UserName" << userEmail
            << "password_sha256" << hashedPassword
            << bsoncxx::builder::stream::finalize;

        // Execute the query
        auto result = collection.find_one(filter.view());

        // Check if the user is found
        if (result) {
            // Extract and return the ObjectId as a string
            bsoncxx::document::element idElement = result->view()["_id"];
            if (idElement) {
                return idElement.get_oid().value.to_string();
            }
        }
    }
    catch (const std::exception& e) {
        // Handle exceptions and print error messages
        std::cerr << "Error: userName or password Incorrect" << e.what() << std::endl;
    }

    // Return an empty string if user not found or an error occurred
    return "";
}
