cmake_minimum_required(VERSION 3.29)
project(task_tracker)
enable_testing()

# Unknown action command
add_test(NAME TestUnknownAction COMMAND task-cli)
set_tests_properties(TestUnknownAction PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task.cli <action>")

# Add action without description
add_test(NAME TestAddNoDescriptionCommand COMMAND task-cli add)
set_tests_properties(TestAddNoDescriptionCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli add <description>")

# Add action with description
add_test(NAME TestAddCommand COMMAND task-cli add "Created")
set_tests_properties(TestAddCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task Created:")

# Update action without id
add_test(NAME TestUpdateWithoutIdCommand COMMAND task-cli update)
set_tests_properties(TestUpdateWithoutIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli update <id>")

# Update action without description
add_test(NAME TestUpdateWithoutDescriptionCommand COMMAND task-cli update 1)
set_tests_properties(TestUpdateWithoutDescriptionCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli update <id> <description>")

# Update action with non-existing-id
add_test(NAME TestUpdateNonExistingIdCommand COMMAND task-cli update 999 "updated" )
set_tests_properties(TestUpdateNonExistingIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task not found")

# Update action with correct params
add_test(NAME TestUpdateCommand COMMAND task-cli update 1 "updated")
set_tests_properties(TestUpdateCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task Updated:")

# Delete action without id
add_test(NAME TestDeleteWithoutIdCommand COMMAND task-cli delete )
set_tests_properties(TestDeleteWithoutIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli delete <id>")

# Delete action with non-existing id
add_test(NAME TestDeleteNonExistingIdCommand COMMAND task-cli delete 999 )
set_tests_properties(TestDeleteNonExistingIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task not found")

# Delete action with correct params
add_test(NAME TestDeleteCommand COMMAND task-cli delete 1 )
set_tests_properties(TestDeleteCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task Deleted:")

# Mark task as Done without id
add_test(NAME MarkDoneWithoutIdCommand COMMAND task-cli mark-done )
set_tests_properties(MarkDoneWithoutIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli mark-done <id>")

# Mark task as In-Progress without id
add_test(NAME MarkInProgressWithoutIdCommand COMMAND task-cli mark-in-progress )
set_tests_properties(MarkInProgressWithoutIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Usage: ./task-cli mark-in-progress <id>")

# Mark task as Done non-existing id
add_test(NAME MarkDoneNonExistingIdCommand COMMAND task-cli mark-done 999)
set_tests_properties(MarkDoneNonExistingIdCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task not found")

# Mark task as Done
add_test(NAME MarkDoneCommand COMMAND task-cli mark-done 1)
set_tests_properties(MarkDoneCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task Changed to: Done")

# Mark task as in-progress
add_test(NAME MarkInProgressCommand COMMAND task-cli mark-in-progress 1)
set_tests_properties(MarkInProgressCommand PROPERTIES PASS_REGULAR_EXPRESSION "Task Changed to: In progres")

# Action not found
add_test(NAME UnknownActionCommand COMMAND task-cli unknown-domman )
set_tests_properties(UnknownActionCommand PROPERTIES PASS_REGULAR_EXPRESSION "Unknown action:")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(task-cli main.cpp)

# Set different output directories based on build type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
else()
    set_target_properties(task-cli PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
endif()