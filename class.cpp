#include <iostream>
#include <fstream> 
#include <string>
#include <sstream>
using namespace std;


    struct User{
        string username;
        string password;
        int balance=10500;
        string carBorrowRequest= "None";
        string carReturnRequest= "None";
    };
    
    struct Car{
        string carName;
        int quantity;
    };
// declaring functions
void displayMenu();
void adminMenu();
void userMenu(const string& username);
void registerUser();
void changeAdminPassword();

bool authenticateUser(const string& username, const string& password)
{ 
    ifstream file("usersDB.txt");
    if (!file.is_open()) {
        cout << "Error opening user database file." << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUsername, filePassword,balance, carBorrowRequest, carReturnRequest;
        // Assuming the format in usersDB.txt is "username,password,balance,carBorrowRequest,carReturnRequest"
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');
        getline(ss, balance, ',');
        getline(ss, carBorrowRequest, ',');
        getline(ss, carReturnRequest, ',');
        // Check if the provided username and password match the user credentials
        // Note: You can also check balance, carBorrowRequest, and carReturnRequest if needed
        if (fileUsername == username && filePassword == password) {
            return true;
        }
    }
    
    return false;
};
    
bool authenticateAdmin(const string& username, const string& password){
ifstream file("admin.txt");
{
    if (!file.is_open()) {
        cout << "Error opening admin file." << endl;
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fileUsername, filePassword;
        // Assuming the format in admin.txt is "username,password"
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');
        // Check if the provided username and password match the admin credentials
        
        if (fileUsername == username && filePassword == password) {
            return true;
        }
    }
    
    return false;
}
}
  

int main(){
    string username, password;
    int choice;

    while(true){
        displayMenu();
        cin >> choice;

        if(choice == 1){ // Admin Login
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
           if(authenticateAdmin(username, password)){
                adminMenu();
           } else {
                cout << "Invalid username or password. Please try again." << endl;
            }
    }
    else if (choice ==2) {// User Login
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (authenticateUser(username, password)) {
            userMenu(username);
        } else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }
else if (choice == 3) {
        cout << "Exiting the program." << endl;
        break;
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
    }
    return 0;
}

//function to display the main menu
void displayMenu() {
    cout << "Welcome to the Car Rental System" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. User Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice: ";
}
// function to display the admin menu
void adminMenu() {
    int choice;
    do{
        cout << "Welcome to the Admin Menu" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Change Admin Password" << endl;
        cout << "3. Logout" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                changeAdminPassword();
                break;
            case 3:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}
// function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    ofstream file("usersDB.txt", ios::app);
    if (file.is_open()) {
        file << username << "," << password << ",10500,None,None" << endl; // Default balance and requests
        file.close();
        cout << "User registered successfully!" << endl;
    } else {
        cout << "Error opening user database file." << endl;
    }
}
// function to change the admin password
void changeAdminPassword() {
    string newPassword;
    cout << "Enter new admin password: ";
    cin >> newPassword;

    ofstream file("admin.txt");
    if (file.is_open()) {
        file << "admin," << newPassword << endl; // Assuming the admin username is always "admin"
        file.close();
        cout << "Admin password changed successfully!" << endl;
    } else {
        cout << "Error opening admin file." << endl;
    }
}
// function to display the user menu
void userMenu(const string& username) {
    cout << "Welcome to the User Menu, " << username << endl;
    // User-specific options can be added here
}