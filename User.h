#ifndef USER_H
#define USER_H
#include <bits/stdc++.h>
using namespace std;
class User {
    public:
    User() = default;
    User(string &uName, string &pWord);
    void setUsername(string &uName);
    void setPassword(string &pWord);
    string getUsername();
    string getPassword();
    bool checkPassword(string &pWord);
    private:
    string username;
    string password;
};
#endif