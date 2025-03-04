#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "core/Task.h"
#include <map>
#include <optional>

/**
 * @class TaskManager
 * @brief Manages a collection of tasks, providing persistence to a JSON file.
 *
 * The TaskManager class handles the storage, retrieval, and manipulation of Task objects.
 * It maintains tasks in a map indexed by their IDs and supports saving to and loading from
 * a JSON file specified by the store name. This class provides methods to add, remove, and
 * find tasks, as well as access the entire task collection.
 */
class TaskManager {
private:
    std::map<int, Task> tasks; ///< Container mapping task IDs to Task objects.
    std::string storeName;    ///< File path for storing tasks in JSON format.
public:

    /**
     * @brief Constructs a TaskManager with an optional store file name.
     * @param storeName The name of the file to persist tasks (defaults to "tasks.json").
     */
    TaskManager(const std::string& storeName = "tasks.json");

    /**
     * @brief Saves all tasks to the store file in JSON format.
     * @throws std::runtime_error If the store file cannot be opened for writing.
     */
    void saveTasksToStore() const;

    /**
     * @brief Loads tasks from the store file into the tasks map.
     * @note If the file does not exist, creates a default file with an initial task.
     * @note Overwrites any existing tasks in the map with the loaded data.
     */
    void loadTasksFromStore();

    /**
     * @brief Finds a task by its ID.
     * @param id The ID of the task to find.
     * @return An optional reference to the Task if found, or std::nullopt if not.
     */
    std::optional<std::reference_wrapper<Task>> findTaskById(int id);

    /**
     * @brief Adds a task to the manager.
     * @param task The Task object to add.
     * @note If a task with the same ID already exists, it will be overwritten.
     */
    void addTask(const Task& task);

    /**
     * @brief Removes a task by its ID.
     * @param id The ID of the task to remove.
     * @note No effect if the ID does not exist in the tasks map.
     */
    void removeTask(int id);

    /**
     * @brief Gets the collection of all tasks.
     * @return A const reference to the tasks map.
     */
    const std::map<int, Task>& getTasks() const;
};

#endif