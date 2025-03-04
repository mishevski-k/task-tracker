#ifndef TASK_H
#define TASK_H

#include "core/TaskStatus.h"
#include <string>
#include <ctime>

class Task {
private:
  int id;
  std::string description;
  TaskStatus status;
  std::time_t createdAt;
  std::time_t updatedAt;
public:
  Task(int id, std::string description, TaskStatus status, std::time_t createdAt, std::time_t updatedAt);
  int getId() const;
  void setId(int id);
  std::string getDescription() const;
  void setDescription(std::string description);
  TaskStatus getStatus() const;
  std::string getStatusLabel() const;
  std::string getStatusKey() const;
  void setStatus(TaskStatus status);
  std::time_t getCreatedAt() const;
  void setCreatedAt(std::time_t createdAt);
  std::string getCreatedAtFormatted() const;
  std::time_t getUpdatedAt() const;
  void setUpdatedAt(std::time_t updatedAt);
  std::string getUpdatedAtFormatted() const;
  std::string toString() const;
  std::string toJSON() const;
private:
  std::string formatTime(std::time_t time) const;
};

#endif