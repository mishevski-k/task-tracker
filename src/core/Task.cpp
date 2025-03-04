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

/**
 * @brief Gets the human-readable label of the task's status.
 * @return The status label (e.g., "To Do", "In Progress", "Done").
 * @note Relies on TaskUtils::statusToLabel() from "core/TaskStatus.h".
 */
std::string Task::getStatusLabel() const { return TaskUtils::statusToLabel(status); }

/**
 * @brief Gets the key representation of the task's status.
 * @return The status key (e.g., "TODO", "IN_PROGRESS", "DONE").
 * @note Relies on TaskUtils::statusToKey() from "core/TaskStatus.h".
 */
std::string Task::getStatusKey() const { return TaskUtils::statusToKey(status); }

void Task::setStatus(TaskStatus status) { this->status = status; }

std::time_t Task::getCreatedAt() const { return createdAt; }

void Task::setCreatedAt(std::time_t createdAt) { this->createdAt = createdAt; }

std::string Task::getCreatedAtFormatted() const { return formatTime(createdAt); }

std::time_t Task::getUpdatedAt() const { return updatedAt; }

void Task::setUpdatedAt(std::time_t updatedAt) { this->updatedAt = updatedAt; }

std::string Task::getUpdatedAtFormatted() const { return formatTime(updatedAt); }

/**
 * @brief Formats a timestamp into a human-readable string.
 * @param time The timestamp to format.
 * @return The formatted time string (e.g., "2025/03/04 12:00:00").
 * @note Uses local time and the format "YYYY/MM/DD HH:MM:SS".
 */
std::string Task::formatTime(std::time_t time) const {
  std::tm* localTime = std::localtime(&time);
  std::ostringstream oss;
  oss << std::put_time(localTime, "%Y/%m/%d %H:%M:%S");
  return oss.str();
}

/**
 * @brief Converts the task to a human-readable string representation.
 * @return A string describing the task's attributes in the format:
 *         "Task: ( id: <id>, status: <label>, description: <desc>, createdAt: <time>, updatedAt: <time> )".
 */
std::string Task::toString() const {
    return std::format("Task: ( id: {}, status: {}, description: {}, createdAt: {}, updatedAt: {} )",
                       getId(), getStatusLabel(), getDescription(), getCreatedAtFormatted(), getUpdatedAtFormatted());
}

/**
 * @brief Converts the task to a JSON-formatted string.
 * @return A JSON string in the format:
 *         {"id":<id>,"description":"<desc>","status":"<key>","createdAt":<time>,"updatedAt":<time>}.
 * @note Uses raw timestamps (std::time_t) for createdAt and updatedAt fields.
 */
std::string Task::toJSON() const {
    return std::format("{{\"id\":{},\"description\":\"{}\",\"status\":\"{}\",\"createdAt\":{},\"updatedAt\":{}}}",
                       id, description, TaskUtils::statusToKey(status), createdAt, updatedAt);
}