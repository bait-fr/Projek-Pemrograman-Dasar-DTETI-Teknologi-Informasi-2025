#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <bits/stdc++.h>
#include "User.h"
using namespace std;
class Account {
    public:
    void registerAccount(string &username, string &password); // create
    void readAllAccounts(); // read
    void updateAccount(string &newUsername, string &newPassword); // update
    void deleteAccount(string &password); // delete
    void saveAllAccounts();
    void login(string &username, string &password);
    void logout();
    bool checkUsernameDuplicates(string &username);
    bool checkPasswordDuplicates(string &password);

    private:
    vector <User> accountList;
    User* currentUser = nullptr;
    string dataFile = "userData.txt";
};
#endif