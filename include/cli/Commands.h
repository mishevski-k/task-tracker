#ifndef COMMANDS_H
#define COMMANDS_H

#include "core/TaskManager.h"

namespace CLI{
    int add(TaskManager& manager, int argc, char* argv[]);
    int update(TaskManager& manager, int argc, char* argv[]);
    int deleteTask(TaskManager& manager, int argc, char* argv[]);
    int changeStatus(TaskManager& manager, int argc, char* argv[], TaskStatus newStatus);
    int list(TaskManager& manager, int argc, char* argv[]);
}

#endif