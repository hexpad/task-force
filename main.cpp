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
