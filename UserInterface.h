#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <bits/stdc++.h>
#include "HabitTracker.h"
#include "Account.h"
using namespace std;

class UserInterface {
    public:
    UserInterface() = default;
    UserInterface(Account &acc, HabitTracker &tracker, string &username);
    void showLoginMenu();
    void showMainMenu();
    void run();
    private:
    Account acc;
    HabitTracker tracker;
    string username;

};
#endif