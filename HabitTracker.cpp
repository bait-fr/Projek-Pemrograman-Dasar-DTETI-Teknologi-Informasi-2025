#include <bits/stdc++.h>
#include "HabitTracker.h"
using namespace std;

string HabitTracker::getToday()
{
    time_t now = time(0);
    tm *t = localtime(&now);
    int year = 1900 + t->tm_year;
    int month = 1 + t->tm_mon;
    int day = t->tm_mday;
    string hasil = to_string(year) + "-";
    if (month < 10)
        hasil += "0";
    hasil += to_string(month) + "-";
    if (day < 10)
        hasil += "0";
    hasil += to_string(day);
    return hasil;
}

void HabitTracker::addHabit(string name, string freq)
{
    habits.push_back(Habit(nextId++, name, freq));
    cout << "Habit added.\n";
}

void HabitTracker::editHabit(int id)
{
    for (int i = 0; i < (int)habits.size(); i++)
    {
        if (habits[i].getId() == id)
        {
            string newName, newFreq;
            cout << "New name: ";
            getline(cin, newName);
            cout << "New frequency: ";
            getline(cin, newFreq);
            if (!newName.empty())
                habits[i].setName(newName);
            if (!newFreq.empty())
                habits[i].setFreq(newFreq);
            cout << "Habit updated.\n";
            return;
        }
    }
    cout << "Habit not found.\n";
}

void HabitTracker::deleteHabit(int id)
{
    for (int i = 0; i < (int)habits.size(); i++)
    {
        if (habits[i].getId() == id)
        {
            habits.erase(habits.begin() + i);
            cout << "Habit deleted.\n";
            return;
        }
    }
    cout << "Habit not found.\n";
}

void HabitTracker::showHabits()
{
    if (habits.empty())
    {
        cout << "No habits yet.\n";
        return;
    }
    cout << "\nID\tName\t\tFreq\t\tStreak\tBest\n";
    for (int i = 0; i < (int)habits.size(); i++)
    {
        cout << habits[i].getId() << "\t" << habits[i].getName() << "\t\t"
             << habits[i].getFreq() << "\t\t" << habits[i].getStreak()
             << "\t" << habits[i].getBestStreak() << "\n";
    }
}

void HabitTracker::checkIn(int id)
{
    string today = getToday();
    for (int i = 0; i < (int)habits.size(); i++)
    {
        if (habits[i].getId() == id)
        {
            if (habits[i].isDoneOn(today))
            {
                cout << "Already done today.\n";
                return;
            }
            habits[i].markDone(today);
            cout << "Nice! Streak: " << habits[i].getStreak() << "\n";
            return;
        }
    }
    cout << "Habit not found.\n";
}

void HabitTracker::showToday()
{
    string today = getToday();
    cout << "\nToday: " << today << "\n";
    if (habits.empty())
    {
        cout << "No habits.\n";
        return;
    }
    for (int i = 0; i < (int)habits.size(); i++)
    {
        string mark = habits[i].isDoneOn(today) ? "[X]" : "[ ]";
        cout << mark << " " << habits[i].getId() << ". " << habits[i].getName() << "\n";
    }
}

void HabitTracker::showStats()
{
    if (habits.empty())
    {
        cout << "No habits.\n";
        return;
    }
    cout << "\n=== Stats ===\n";
    for (int i = 0; i < (int)habits.size(); i++)
    {
        cout << habits[i].getName() << "\n";
        cout << "  Streak: " << habits[i].getStreak() << "\n";
        cout << "  Best: " << habits[i].getBestStreak() << "\n";
        cout << "  Total: " << habits[i].getTotal() << "\n\n";
    }
}

void HabitTracker::showHistory(int id)
{
    for (int i = 0; i < (int)habits.size(); i++)
    {
        if (habits[i].getId() == id)
        {
            vector<string> d = habits[i].getDates();
            cout << "\nHistory: " << habits[i].getName() << "\n";
            if (d.empty())
            {
                cout << "No data.\n";
                return;
            }
            for (int j = (int)d.size() - 1; j >= max(0, (int)d.size() - 10); j--)
                cout << d[j] << "\n";
            return;
        }
    }
    cout << "Habit not found.\n";
}

void HabitTracker::loadFile(string file)
{
    ifstream f(file);
    if (!f)
        return;
    habits.clear();
    nextId = 1;
    string line;
    while (getline(f, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        string idStr, name, freq, streakStr, bestStr, totalStr, datesStr;
        if (getline(ss, idStr, '|') and getline(ss, name, '|') and getline(ss, freq, '|') and
            getline(ss, streakStr, '|') and getline(ss, bestStr, '|') and
            getline(ss, totalStr, '|') and getline(ss, datesStr))
        {
            int id = stoi(idStr);
            Habit h(id, name, freq);
            stringstream ds(datesStr);
            string date;
            while (getline(ds, date, ','))
                if (!date.empty())
                    h.markDone(date);
            habits.push_back(h);
            if (id >= nextId)
                nextId = id + 1;
        }
    }
    f.close();
}

void HabitTracker::saveFile(string file)
{
    ofstream f(file);
    if (!f)
    {
        cout << "Cannot save.\n";
        return;
    }
    for (int i = 0; i < (int)habits.size(); i++)
    {
        f << habits[i].getId() << "|" << habits[i].getName() << "|" << habits[i].getFreq() << "|"
          << habits[i].getStreak() << "|" << habits[i].getBestStreak() << "|" << habits[i].getTotal() << "|";
        vector<string> d = habits[i].getDates();
        for (int j = 0; j < (int)d.size(); j++)
        {
            f << d[j];
            if (j < (int)d.size() - 1)
                f << ",";
        }
        f << "\n";
    }
    f.close();
    cout << "Saved.\n";
}
