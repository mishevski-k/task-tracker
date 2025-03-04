#include <cli/Commands.h>
#include <iostream>

namespace CLI {
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