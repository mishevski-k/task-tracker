#ifndef TASK_STATUS_H
#define TASK_STATUS_H

#include <string>
#include <unordered_map>

/**
 * @enum TaskStatus
 * @brief Represents the possible states of a task.
 *
 * This enum defines the lifecycle states a task can have in a task management system.
 * It includes common statuses like TODO, IN_PROGRESS, and DONE, as well as DELETED and UNKNOWN
 * for handling edge cases or invalid states.
 */
enum class TaskStatus{
  TODO, ///< Task is yet to be started.
  IN_PROGRESS, ///< Task is currently being worked on.
  DONE, ///< Task has been completed.
  DELETED, ///< Task has been marked as deleted.
  UNKNOWN //< Task status is not recognized or invalid.
};

/**
 * @namespace TaskUtils
 * @brief Provides utility functions for converting TaskStatus values to strings and vice versa.
 *
 * This namespace contains helper functions to work with the TaskStatus enum, including
 * converting statuses to human-readable labels, machine-readable keys, and parsing keys
 * back to TaskStatus values.
 */
namespace TaskUtils{

  /**
   * @brief Converts a TaskStatus enum value to a human-readable label.
   * @param status The TaskStatus value to convert.
   * @return A string label (e.g., "Todo", "In progress", "Done"), or "Unknown" if not found.
   */
  std::string statusToLabel(TaskStatus status);
  /**
   * @brief Converts a TaskStatus enum value to a machine-readable key.
   * @param status The TaskStatus value to convert.
   * @return A string key (e.g., "todo", "in_progress", "done"), or "unknown" if not found.
   */
  std::string statusToKey(TaskStatus status);

  /**
   *
   * @brief Converts a machine-readable key to a TaskStatus enum value.
   * @param key The string key to parse (e.g., "todo", "done").
   * @return The corresponding TaskStatus value, or TaskStatus::UNKNOWN if not recognized.
   */
  TaskStatus keyToStatus(const std::string& key);
}

#endif