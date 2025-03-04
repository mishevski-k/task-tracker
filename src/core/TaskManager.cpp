#include "core/TaskManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

TaskManager::TaskManager(const std::string& storeName) : storeName(storeName) {}

void TaskManager::saveTasksToStore() const {
  std::ofstream file(storeName);
  if(!file){
    throw std::runtime_error("Failed to open store file: " + storeName);
  }

  file << "[";
  bool first = true;
  for(const auto& [id, task] : tasks) {
    if(!first) file << ", ";
    file << task.toJSON();
    first = false;
  }
  file << "]";
  file.close();
}

void TaskManager::loadTasksFromStore() {
  std::ifstream file(storeName);
  if(!file){
    std::ofstream newFile(storeName);
    newFile << "[{\"id\":1,\"description\":\"Create Store\",\"status\":\"todo\",\"createdAt\":0,\"updatedAt\":0}]";
    newFile.close();
    file.open(storeName);
  }

  std::string json, line;
  while(std::getline(file, line)) {
    json += line;
  }
  file.close();

  size_t pos = 0;
  while((pos = json.find("{")) != std::string::npos){
    size_t endPos = json.find("}", pos);
    if(endPos == std::string::npos) break;
    std::string taskStr = json.substr(pos + 1, endPos - pos -1);
    json.erase(0, endPos + 1);

    int id;
    std::string description, statusStr;
    std::time_t createdAt, updatedAt;

    std::istringstream ss(taskStr);
    std::string token;
    while (std::getline(ss, token, ',')) {
      size_t colonPos = token.find(":");
      std::string key = token.substr(1, colonPos - 2);
      std::string value = token.substr(colonPos + 1);
      value.erase(0, value.find_first_not_of(" "));
      value.erase(value.find_last_not_of(" ") + 1);

      if (key == "id") id = std::stoi(value);
      else if (key == "description") description = value.substr(1, value.size() - 2);
      else if (key == "status") statusStr = value.substr(1, value.size() - 2);
      else if (key == "createdAt") createdAt = std::stoll(value);
      else if (key == "updatedAt") updatedAt = std::stoll(value);
    }
    tasks.emplace(id, Task(id, description, TaskUtils::keyToStatus(statusStr), createdAt, updatedAt));
  }
}

std::optional<std::reference_wrapper<Task>> TaskManager::findTaskById(int id) {
  if (auto it = tasks.find(id); it != tasks.end()) {
    return it->second;
  }
  return std::nullopt;
}

void TaskManager::addTask(const Task& task) {
  tasks.emplace(task.getId(), task);
}

void TaskManager::removeTask(int id) {
  tasks.erase(id);
}

const std::map<int, Task>& TaskManager::getTasks() const {
  return tasks;
}