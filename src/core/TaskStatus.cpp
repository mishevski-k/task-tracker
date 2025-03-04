#include "core/TaskStatus.h"

namespace {

    /**
     * @brief Maps TaskStatus values to human-readable labels.
     *
     * This unordered_map provides a lookup table for converting TaskStatus enum values
     * to their corresponding display labels. Unmapped statuses default to "Unknown".
     */
    const std::unordered_map<TaskStatus, std::string> statusLabelMap = {
        {TaskStatus::DONE, "Done"},
        {TaskStatus::TODO, "Todo"},
        {TaskStatus::IN_PROGRESS, "In progress"},
        {TaskStatus::DELETED, "Deleted"},
    };

    /**
     * @brief Maps TaskStatus values to machine-readable keys.
     *
     * This unordered_map provides a lookup table for converting TaskStatus enum values
     * to their corresponding keys suitable for serialization or APIs. Unmapped statuses
     * default to "unknown".
     */
    const std::unordered_map<TaskStatus, std::string> statusKeyMap = {
        {TaskStatus::DONE, "done"},
        {TaskStatus::TODO, "todo"},
        {TaskStatus::IN_PROGRESS, "in_progress"},
        {TaskStatus::DELETED, "deleted"},
    };

}

namespace TaskUtils {

    /**
     * @brief Converts a TaskStatus enum value to a human-readable label.
     * @param status The TaskStatus value to convert.
     * @return A string label (e.g., "Todo", "In progress", "Done"), or "Unknown" if not found.
     * @note Uses the statusLabelMap for lookup; returns "Unknown" for unmapped statuses like TaskStatus::UNKNOWN.
     */
    std::string statusToLabel(TaskStatus status) {
      if(auto i = statusLabelMap.find(status); i != statusLabelMap.end()) {
        return i->second;
      }
      return "Unknown";
    }

    /**
     * @brief Converts a TaskStatus enum value to a machine-readable key.
     * @param status The TaskStatus value to convert.
     * @return A string key (e.g., "todo", "in_progress", "done"), or "unknown" if not found.
     * @note Uses the statusKeyMap for lookup; returns "unknown" for unmapped statuses like TaskStatus::UNKNOWN.
     */
    std::string statusToKey(TaskStatus status) {
      if(auto i = statusKeyMap.find(status); i != statusKeyMap.end()) {
        return i->second;
      }
      return "unknown";
    }

    /**
     * @brief Converts a machine-readable key to a TaskStatus enum value.
     * @param key The string key to parse (e.g., "todo", "done").
     * @return The corresponding TaskStatus value, or TaskStatus::UNKNOWN if the key is not recognized.
     * @note Iterates over statusKeyMap to find a matching key; case-sensitive comparison.
     */
    TaskStatus keyToStatus(const std::string& key) {
      for(const auto& [iStatus, iKey] : statusKeyMap) {
        if (iKey == key){
          return iStatus;
        }
      }
      return TaskStatus::UNKNOWN;
    }

}