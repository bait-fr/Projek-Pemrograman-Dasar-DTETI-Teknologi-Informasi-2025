#include <bits/stdc++.h>
#include "User.h"
using namespace std;

void User::setUsername(string &uName) {
    username = uName;
}

void User::setPassword(string &pWord) {
    password = pWord;
}

string User::getUsername() {
    return username;
}

string User::getPassword() {
    return password;
}

bool User::checkPassword(string &pWord) {
    return pWord == password;
}

User::User(string &uName, string &pWord) {
    username = uName;
    password = pWord;
}