#ifndef HABIT_H
#define HABIT_H
#include <bits/stdc++.h>
using namespace std;
class Habit
{
public:
    Habit() = default;
    Habit(int id, string name, string freq);
    int getId();
    string getName();
    string getFreq();
    int getStreak();
    int getBestStreak();
    int getTotal();
    vector<string> getDates();
    void setName(string n);
    void setFreq(string f);
    void addStreak();
    void resetStreak();
    void markDone(string date);
    bool isDoneOn(string date);

private:
    int id;
    string name;
    string freq;
    int streak = 0;
    int bestStreak = 0;
    int total = 0;
    vector<string> dates;
};
#endif
