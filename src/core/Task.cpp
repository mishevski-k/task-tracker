#include "core/Task.h"
#include <format>
#include <iomanip>
#include <sstream>

Task::Task(int id, std::string description, TaskStatus status, std::time_t createdAt, std::time_t updatedAt) :
           id(id), description(description), status(status), createdAt(createdAt), updatedAt(updatedAt) {}

int Task::getId() const { return id; }
void Task::setId(int id) { this->id = id; }
std::string Task::getDescription() const { return description; }
void Task::setDescription(std::string description) { this->description = description; }
TaskStatus Task::getStatus() const { return status; }
std::string Task::getStatusLabel() const { return TaskUtils::statusToLabel(status); }
std::string Task::getStatusKey() const { return TaskUtils::statusToKey(status); }
void Task::setStatus(TaskStatus status) { this->status = status; }
std::time_t Task::getCreatedAt() const { return createdAt; }
void Task::setCreatedAt(std::time_t createdAt) { this->createdAt = createdAt; }
std::string Task::getCreatedAtFormatted() const { return formatTime(createdAt); }
std::time_t Task::getUpdatedAt() const { return updatedAt; }
void Task::setUpdatedAt(std::time_t updatedAt) { this->updatedAt = updatedAt; }
std::string Task::getUpdatedAtFormatted() const { return formatTime(updatedAt); }

std::string Task::formatTime(std::time_t time) const {
  std::tm* localTime = std::localtime(&time);
  std::ostringstream oss;
  oss << std::put_time(localTime, "%Y/%m/%d %H:%M:%S");
  return oss.str();
}

std::string Task::toString() const {
    return std::format("Task: ( id: {}, status: {}, description: {}, createdAt: {}, updatedAt: {} )",
                       getId(), getStatusLabel(), getDescription(), getCreatedAtFormatted(), getUpdatedAtFormatted());
}

std::string Task::toJSON() const {
    return std::format("{{\"id\":{},\"description\":\"{}\",\"status\":\"{}\",\"createdAt\":{},\"updatedAt\":{}}}",
                       id, description, TaskUtils::statusToKey(status), createdAt, updatedAt);
}