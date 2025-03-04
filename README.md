# Task Tracker

**Track tasks using your CLI, built with C++**

Task Tracker is a command-line interface (CLI) tool designed to help you manage your tasks efficiently. Written in C++, it allows you to add, update, delete, and track the status of tasks, storing them persistently in a `tasks.json` file in your current directory. This project was built to practice programming skills such as filesystem operations, user input handling, and CLI application development, meeting the following requirements:

- Add, update, and delete tasks.
- Mark tasks as in-progress or done.
- List all tasks or filter by status (todo, in-progress, done).
- Store tasks in a JSON file, created automatically if it doesn't exist.
- Use only the C++ Standard Library (no external dependencies).
- Handle errors and edge cases gracefully.

## Getting Started

### Prerequisites
- A terminal to run the application.
- For manual builds: A C++ compiler (e.g., `g++`, `clang++`) supporting C++20 or later.

### Installation
You can either download a pre-built binary or build the project manually.

#### Option 1: Download Pre-Built Binaries
Download the executable for your operating system from the [GitHub Releases page](https://github.com/mishevski-k/task-tracker/releases):
- [Windows](https://github.com/mishevski-k/task-tracker/releases/latest/download/task-cli-windows.zip)
- [MacOS](https://github.com/mishevski-k/task-tracker/releases/latest/download/task-cli-macos.zip)
- [Linux](https://github.com/mishevski-k/task-tracker/releases/latest/download/task-cli-linux.zip)

1. Download the Zip.
2. Extract It
3. Place it in a directory of your choice.
4. Open a terminal in that directory and run the commands below.

#### Option 2: Build Manually
1. Clone or download the source code:
   ```bash
   git clone https://github.com/yourusername/task-tracker.git
   cd task-tracker

2. Compile the project:
    ```bash
   g++ -std=c++20 -o task-cli main.cpp core/Task.cpp core/TaskManager.cpp core/TaskStatus.cpp cli/Commands.cpp
   
3. Run the executable:
    ```bash
   ./task-cli

#### Usage
Run the app with task-cli (Windows) or ./task-cli (MacOS/Linux) from the directory containing the executable. Below are the supported commands:

    # Adding a new task
    task-cli add "Buy groceries"
    # Output: Task Created: Task: ( id: 1, status: Todo, description: Buy groceries, createdAt: 2025/03/04 12:00:00, updatedAt: 2025/03/04 12:00:00 )
    
    # Updating a task
    task-cli update 1 "Buy groceries and cook dinner"
    # Output: Task Updated: Task: ( id: 1, status: Todo, description: Buy groceries and cook dinner, createdAt: 2025/03/04 12:00:00, updatedAt: 2025/03/04 12:05:00 )
    
    # Deleting a task
    task-cli delete 1
    # Output: Task Deleted: ID 1
    
    # Marking a task as in progress or done
    task-cli mark-in-progress 1
    # Output: Task Changed to: In progress
    #         Task: ( id: 1, status: In progress, description: Buy groceries and cook dinner, createdAt: 2025/03/04 12:00:00, updatedAt: 2025/03/04 12:10:00 )
    task-cli mark-done 1
    # Output: Task Changed to: Done
    #         Task: ( id: 1, status: Done, description: Buy groceries and cook dinner, createdAt: 2025/03/04 12:00:00, updatedAt: 2025/03/04 12:15:00 )
    
    # Listing all tasks
    task-cli list
    
    # Listing tasks by status
    task-cli list done
    task-cli list todo
    task-cli list in-progress


**Note**: Depending on your OS, use `task-cli` (Windows) or `./task-cli` (MacOS/Linux). You must be in the directory containing the executable.

## Task Properties

Each task stored in `tasks.json` has the following properties:

- `id`: A unique integer identifier.
- `description`: A short text description of the task.
- `status`: The task's status (`todo`, `in_progress`, or `done`).
- `createdAt`: The timestamp of creation (Unix epoch time).
- `updatedAt`: The timestamp of the last update (Unix epoch time).

### Example `tasks.json`:

```json
[
    {"id": 1, "description": "Buy groceries", "status": "todo", "createdAt": 1677654321, "updatedAt": 1677654321},
    {"id": 2, "description": "Write README", "status": "in_progress", "createdAt": 1677654380, "updatedAt": 1677654500}
]
````

## Project Requirements

This project was built to meet the following specifications:

- **CLI Interface**: Runs from the command line with positional arguments.
- **JSON Storage**: Tasks are saved in a `tasks.json` file, created if it doesn’t exist.
- **Native Filesystem**: Uses C++ Standard Library `<fstream>` for file operations.
- **No External Libraries**: Relies solely on the C++ Standard Library.
- **Error Handling**: Manages invalid inputs, missing files, and other edge cases.

### Task Description

Task Tracker is a CLI tool to track what you need to do, what you have done, and what you are currently working on. It helps practice programming skills like filesystem interaction, user input handling, and CLI development.

## Contributing

Contributions are welcome! Fork the [repository](https://github.com/mishevski-k/task-tracker), submit issues, or create pull requests to enhance Task Tracker.

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). See the `LICENSE` file for details.

### Project Url 

 [Task Tracker](https://roadmap.sh/projects/task-tracker) by [RoadMap.sh](https://roadmap.sh/)

Happy task tracking!