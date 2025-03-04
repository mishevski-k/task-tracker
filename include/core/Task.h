#ifndef TASK_H
#define TASK_H

#include "core/TaskStatus.h"
#include <string>
#include <ctime>


/**
 * @class Task
 * @brief Represents a task with an ID, description, status, and creation/update timestamps.
 *
 * The Task class encapsulates the properties and behaviors of a task in a task management system.
 * It provides methods to access and modify task attributes, as well as utilities to format the task
 * as a string or JSON representation. This class assumes the existence of a TaskStatus enum and
 * TaskUtils helper functions defined in "core/TaskStatus.h".
 */
class Task {
private:
    int id; ///< Unique identifier for the task.
    std::string description; ///< Brief description of the task.
    TaskStatus status; ///< Current status of the task (e.g., TODO, IN_PROGRESS).
    std::time_t createdAt; ///< Timestamp when the task was created.
    std::time_t updatedAt; ///< Timestamp when the task was last updated.
public:
    /**
       * @brief Constructs a Task object with the specified attributes.
       * @param id The unique identifier for the task.
       * @param description A brief description of the task.
       * @param status The initial status of the task.
       * @param createdAt The creation timestamp of the task.
       * @param updatedAt The last updated timestamp of the task.
       */
    Task(int id, std::string description, TaskStatus status, std::time_t createdAt, std::time_t updatedAt);

    /**
       * @brief Gets the task's unique identifier.
       * @return The task ID.
       */
    int getId() const;

    /**
     * @brief Sets the task's unique identifier.
     * @param id The new task ID.
     */
    void setId(int id);

    /**
     * @brief Gets the task's description.
     * @return The task description.
     */
    std::string getDescription() const;

    /**
     * @brief Sets the task's description.
     * @param description The new task description.
     */
    void setDescription(std::string description);

    /**
     * @brief Gets the task's current status.
     * @return The task status as a TaskStatus enum value.
     */
    TaskStatus getStatus() const;

    /**
     * @brief Gets the human-readable label of the task's status.
     * @return The status label (e.g., "To Do", "In Progress", "Done").
     * @note Relies on TaskUtils::statusToLabel() from "core/TaskStatus.h".
     */
    std::string getStatusLabel() const;

    /**
     * @brief Gets the key representation of the task's status.
     * @return The status key (e.g., "TODO", "IN_PROGRESS", "DONE").
     * @note Relies on TaskUtils::statusToKey() from "core/TaskStatus.h".
     */
    std::string getStatusKey() const;

    /**
     * @brief Sets the task's status.
     * @param status The new task status.
     */
    void setStatus(TaskStatus status);

    /**
     * @brief Gets the task's creation timestamp.
     * @return The creation time as a std::time_t value.
     */
    std::time_t getCreatedAt() const;

    /**
     * @brief Sets the task's creation timestamp.
     * @param createdAt The new creation timestamp.
     */
    void setCreatedAt(std::time_t createdAt);

    /**
     * @brief Gets the formatted creation timestamp as a string.
     * @return The formatted creation time (e.g., "2025/03/04 12:00:00").
     */
    std::string getCreatedAtFormatted() const;

    /**
     * @brief Gets the task's last updated timestamp.
     * @return The last updated time as a std::time_t value.
     */
    std::time_t getUpdatedAt() const;

    /**
     * @brief Sets the task's last updated timestamp.
     * @param updatedAt The new last updated timestamp.
     */
    void setUpdatedAt(std::time_t updatedAt);

    /**
     * @brief Gets the formatted last updated timestamp as a string.
     * @return The formatted last updated time (e.g., "2025/03/04 12:00:00").
     */
    std::string getUpdatedAtFormatted() const;

    /**
     * @brief Converts the task to a human-readable string representation.
     * @return A string describing the task's attributes.
     */
    std::string toString() const;

    /**
     * @brief Converts the task to a JSON-formatted string.
     * @return A JSON string representing the task's attributes.
     */
    std::string toJSON() const;

private:

    /**
     * @brief Formats a timestamp into a human-readable string.
     * @param time The timestamp to format.
     * @return The formatted time string (e.g., "2025/03/04 12:00:00").
     */
    std::string formatTime(std::time_t time) const;
};

#endif
