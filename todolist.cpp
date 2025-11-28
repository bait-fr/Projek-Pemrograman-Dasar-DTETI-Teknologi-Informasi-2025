#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>  
#include <algorithm>  

using namespace std;

// Class Task 
class Task {
private:
    int id;
    string description;
    string status;  
    string deadline;

public:
    Task(int id, string desc, string stat, string dl) : id(id), description(desc), status(stat), deadline(dl) {}

    int getId() const { return id; }
    string getDescription() const { return description; }
    string getStatus() const { return status; }
    string getDeadline() const { return deadline; }

    void setDescription(string desc) { description = desc; }
    void setStatus(string stat) { status = stat; }
    void setDeadline(string dl) { deadline = dl; }

    virtual void display() const {
        cout << "ID: " << id << " | Desc: " << description << " | Status: " << status << " | Deadline: " << deadline << endl;
    }
};

// Class ToDoList 
class ToDoList {
private:
    vector<Task> tasks;
    int nextId = 1;

public:
    // Add task
    void addTask(string desc, string dl) {
        tasks.push_back(Task(nextId++, desc, "pending", dl));
        cout << "Task added successfully!" << endl;
    }

    // Edit task 
    void editTask(int id) {
        for (auto& task : tasks) {
            if (task.getId() == id) {
                string newDesc, newDl;
                cout << "Enter new description: ";
                getline(cin, newDesc);
                cout << "Enter new deadline (YYYY-MM-DD): ";
                getline(cin, newDl);
                
                if (!newDesc.empty()) task.setDescription(newDesc);
                if (!newDl.empty()) task.setDeadline(newDl);
                
                cout << "Task edited successfully!" << endl;
                return;
            }
        }
        cout << "Task not found!" << endl;
    }

    // Tampilkan tasks 
    void displayTasks(int page = 1, int perPage = 5) {
        int start = (page - 1) * perPage;
        int end = min(start + perPage, (int)tasks.size());
        if (start >= tasks.size()) {
            cout << "No more tasks." << endl;
            return;
        }
        cout << "Page " << page << ":" << endl;
        for (int i = start; i < end; ++i) {
            tasks[i].display();
        }
        cout << "Total tasks: " << tasks.size() << endl;
    }

    // Mark task done/undone 
    void markDone(int id) {
        for (auto& task : tasks) {
            if (task.getId() == id) {
                task.setStatus(task.getStatus() == "pending" ? "done" : "pending");
                cout << "Task status updated!" << endl;
                return;
            }
        }
        cout << "Task not found!" << endl;
    }

    // Delete Task
    void deleteTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(), 
                         [id](const Task& t) { return t.getId() == id; });
        if (it != tasks.end()) {
            tasks.erase(it);
            cout << "Task deleted successfully!" << endl;
        } else {
            cout << "Task not found!" << endl;
        }
    }

    // Load from file
    void loadFromFile(const string& filename = "output.txt") {
        ifstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error: Cannot open file '" << filename << "'" << endl;
            cout << "Make sure the file exists!" << endl;
            return;
        }
        
        tasks.clear();
        nextId = 1;
        
        string line;
        int loadedCount = 0;
        
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string idStr, desc, stat, dl;
            
            if (getline(ss, idStr, '|') &&
                getline(ss, desc, '|') &&
                getline(ss, stat, '|') &&
                getline(ss, dl)) {
                
                try {
                    int id = stoi(idStr);
                    tasks.push_back(Task(id, desc, stat, dl));
                    loadedCount++;
                    
                    if (id >= nextId) nextId = id + 1;
                    
                } catch (const exception& e) {
                    cout << "Warning: Invalid data in line: " << line << endl;
                }
            } else {
                cout << "Warning: Invalid format in line: " << line << endl;
            }
        }
        
        file.close();
        cout << "Successfully loaded " << loadedCount << " tasks from '" << filename << "'" << endl;
    }

    // Save ke file 
    void saveToFile(const string& filename = "output.txt") {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }
        for (const auto& task : tasks) {
            file << task.getId() << "|" << task.getDescription() << "|" 
                 << task.getStatus() << "|" << task.getDeadline() << endl;
        }
        file.close();
        cout << "Data saved to " << filename << endl;
    }
};

// Main Function
int main() {
    ToDoList todo;
    todo.loadFromFile("output.txt");

    int choice;
    while (true) {
        cout << "\n==================================================\n";
        cout << "                    TO DO LIST                    \n";
        cout << "==================================================\n";
        cout << "\nMenu:\n";
        cout << "1. Add Task\n";
        cout << "2. Edit Task\n";
        cout << "3. Display Tasks (with paging)\n";
        cout << "4. Mark Task Done/Undone\n";
        cout << "5. Delete Task\n";
        cout << "6. Save to File\n";
        cout << "7. Exit\n";
        cout << "Option6: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string desc, dl;
            cout << "Enter description: ";
            getline(cin, desc);
            cout << "Enter deadline (YYYY-MM-DD): ";
            getline(cin, dl);
            todo.addTask(desc, dl);
        } else if (choice == 2) {
            int id;
            cout << "Enter task ID to edit: ";
            cin >> id;
            cin.ignore();
            todo.editTask(id);
        } else if (choice == 3) {
            int page;
            cout << "Enter page number: ";
            cin >> page;
            todo.displayTasks(page);
        } else if (choice == 4) {
            int id;
            cout << "Enter task ID to mark: ";
            cin >> id;
            todo.markDone(id);
        } else if (choice == 5) {
            int id;
            cout << "Enter task ID to delete: ";
            cin >> id;
            todo.deleteTask(id);
        } else if (choice == 6) {
            todo.saveToFile("output.txt");
        } else if (choice == 7) {
            todo.saveToFile("output.txt");
            cout << "App closed\n";
            break;
        } else {
            cout << "ERROR: Invalid choice!" << endl;
        }
    }
    return 0;
}

