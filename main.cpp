#include <bits/stdc++.h>
#include "HabitTracker.h"
#include "Account.h"
using namespace std;

int main()
{
    Account acc;
    HabitTracker tracker;
    acc.readAllAccounts();

    int authChoice;
    bool loggedIn = false;
    string username, password;

    while (!loggedIn)
    {
        cout << "\n=== HABIT TRACKER ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Pilih: ";
        cin >> authChoice;
        cin.ignore();

        if (authChoice == 1)
        {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            acc.login(username, password);
            loggedIn = true;
            tracker.loadFile(username + "_habits.txt");
        }
        else if (authChoice == 2)
        {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);
            acc.registerAccount(username, password);
            acc.saveAllAccounts();
        }
        else if (authChoice == 3)
        {
            return 0;
        }
    }

    int choice;
    while (true)
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Tambah Habit\n";
        cout << "2. Lihat Semua Habit\n";
        cout << "3. Cek Hari Ini\n";
        cout << "4. Tandai Selesai\n";
        cout << "5. Statistik\n";
        cout << "6. Riwayat\n";
        cout << "7. Edit Habit\n";
        cout << "8. Hapus Habit\n";
        cout << "9. Simpan & Keluar\n";
        cout << "Pilih: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string name, freq;
            cout << "Nama habit: ";
            getline(cin, name);
            cout << "Frekuensi (daily/weekly/monthly): ";
            getline(cin, freq);
            tracker.addHabit(name, freq);
        }
        else if (choice == 2)
        {
            tracker.showHabits();
        }
        else if (choice == 3)
        {
            tracker.showToday();
        }
        else if (choice == 4)
        {
            tracker.showToday();
            int id;
            cout << "ID habit: ";
            cin >> id;
            cin.ignore();
            tracker.checkIn(id);
        }
        else if (choice == 5)
        {
            tracker.showStats();
        }
        else if (choice == 6)
        {
            tracker.showHabits();
            int id;
            cout << "ID habit: ";
            cin >> id;
            cin.ignore();
            tracker.showHistory(id);
        }
        else if (choice == 7)
        {
            tracker.showHabits();
            int id;
            cout << "ID habit: ";
            cin >> id;
            cin.ignore();
            tracker.editHabit(id);
        }
        else if (choice == 8)
        {
            tracker.showHabits();
            int id;
            cout << "ID habit: ";
            cin >> id;
            cin.ignore();
            tracker.deleteHabit(id);
        }
        else if (choice == 9)
        {
            tracker.saveFile(username + "_habits.txt");
            acc.logout();
            break;
        }
        else
        {
            cout << "Pilihan salah.\n";
        }
    }
    return 0;
}
