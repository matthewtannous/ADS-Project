#include <iostream>
#include "Users.h"
#include "utils.h"


using namespace std;

int main() {
    Users users; // List of all users
    // cout << users.users.size();
    int choice;
    array<string, 2> userInfo;

    do {
        cout << "Hello! What would you like to do?\n"
                "1. Register\n"
                "2. Login\n"
                "3. Exit\n"
                "4. Print all users (testing)\n"; // Add other options later

        cin >> choice;

        switch (choice) {
            case 1:
                userInfo = getUserInfo();
                users.signup(userInfo[0], userInfo[1]);
                break;
            case 2:
                userInfo = getUserInfo();
                users.login(userInfo[0], userInfo[1]);
                break;
            case 4:
                users.printAllUsers();
                break;
            default:
                cout << "Exiting...";
        }
    } while (choice != 3);
}
