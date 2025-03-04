#include <cli/Commands.h>
#include <iostream>

/**
 * @namespace CLI
 * @brief Implementation of CLI commands for task management.
 */
namespace CLI {

    /**
     * @brief Adds a new task to the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects description at argv[2]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments).
     * @note Assigns the next available ID based on the highest existing ID or 1 if empty.
     * @note Saves changes to the store file after adding the task.
     */
    int add(TaskManager& manager, int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Usage: ./task-cli add <description>" << std::endl;
            return 1;
        }

        int id = manager.getTasks().empty() ? 1 : manager.getTasks().rbegin()->first + 1;
        Task task(id, argv[2], TaskStatus::TODO, std::time(nullptr), std::time(nullptr));
        manager.addTask(task);

        std::cout << "Task Created: " << task.toString() << std::endl;
        manager.saveTasksToStore();
        return 0;
    }

    /**
     * @brief Updates the description of an existing task in the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2], description at argv[3]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     * @note Updates the task's updatedAt timestamp to the current time.
     * @note Saves changes to the store file after updating the task.
     */
    int update(TaskManager& manager, int argc, char* argv[]) {
        if (argc < 4) {
            std::cerr << "Usage: ./task-cli update <id> <description>" << std::endl;
            return 1;
        }

        int id = std::stoi(argv[2]);
        auto taskOpt = manager.findTaskById(id);
        if (!taskOpt) {
            std::cerr << "Task not found" << std::endl;
            return 1;
        }

        Task& task = taskOpt.value();
        task.setDescription(argv[3]);
        task.setUpdatedAt(std::time(nullptr));

        std::cout << "Task Updated: " << task.toString() << std::endl;
        manager.saveTasksToStore();
        return 0;
    }

    /**
     * @brief Deletes a task from the TaskManager by its ID.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2]).
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     * @note Saves changes to the store file after deleting the task.
     */
    int deleteTask(TaskManager& manager, int argc, char* argv[]) {
        if (argc < 3) {
            std::cerr << "Usage: ./task-cli delete <id>" << std::endl;
            return 1;
        }

        int id = std::stoi(argv[2]);
        auto taskOpt = manager.findTaskById(id);
        if (!taskOpt) {
            std::cerr << "Task not found" << std::endl;
            return 1;
        }

        manager.removeTask(id);
        std::cout << "Task Deleted: ID " << id << std::endl;
        manager.saveTasksToStore();
        return 0;
    }

    /**
     * @brief Changes the status of an existing task in the TaskManager.
     * @param manager The TaskManager instance to modify.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (expects ID at argv[2]).
     * @param newStatus The new TaskStatus to apply to the task.
     * @return 0 on success, 1 on failure (e.g., insufficient arguments or task not found).
     * @note Updates the task's updatedAt timestamp to the current time.
     * @note Saves changes to the store file after updating the task status.
     */
    int changeStatus(TaskManager& manager, int argc, char* argv[], TaskStatus newStatus) {
        if (argc < 3) {
            std::cerr << "Usage: ./task-cli mark-" << TaskUtils::statusToKey(newStatus) << " <id>" << std::endl;
            return 1;
        }

        int id = std::stoi(argv[2]);
        auto taskOpt = manager.findTaskById(id);
        if (!taskOpt) {
            std::cerr << "Task not found" << std::endl;
            return 1;
        }

        Task& task = taskOpt.value();
        task.setStatus(newStatus);
        task.setUpdatedAt(std::time(nullptr));

        std::cout << "Task Changed to: " << task.getStatusLabel() << std::endl;
        std::cout << task.toString() << std::endl;
        manager.saveTasksToStore();
        return 0;
    }

    /**
     * @brief Lists tasks from the TaskManager, optionally filtered by status.
     * @param manager The TaskManager instance to query.
     * @param argc The number of command-line arguments.
     * @param argv The array of command-line arguments (optional status filter at argv[2]).
     * @return 0 on success, 1 on failure (e.g., invalid status filter).
     * @note If no status filter is provided, lists all tasks.
     * @note Supports status filters: "done", "todo", "in_progress"; others result in an error.
     */
    int list(TaskManager& manager, int argc, char* argv[]) {
        std::optional<TaskStatus> statusFilter = std::nullopt;
        if (argc > 2) {
            statusFilter = TaskUtils::keyToStatus(argv[2]);
            if (statusFilter == TaskStatus::UNKNOWN) {
                std::cerr << "Unknown task status, supported: [done, todo, in-progress]" << std::endl;
                return 1;
            }
        }

        for (const auto& [id, task] : manager.getTasks()) {
            if (statusFilter && task.getStatus() != statusFilter) continue;
            std::cout << task.toString() << std::endl;
        }
        return 0;
    }
}