#include <bits/stdc++.h>
#include "Account.h"
#include "User.h"
using namespace std;

bool Account::checkUsernameDuplicates(string &username) {
    for(int i = 0; i < (int)accountList.size(); i++) if(accountList[i].getUsername() == username) return true;
    return false;
}

bool Account::checkPasswordDuplicates(string &password) {
    for(int i = 0; i < (int)accountList.size(); i++) if(accountList[i].getPassword() == password) return true;
    return false;
}

void Account::registerAccount(string &username, string &password) {
    if(username.empty() or password.empty()) {
        cout << "Username/password cannot be empty!\n";
        return;
    }
    if(checkUsernameDuplicates(username)) {
        cout << "Username already taken.\n";
        return;
    }
    accountList.emplace_back(username, password);
    cout << "Account successfully registered.\n";
}

void Account::login(string &username, string &password) {
    int index = -1;
    bool found = false;
    for(int i = 0; i < (int)accountList.size(); i++) {
        if(accountList[i].getUsername() == username) {
            index = i;
            break;
        }
    }
    if(index != -1 and accountList[index].getPassword() == password) found = true;
    if(found) {
        currentUser = &accountList[index];
        cout << "Login successful. Welcome, " << username << '\n';
        return;
    }
    cout << "Login failed. Invalid username/password.\n";
}

void Account::logout() {
    if(currentUser) {
        cout << "Logged out from " << currentUser->getUsername() << ".\n";
        currentUser = nullptr;
        return;
    }
}

void Account::updateAccount(string &newUsername, string &newPassword) {
    if(!currentUser) return;
    if(newUsername.empty() or newPassword.empty()) {
        cout << "Username/password cannot be empty!\n";
        return;
    }
    if(checkUsernameDuplicates(newUsername)) {
        cout << "Username is already taken.\n";
        return;
    }
    currentUser->setUsername(newUsername);
    cout << "Username updated to " << newUsername << '\n';
    if(checkPasswordDuplicates(newPassword)) {
        cout << "Password cannot be the same as the previous one!\n";
        return;
    }
    currentUser->setPassword(newPassword);
    cout << "Password successfully updated.\n";
}

void Account::deleteAccount(string &password) {
    if(!currentUser) return;
    if(!currentUser->checkPassword(password)) {
        cout << "Incorrect password. Deletion failed!\n";
        return;
    }
    string username = currentUser->getUsername();
    int index = -1;
    for(int i = 0; i < (int)accountList.size(); i++) if(accountList[i].getUsername() == username) index = i;
    accountList.erase(accountList.begin() + index);
    logout();
    cout << "Account successfully deleted.\n";
}

void Account::readAllAccounts() {
    ifstream inFile(dataFile);
    if(!inFile) {
        cout << "Cannot open account database.\n";
        return;
    }
    accountList.clear();
    string username, password;
    while(inFile >> username >> password) accountList.emplace_back(username, password);
    inFile.close();
    cout << "Accounts succesfully read.\n";
}

void Account::saveAllAccounts() {
    string outputFile = "outputFile.txt";
    ofstream outFile(outputFile);
    if(!outFile) {
        cout << "Cannot save account database.\n";
        return;
    }
    for(int i = 0; i < (int)accountList.size(); i++) outFile << accountList[i].getUsername() << ' ' << accountList[i].getPassword() << '\n';
    outFile.close();
    cout << "Accounts succesfully saved.\n";
}