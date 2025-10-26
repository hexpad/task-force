# Task Force

Keeps a list of things. Can mark them as completed.
✅ One checkmark at a time!

# Task.h
```cpp
#ifndef TASK_H
#define TASK_H

#include <vector>
#include <string>

// ANCII color codes
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

// Task structure
struct Task {
    std::string name{};
    bool completed{};
};

// Function prototypes
void saveTasks(const std::vector<Task>& list);
void loadTasks(std::vector<Task>& list);
int safeInput();
void listTasks(const std::vector<Task>& list);

#endif
```

# Task.cpp
```cpp
#include "Task.h"
#include <iostream>
#include <fstream>
#include <limits>

// Save tasks to file
void saveTasks(const std::vector<Task>& list) {
    std::ofstream file("tasks.txt");
    for(const auto& t : list) {
        file << t.completed << ";" << t.name << std::endl;
    }
}

// Load tasks from file
void loadTasks(std::vector<Task>& list) {
    std::ifstream file("tasks.txt");
    std::string line;
    while(std::getline(file,line)) {
        std::size_t sep = line.find(';');
        if(sep == std::string::npos) continue;
        bool status = (line.substr(0,sep) == "1");
        std::string name = line.substr(sep+1);
        list.push_back({name,status});
    }
}

// Safe int input
int safeInput() {
    int choice{};
    while(true) {
        std::cin >> choice;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n'); // discard input
            std::cout << "Invalid input! Please try again: ";
        }else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clean buffer
            return choice;
        }
    }
}

// List all tasks, showing incomplete tasks first
void listTasks(const std::vector<Task>& list) {
    if (list.empty()) {
        std::cout << "List is empty.\n";
        return;
    }

    // First, list incomplete tasks
    for (std::size_t i = 0; i < list.size(); i++) {
        if (!list[i].completed)
            std::cout << i + 1 << ". [ ] " << list[i].name << std::endl;
    }

    // Then, list completed tasks
    for (std::size_t i = 0; i < list.size(); i++) {
        if (list[i].completed)
            std::cout << GREEN << i + 1 << ". [✔] " << list[i].name << RESET << std::endl;
    }
}
```

# main.cpp
```cpp
#include "Task.h"
#include <iostream>
#include <vector>
#include <string>


int main()
{
    std::vector<Task> list;
    loadTasks(list);

    while(true) {
        std::cout << "\n=== TASK FORCE ===\n"
                  << "1. Add Task\n"
                  << "2. List Tasks\n"
                  << "3. Mark Task As Completed\n"
                  << "4. Delete Task\n"
                  << "5. Exit\n"
                  << "Choice: ";

        int choice = safeInput();

        if (choice == 1) {
            std::string taskName;
            std::cout << "Enter task: ";
            std::getline(std::cin , taskName);
            list.push_back({taskName, false});
            saveTasks(list);
        }
        else if (choice == 2 ) {
            std::cout << "\n--- Tasks ---\n";
            listTasks(list);
        }
        else if (choice == 3) {
            std::cout << "Enter task number to mark as completed: ";
            int i = safeInput();
            if (i>0 && i<=list.size()) {
                list[i-1] .completed = true;
                saveTasks(list);
            } else std::cout << "Invalid number!\n";
        }
        else if (choice == 4) {
            std::cout << "Enter task number to delete: ";
            int i = safeInput();
            if (i>0 && i<= list.size()) {
                list.erase(list.begin() + i - 1);
                saveTasks(list);
            } else std::cout << "Invalid number!\n";
        }
        else if (choice == 5) {
            std::cout << "Exiting...\n";
            break;
        }
        else std::cout << "Invalid choice!\n";
    }

}
``

