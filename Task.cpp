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
