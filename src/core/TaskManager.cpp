#include "core/TaskManager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Constructs a TaskManager with an optional store file name.
 * @param storeName The name of the file to persist tasks (defaults to "tasks.json").
 */
TaskManager::TaskManager(const std::string& storeName) : storeName(storeName) {}

/**
 * @brief Saves all tasks to the store file in JSON format.
 * @throws std::runtime_error If the store file cannot be opened for writing.
 * @note Writes tasks as a JSON array, with each task represented as a JSON object.
 */
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

/**
 * @brief Loads tasks from the store file into the tasks map.
 * @note If the file does not exist, creates a default file with an initial task:
 *       {"id":1,"description":"Created Store","status":"todo","createdAt":0,"updatedAt":0}.
 * @note Overwrites any existing tasks in the map with the loaded data.
 * @note Assumes a simple JSON format and may not handle malformed JSON robustly.
 */
void TaskManager::loadTasksFromStore() {
  std::ifstream file(storeName);
  if(!file){
    std::ofstream newFile(storeName);
    newFile << "[{\"id\":1,\"description\":\"Created Store\",\"status\":\"todo\",\"createdAt\":0,\"updatedAt\":0}]";
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

/**
 * @brief Finds a task by its ID.
 * @param id The ID of the task to find.
 * @return An optional reference to the Task if found, or std::nullopt if not.
 */
std::optional<std::reference_wrapper<Task>> TaskManager::findTaskById(int id) {
  if (auto it = tasks.find(id); it != tasks.end()) {
    return it->second;
  }
  return std::nullopt;
}

/**
 * @brief Adds a task to the manager.
 * @param task The Task object to add.
 * @note If a task with the same ID already exists, it will be overwritten.
 */
void TaskManager::addTask(const Task& task) {
  tasks.emplace(task.getId(), task);
}

/**
 * @brief Removes a task by its ID.
 * @param id The ID of the task to remove.
 * @note No effect if the ID does not exist in the tasks map.
 */
void TaskManager::removeTask(int id) {
  tasks.erase(id);
}

/**
 * @brief Gets the collection of all tasks.
 * @return A const reference to the tasks map.
 */
const std::map<int, Task>& TaskManager::getTasks() const {
  return tasks;
}