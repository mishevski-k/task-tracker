#include <iostream>
#include <ctime>
#include <vector>

// NOTE: Basic Implementation, code should be refactored and restructured in the future
// Features to change/add: change tasks to a better data structure, add exception handling instead of return code

enum TaskStatus {
    TODO, IN_PROGRESS, DONE
};

class Task {
private:
    int id;
    std::string description;
    TaskStatus status;
    std::time_t createdAt;
    std::time_t updatedAt;
public:
    Task(int id, std::string description, TaskStatus status, std::time_t createdAt, std::time_t updatedAt) {
        this->id = id;
        this->description = description;
        this->status = status;
        this->createdAt = createdAt;
        this->updatedAt = updatedAt;
    }

    int getId() {
        return this->id;
    }

    void setId(int id) {
        this->id = id;
    }

    std::string getDescription() {
        return this->description;
    }

    void setDescription(std::string description) {
        this->description = description;
    }

    TaskStatus getStatus() {
        return this->status;
    }

    void setStatus(TaskStatus status) {
        this->status = status;
    }

    std::time_t getCreatedAt() {
        return this->createdAt;
    }

    void setCreatedAt(std::time_t createdAt) {
        this->createdAt = createdAt;
    }

    std::time_t getUpdatedAt() {
        return this->updatedAt;
    }

    void setUpdatedAt(std::time_t updatedAt) {
        this->updatedAt = updatedAt;
    }
};

// Change to binary tree later on for faster search
std::vector<Task> tasks;

int add(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./task-cli add <description>" << std::endl;
        return 1;
    }

    Task task = Task(tasks.size() + 1, argv[2], TaskStatus::TODO, std::time(nullptr), std::time(nullptr));

    tasks.push_back(task);

    return 0;
}

int upddate(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./task-cli update <id> <description>" << std::endl;
        return 1;
    }

    int id = std::stoi(argv[2]);
    std::string description = static_cast<std::string>(argv[3]);

    for (Task& task : tasks) {
        if (task.getId() == id) {
            task.setDescription(description);
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {

    // Just for testing
    Task task = Task(1, "test", TaskStatus::DONE, std::time(nullptr), std::time(nullptr));
    tasks.push_back(task);

    if (argc < 2) {
        std::cerr << "Usage: ./task.cli <action>\n";
        return 1;
    }

    std::cout << argc << std::endl;

    std::string action = static_cast<std::string>(argv[1]);

    if (action == "add") {
        add(argc, argv);
    }else if (action == "update") {
        upddate(argc, argv);
    }

    for (int i = 0; i < tasks.size(); ++i) {
        std::cout << tasks.at(i).getId() << std::endl;
        std::cout << tasks.at(i).getDescription() << std::endl;
        std::cout << tasks.at(i).getStatus() << std::endl;
        std::cout << tasks.at(i).getCreatedAt() << std::endl;
        std::cout << tasks.at(i).getUpdatedAt() << std::endl;
    }

    std::cout << "Main is working" << std::endl;

    return 0;
}