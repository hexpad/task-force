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
