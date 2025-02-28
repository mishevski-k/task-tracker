#include <iostream>
#include <ctime>
#include <vector>

// NOTE: Basic Implementation, code should be refactored and restructured in the future

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

int main() {

    std::vector<Task> tasks;


    Task task = Task(1, "test", TaskStatus::DONE, std::time(nullptr), std::time(nullptr));

    tasks.push_back(task);

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