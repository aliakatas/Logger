# Logger
Simple message logger for CLI applications.

The core class definition and implementation can be found in the [Logger](https://github.com/aliakatas/Logger/tree/main/Logger/Logger) directory. 
Examples of using the class can be found in [test_driver](https://github.com/aliakatas/Logger/tree/main/Logger/test_driver) directory.

### Example Output
The Logger can write to stderr or a log file, depending on the object's usage in the code.

Some possible outputs can be:
    $![2021-09-17 18:22:57] This is an event description with a line guard ($!). 
    !![2021-09-17 18:22:57] ERROR: This is an error message with line guard (!! - optional).
    [2021-09-17 18:22:57] WARNING: This is a warning message without a line guard (can have a line guard).
    [2021-09-17 18:22:57] NOTE: This is a note message without a line guard (can have a line guard).
    This is simply a message line.
    [2021-09-21] (A date can be written without further messages)
    [2021-09-17 18:22:57] (A date + time can be written without further messages)
    
The line ending is a newline character by default, but can change during function calls.

    
