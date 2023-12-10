#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

class User {
public:
    // Constructor that takes the user's ID
    User(const std::string& ID);

    // Function to withdraw funds from the user's account
    void withdrawFunds(double amount);

    // Function to view the user's account balance
    void viewFunds() const;

    

private:
    std::string name;           // User's name
    std::string databaseID;     // User's ID used as a unique identifier in the database
    double accountBalance;      // User's account balance
    int age;                    // User's age

    // Helper function to get a MongoDB client
    mongocxx::client getMongoClient() const;

    // Helper function to query the user document from the database
    void queryDatabase();
    void updateDatabase() const;
};

// Constructor implementation
User::User(const std::string& ID) : databaseID(ID) {
    // Call the function to query the database when a new User object is created
    queryDatabase();
}

// Function to withdraw funds from the user's account
void User::withdrawFunds(double amount) {

    if (amount > 0 && amount <= accountBalance) {
        accountBalance -= amount;
        updateDatabase();
        std::cout << "Withdrawal successful. New balance: " << accountBalance << std::endl;
    }
    else {
        std::cout << "Invalid withdrawal amount or insufficient funds." << std::endl;
    }
}

// Function to view the user's account balance
void User::viewFunds() const {
    std::cout << "Account balance for user " << name << ": " << accountBalance << std::endl;
}

// Helper function to get a MongoDB client
mongocxx::client User::getMongoClient() const {
 
    // Example: return mongocxx::client(mongocxx::uri{"mongodb://localhost:27017"});
    return mongocxx::client{"FixME: ADD MONGODB CLIENT URL"};
}

// Helper function to query the user document from the database
void User::queryDatabase() {
    try {
        auto client = getMongoClient();
        auto collection = client["your_database"]["users"]; // Replace with your actual database and collection names

        // Create a BSON document for the query
        bsoncxx::builder::stream::document filter_builder;
        filter_builder << "database_id" << databaseID;

        // Execute the find query
        auto result = collection.find_one(filter_builder.view());

        // Check if the user is found
        if (result) {
            // Extract and set the user information
            bsoncxx::document::element nameElement = result->view()["name"];
            bsoncxx::document::element balanceElement = result->view()["account_balance"];
            if (nameElement && balanceElement) {
                name = nameElement.get_utf8().value.to_string();
                accountBalance = balanceElement.get_double();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error querying database: " << e.what() << std::endl;
    }
}
void User::updateDatabase() const {
    try {
        auto client = getMongoClient();
        auto collection = client["your_database"]["users"];

        // Create a BSON document to update the user information
        bsoncxx::builder::stream::document filter_builder, update_builder;
        filter_builder << "database_id" << databaseID;
        update_builder << "$set" << bsoncxx::builder::stream::open_document
            << "account_balance" << accountBalance
            << bsoncxx::builder::stream::close_document;

        // Execute the update query
        collection.update_one(filter_builder.view(), update_builder.view());
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating database: " << e.what() << std::endl;
    }
}

