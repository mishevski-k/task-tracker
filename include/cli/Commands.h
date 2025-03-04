#ifndef COMMANDS_H
#define COMMANDS_H

#include "core/TaskManager.h"

/**
 * @namespace CLI
 * @brief Provides command-line interface (CLI) functions for interacting with a TaskManager.
 *
 * This namespace contains functions that implement CLI commands for managing tasks, such as
 * adding, updating, deleting, changing the status of, and listing tasks. Each function operates
 * on a TaskManager instance and processes command-line arguments (argc, argv).
 */
namespace CLI{

    /**
     * @brief Adds a new task to the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects description at argv[2]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments).
     */
    int add(TaskManager& manager, int argc, char* argv[]);

    /**
     * @brief Updates the description of an existing task in the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2], description at argv[3]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     */
    int update(TaskManager& manager, int argc, char* argv[]);

    /**
     * @brief Deletes a task from the TaskManager by its ID.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     */
    int deleteTask(TaskManager& manager, int argc, char* argv[]);

    /**
     * @brief Changes the status of an existing task in the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2]).
     * @param newStatus The new TaskStatus to apply to the task.
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     */
    int changeStatus(TaskManager& manager, int argc, char* argv[], TaskStatus newStatus);

    /**
     * @brief Lists tasks from the TaskManager, optionally filtered by status.
     * @param manager The TaskManager instance to query.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (optional status filter at argv[2]).
     * @return 0 on success, 1 on failure (e.g., invalid status filter).
     */
    int list(TaskManager& manager, int argc, char* argv[]);
}

#endif