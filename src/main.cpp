#include "core/TaskManager.h"
#include "cli/Commands.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./task-cli <action>\n";
        return 1;
    }

    TaskManager manager;
    try {
        manager.loadTasksFromStore();
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return 1;
    }

    std::string action = argv[1];
    if (action == "add") return CLI::add(manager, argc, argv);
    if (action == "update") return CLI::update(manager, argc, argv);
    if (action == "delete") return CLI::deleteTask(manager, argc, argv);
    if (action == "mark-in-progress") return CLI::changeStatus(manager, argc, argv, TaskStatus::IN_PROGRESS);
    if (action == "mark-done") return CLI::changeStatus(manager, argc, argv, TaskStatus::DONE);
    if (action == "list") return CLI::list(manager, argc, argv);

    std::cerr << "Unknown action: " << action << std::endl;
    return 1;
}