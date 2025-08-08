#include<iostream>
using namespace std;
class Message {
    string sender;
    string receiver;
    string content;
    string timestamp;
    
};
class User {
    public:
    string username;
    vector<Message> inbox;
    vector<Message> outbox;
    User(string uname, string pass):username(uname){ 
        if(isValid(pass)){
            password = pass;}
        else{
            throw invalid_argument("Invalid password");
            cout << "Invalid password. Please try again." << endl;
        }
    }
    bool login(string pass) {
        if(pass == password) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Login failed. Incorrect password." << endl;
            return false;
        }
    };


    private:
        bool isValid(string pass) {
            if(pass.length() < 6) {
                cout << "Password must be at least 6 characters long." << endl;
                return false;
            }
            return !pass.empty(); // Example: password should not be empty
        }
        string password;
    
};


int main(){
    int input=0;
    unordered_map<string, User> users; // Store users by username
    while(input!=3){
        cout<<"1.new User \n 2.login \n 3 exit "<<endl;
        cin>>input;
        
        if(input==1){
            string username, password;
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
            try{
                User newUser(username, password);
                users[username] = newUser; // Store the new user in the map
            cout<<"User created successfully!"<<endl;}
            catch(const invalid_argument& e){
                cout<<"User NOT created successfully"<<endl;
            
            }
        } else if(input==2){
            string username, password;
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
    }
}
