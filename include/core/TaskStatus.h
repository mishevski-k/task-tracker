#ifndef TASK_STATUS_H
#define TASK_STATUS_H

#include <string>
#include <unordered_map>

enum class TaskStatus{
  TODO, IN_PROGRESS, DONE, DELETED, UNKNOWN
};

namespace TaskUtils{
  std::string statusToLabel(TaskStatus status);
  std::string statusToKey(TaskStatus status);
  TaskStatus keyToStatus(const std::string& key);
}

#endif