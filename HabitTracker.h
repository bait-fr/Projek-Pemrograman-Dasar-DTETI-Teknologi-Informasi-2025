#ifndef HABITTRACKER_H
#define HABITTRACKER_H
#include <bits/stdc++.h>
#include "Habit.h"
using namespace std;
class HabitTracker
{
public:
    void addHabit(string name, string freq);
    void editHabit(int id);
    void deleteHabit(int id);
    void showHabits();
    void checkIn(int id);
    void showToday();
    void showStats();
    void showHistory(int id);
    void loadFile(string file);
    void saveFile(string file);
    string getToday();

private:
    vector<Habit> habits;
    int nextId = 1;
};
#endif
