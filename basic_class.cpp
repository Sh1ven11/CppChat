#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <ctime>

using namespace std;

class Message {
public:
    string sender;
    string receiver;
    string content;
    string timestamp;

    Message(string s, string r, string c, string t) :
        sender(s), receiver(r), content(c), timestamp(t) {}
};

class User {
private:
    string password;

    bool isValid(string pass) {
        if (pass.length() < 6) {
            cout << "Password must be at least 6 characters long." << endl;
            throw invalid_argument("Invalid password");
            return false;
        }
        return !pass.empty();
    }

public:
    string username;
    vector<Message> inbox;
    vector<Message> outbox;
    User() = default; 

    User(string uname, string pass) : username(uname) {
        if (isValid(pass)) {
            password = pass;
        } else {
            throw invalid_argument("Invalid password");
        }
    }

    bool login(string pass) {
        if (pass == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Login failed. Incorrect password." << endl;
            return false;
        }
    }
};

int main() {
    int input = 0;
    unordered_map<string, User> users;

    while (input != 3) {
        cout << "1. New User\n2. Login\n3. Exit" << endl;
        cin >> input;

        if (input == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            try {
                User newUser(username, password);
                users[username] = newUser;
                cout << "User created successfully!" << endl;
            } catch (const invalid_argument &e) {
                cout << "User NOT created successfully: " << e.what() << endl;
            }
        } else if (input == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (users.find(username) == users.end()) {
                cout << "User not found. Please register first." << endl;
                continue;
            }

            User &user = users[username];
            if (user.login(password)) {
                cout << "Welcome, " << user.username << "!" << endl;
                int action = 0;
                while (action != 3) {
                    cout << "1. Send Message\n2. View Inbox\n3. Logout" << endl;
                    cin >> action;

                    if (action == 1) {
                        string receiver, content, timestamp;
                        cout << "Enter receiver username: ";
                        cin >> receiver;
                        cout << "Enter message content: ";
                        cin.ignore(); // Clear the newline character from the input buffer
                        getline(cin, content);
                        std::time_t now = std::time(nullptr);
                        timestamp = std::ctime(&now);
                        timestamp.pop_back(); 

                        if (users.find(receiver) != users.end()) {
                            Message msg(user.username, receiver, content, timestamp);
                            user.outbox.push_back(msg);
                            users[receiver].inbox.push_back(msg);
                            cout << "Message sent successfully!" << endl;
                        } else {
                            cout << "Receiver not found." << endl;
                        }
                    } else if (action == 2) {
                        cout << "Inbox for " << user.username << ":" << endl;
                        for (const auto &msg : user.inbox) {
                            cout << "From: " << msg.sender << ", Content: " << msg.content
                                 << ", Timestamp: " << msg.timestamp << endl;
                        }
                    } else if (action == 3) {
                        cout << "Logging out..." << endl;
                    } else {
                        cout << "Invalid action. Please try again." << endl;
                    }
                }

                // Further functionality like messaging can be added here
            } else {
                cout << "Login failed. Please try again." << endl;
            }
        }
    }

    return 0;
}
