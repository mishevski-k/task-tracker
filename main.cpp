#include <iostream>
#include <ctime>
#include <optional>
#include <vector>
#include <format>
#include <iomanip>
#include <unordered_map>
#include <sstream>

// NOTE: Basic Implementation, code should be refactored and restructured in the future
// Features to change/add: change tasks to a better data structure, add exception handling instead of return code, refactor everything in more header/source files

enum TaskStatus {
    TODO, IN_PROGRESS, DONE
};

std::string statusToString(TaskStatus status) {
    static  const std::unordered_map<TaskStatus, std::string> statusMap = {
        {TaskStatus::DONE, "Done"},
        {TaskStatus::TODO, "Todo"},
        {TaskStatus::IN_PROGRESS, "In progress"},
    };

    if (auto it = statusMap.find(status); it != statusMap.end()) {
        return it->second;
    }

    return "Unknown";
}

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

    std::string getStatusString() {
        return statusToString(this->status);
    }

    void setStatus(TaskStatus status) {
        this->status = status;
    }

    std::string formatTime(std::time_t time) {
        std::tm* localTime = std::localtime(&time);
        std::ostringstream oss;
        oss << std::put_time(localTime, "%Y/%m/%d %H:%M:%S");

        return oss.str();
    }

    std::time_t getCreatedAt() {
        return this->createdAt;
    }

    void setCreatedAt(std::time_t createdAt) {
        this->createdAt = createdAt;
    }

    std::string getCreatedAtFormated() {
        return formatTime(this->getCreatedAt());
    }

    std::time_t getUpdatedAt() {
        return this->updatedAt;
    }

    void setUpdatedAt(std::time_t updatedAt) {
        this->updatedAt = updatedAt;
    }

    std::string getUpdatedAtFormated() {
        return formatTime(this->getUpdatedAt());
    }
};

// Change to binary tree later on for faster search
std::vector<Task> tasks;

struct FindTaskByIdResponse {
    Task& task;
    int index;
};

std::optional<FindTaskByIdResponse> findTaskById(int id) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].getId() == id) {
            return FindTaskByIdResponse{tasks[i], i};
        }
    }
    return std::nullopt;
}

int add(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./task-cli add <description>" << std::endl;
        return 1;
    }

    Task task = Task(tasks.size() + 1, argv[2], TaskStatus::TODO, std::time(nullptr), std::time(nullptr));

    tasks.push_back(task);

    return 0;
}

int update(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: ./task-cli update <id> <description>" << std::endl;
        return 1;
    }

    int id = std::stoi(argv[2]);
    std::string description = static_cast<std::string>(argv[3]);

    std::optional<FindTaskByIdResponse> response = findTaskById(id);

    if (!response) {
        std::cerr << "Task not found" << std::endl;
    }

    response->task.setDescription(description);

    return 0;
}

int deleteTask(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: ./task-cli delete <id>" << std::endl;
        return 1;
    }

    int id = std::stoi(argv[2]);

    std::optional<FindTaskByIdResponse> response = findTaskById(id);

    if (!response) {
        std::cerr << "Task not found" << std::endl;
        return 1;
    }

    tasks.erase(tasks.begin() + response->index);

    return 0;
}

void list() {
    for (Task task : tasks) {
        std::string message = std::format("Task: ( id: {}, status: {}, description: {}, createdAt: {}, updatedAt: {} )", task.getId(), task.getStatusString(), task.getDescription(), task.getCreatedAtFormated(), task.getUpdatedAtFormated());
        std::cout << message << std::endl;
    }
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
        update(argc, argv);
    }else if (action == "delete") {
        deleteTask(argc, argv);
    }else if (action == "list") {
        list();
    }

    // For debugging only
    list();

    std::cout << "Main is working" << std::endl;

    return 0;
}