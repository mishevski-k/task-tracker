#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "core/Task.h"
#include <map>
#include <optional>

class TaskManager {
private:
    std::map<int, Task> tasks;
    std::string storeName;
public:
    TaskManager(const std::string& storeName = "tasks.json");
    void saveTasksToStore() const;
    void loadTasksFromStore();
    std::optional<std::reference_wrapper<Task>> findTaskById(int id);
    void addTask(const Task& task);
    void removeTask(int id);
    const std::map<int, Task>& getTasks() const;
};

#endif