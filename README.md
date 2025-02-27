
<div style="text-align: center;">
    <h1 style="font-size: 40px; ">
        Task Tracker
    </h1>
    <p style="font-size: 15px; background-color: darkgrey; color: black; border-radius: 10px; width: fit-content; margin: auto; padding: 0 15px;">
        track task using your cli, made with C++
    </p>
</div>

***

<div style="text-align: center;">
    <h1 style="font-size: 35px;">
        Usage
    </h1>
    <p style="font-size: 15px; background-color: darkgrey; color: black; border-radius: 10px; width: fit-content; margin: auto; padding: 7px 15px;">
        Note: depending on OS, you can run the app like this: <span style="background-color: aquamarine; border-radius: 15px; padding: 0 5px;">task-cli</span> or like this <span style="background-color: aquamarine; border-radius: 15px; padding: 0 5px;">./task-cli</span> in your terminal of choice. you need to be in the folder where the executable resides in.
    </p>
</div>

<div style="width: fit-content; margin: auto;">

``` 
# Adding a new task
task-cli add "Buy groceries"
# Output: Task added successfully (ID: 1)

# Updating and deleting tasks
task-cli update 1 "Buy groceries and cook dinner"
task-cli delete 1

# Marking a task as in progress or done
task-cli mark-in-progress 1
task-cli mark-done 1

# Listing all tasks
task-cli list

# Listing tasks by status
task-cli list done
task-cli list todo
task-cli list in-progress
```

</div>

