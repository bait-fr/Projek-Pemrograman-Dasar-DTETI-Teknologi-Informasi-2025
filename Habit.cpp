#include <bits/stdc++.h>
#include "Habit.h"
using namespace std;

Habit::Habit(int id, string name, string freq)
{
    this->id = id;
    this->name = name;
    this->freq = freq;
    streak = 0;
    bestStreak = 0;
    total = 0;
}

int Habit::getId() { return id; }
string Habit::getName() { return name; }
string Habit::getFreq() { return freq; }
int Habit::getStreak() { return streak; }
int Habit::getBestStreak() { return bestStreak; }
int Habit::getTotal() { return total; }
vector<string> Habit::getDates() { return dates; }

void Habit::setName(string n) { name = n; }
void Habit::setFreq(string f) { freq = f; }

void Habit::addStreak()
{
    streak++;
    if (streak > bestStreak)
        bestStreak = streak;
}

void Habit::resetStreak() { streak = 0; }

void Habit::markDone(string date)
{
    if (!isDoneOn(date))
    {
        dates.push_back(date);
        total++;
        addStreak();
    }
}

bool Habit::isDoneOn(string date)
{
    for (int i = 0; i < (int)dates.size(); i++)
        if (dates[i] == date)
            return true;
    return false;
}
