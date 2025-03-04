#include "core/TaskManager.h"
#include "cli/Commands.h"
#include <iostream>

/**
 * @brief Entry point for the task management CLI application.
 *
 * This function serves as the main entry point for a command-line interface (CLI) tool
 * that manages tasks using a TaskManager instance. It processes command-line arguments
 * to determine the action to perform (e.g., add, update, delete, list tasks) and delegates
 * to the appropriate CLI command function. The program loads tasks from a store file
 * upon startup and handles errors gracefully.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments, where:
 *             - argv[0] is the program name,
 *             - argv[1] is the action (e.g., "add", "list"),
 *             - argv[2...] are action-specific arguments.
 * @return 0 on successful execution, 1 on failure (e.g., invalid action, insufficient arguments, or error loading tasks).
 */
int main(int argc, char* argv[]) {

    // Check for minimum required arguments
    if (argc < 2) {
        std::cerr << "Usage: ./task-cli <action>\n";
        return 1;
    }

    // Initialize the TaskManager and load tasks
    TaskManager manager;
    try {
        manager.loadTasksFromStore();
    } catch (const std::exception& e) {
        std::cerr << "Error loading tasks: " << e.what() << std::endl;
        return 1;
    }

    // Determine the action and delegate to the appropriate CLI command
    std::string action = argv[1];
    if (action == "add") return CLI::add(manager, argc, argv);
    if (action == "update") return CLI::update(manager, argc, argv);
    if (action == "delete") return CLI::deleteTask(manager, argc, argv);
    if (action == "mark-in-progress") return CLI::changeStatus(manager, argc, argv, TaskStatus::IN_PROGRESS);
    if (action == "mark-done") return CLI::changeStatus(manager, argc, argv, TaskStatus::DONE);
    if (action == "list") return CLI::list(manager, argc, argv);

    // Handle unknown actions
    std::cerr << "Unknown action: " << action << std::endl;
    return 1;
}