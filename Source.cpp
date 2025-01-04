#include <iostream>
#include <string>
#include <stack>
#include <limits>
using namespace std;

struct Task {
    int id;
    string name;
    string description;
    int priority;
    string dueDate;
    bool completed;
    Task* next;
};

Task* head = nullptr;
stack<Task*> deletedTasks;

void addTask(int id, string name, string description, int priority, string dueDate) {
    Task* newTask = new Task{id, name, description, priority, dueDate, false, nullptr};
    if (head == nullptr) {
        head = newTask;
    } else {
        Task* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newTask;
    }
    cout << "Task added successfully!\n";
}

void displayTasks() {
    if (head == nullptr) {
        cout << "No tasks available.\n";
        return;
    }
    cout << "Tasks List:\n";
    Task* temp = head;
    while (temp != nullptr) {
        cout << "Task ID: " << temp->id << "\n";
        cout << "Task Name: " << temp->name << "\n";
        cout << "Description: " << temp->description << "\n";
        cout << "Priority: " << temp->priority << "\n";
        cout << "Due Date: " << temp->dueDate << "\n";
        cout << "Completed: " << (temp->completed ? "Yes" : "No") << "\n";
        cout << "-----------------------\n";
        temp = temp->next;
    }
}

void editTask(int id) {
    Task* temp = head;
    while (temp != nullptr && temp->id != id) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Task not found.\n";
        return;
    }
    cout << "Enter New Task Name: ";
    cin.ignore();
    getline(cin, temp->name);
    cout << "Enter New Task Description: ";
    getline(cin, temp->description);
    cout << "Enter New Task Priority (1-5): ";
    cin >> temp->priority;
    cout << "Enter New Task Due Date (DD/MM/YYYY): ";
    cin >> temp->dueDate;
    cout << "Task updated successfully!\n";
}

void deleteTask(int id) {
    Task* temp = head;
    Task* prev = nullptr;

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Task not found.\n";
        return;
    }

    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    deletedTasks.push(temp);
    cout << "Task deleted successfully!\n";
}

void undoLastDelete() {
    if (deletedTasks.empty()) {
        cout << "No deleted tasks to undo.\n";
        return;
    }

    Task* restoredTask = deletedTasks.top();
    deletedTasks.pop();
    restoredTask->next = head;
    head = restoredTask;
    cout << "Undo successful. Task restored.\n";
}

void markTaskCompleted(int id) {
    Task* temp = head;
    while (temp != nullptr && temp->id != id) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Task not found.\n";
        return;
    }
    temp->completed = true;
    cout << "Task marked as completed.\n";
}

void searchTask(int id) {
    Task* temp = head;
    while (temp != nullptr && temp->id != id) {
        temp = temp->next;
    }
    if (temp == nullptr) {
        cout << "Task not found.\n";
        return;
    }
    cout << "Task Found:\n";
    cout << "Task ID: " << temp->id << "\n";
    cout << "Task Name: " << temp->name << "\n";
    cout << "Description: " << temp->description << "\n";
    cout << "Priority: " << temp->priority << "\n";
    cout << "Due Date: " << temp->dueDate << "\n";
    cout << "Completed: " << (temp->completed ? "Yes" : "No") << "\n";
}

int main() {
    int choice;
    do {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Edit Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Mark Task as Completed\n";
        cout << "6. Search Task\n";
        cout << "7. Undo Last Delete\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                string name, description, dueDate;
                cout << "Enter Task ID: ";
                cin >> id;
                cout << "Enter Task Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Task Description: ";
                getline(cin, description);
                cout << "Enter Task Priority (1-5): ";
                cin >> priority;
                cout << "Enter Task Due Date (DD/MM/YYYY): ";
                cin >> dueDate;
                addTask(id, name, description, priority, dueDate);
                break;
            }
            case 2:
                displayTasks();
                break;
            case 3: {
                int id;
                cout << "Enter Task ID to edit: ";
                cin >> id;
                editTask(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter Task ID to delete: ";
                cin >> id;
                deleteTask(id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Task ID to mark as completed: ";
                cin >> id;
                markTaskCompleted(id);
                break;
            }
            case 6: {
                int id;
                cout << "Enter Task ID to search: ";
                cin >> id;
                searchTask(id);
                break;
            }
            case 7:
                undoLastDelete();
                break;
            case 8:
                cout << "Exiting Task Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
