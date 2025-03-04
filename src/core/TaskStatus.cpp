#include "core/TaskStatus.h"

namespace {

    const std::unordered_map<TaskStatus, std::string> statusLabelMap = {
        {TaskStatus::DONE, "Done"},
        {TaskStatus::TODO, "Todo"},
        {TaskStatus::IN_PROGRESS, "In progress"},
        {TaskStatus::DELETED, "Deleted"},
    };

    const std::unordered_map<TaskStatus, std::string> statusKeyMap = {
        {TaskStatus::DONE, "done"},
        {TaskStatus::TODO, "todo"},
        {TaskStatus::IN_PROGRESS, "in_progress"},
        {TaskStatus::DELETED, "deleted"},
    };

}

namespace TaskUtils {

    std::string statusToLabel(TaskStatus status) {
      if(auto i = statusLabelMap.find(status); i != statusLabelMap.end()) {
        return i->second;
      }
      return "Unknown";
    }

    std::string statusToKey(TaskStatus status) {
      if(auto i = statusKeyMap.find(status); i != statusKeyMap.end()) {
        return i->second;
      }
      return "unknown";
    }

    TaskStatus keyToStatus(const std::string& key) {
      for(const auto& [iStatus, iKey] : statusKeyMap) {
        if (iKey == key){
          return iStatus;
        }
      }
      return TaskStatus::UNKNOWN;
    }

}