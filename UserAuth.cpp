#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

// Hold user data
struct User {
    std::string username;
    std::string password;
};

// Read user data from file
std::vector<User> readUserDataFromFile(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string username, password;

        while (file >> username >> password) {
            users.push_back({username, password});
        }

        file.close();
    }

    return users;
}

// Write user data to file
void writeUserDataToFile(const std::string& filename, const std::vector<User>& users) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const User& user : users) {
            file << user.username << " " << user.password << "\n";
        }

        file.close();
    }
}

// Check is username exists
bool doesUsernameExist(const std::vector<User>& users, const std::string& username) {
    for (const User& user : users) {
        if (user.username == username) {
            return true;
        }
    }

    return false;
}

// Register new user
void registerUser(std::vector<User>& users) {
    std::string username, password;

    std::cout << "\n=== Register ===\n";
    std::cout << "Enter a username: ";
    std::cin >> username;

    if (doesUsernameExist(users, username)) {
        std::cout << "Username already exists. Please choose a different username.\n";

        return;
    }

    std::cout << "Enter a password: ";
    std::cin >> password;

    users.push_back({username, password});
    writeUserDataToFile("users.txt", users);

    std::cout << "User registered successfully.\n";
}

// Authenticate User
bool authenticateUser(const std::vector<User>& users, const std::string& username, const std::string& password) {
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }

    return false;
}

// Header
void displayHeader(const std::string& title) {
    std::cout << "\033[1;36m"; // cyan text
    std::cout << std::setw(40) << std::right << title << std::endl;
    std::cout << "\033[0m"; // Reset text color
}

int main() {
    std::vector<User> users = readUserDataFromFile("users.txt");

    int choice;
    std::string username, password;

    do {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                std::cout << "\n=== Login ===\n";
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;

                if (authenticateUser(users, username, password)) {
                    displayHeader("Login successful!");
                } else {
                    displayHeader("Invalid username or password.");
                }
                break;
            case 3:
                displayHeader("Exiting...");
                break;
            default:
                displayHeader("Invalid choice. Please try again.");
        }
    } while (choice != 3);

    return 0;
}