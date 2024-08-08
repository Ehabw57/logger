# Logger Application

Welcome to the Logger Application! This command-line tool is designed to help you manage employee logs and records efficiently. It supports logging activities, managing employee data, and provides a comprehensive help system.

## Features

- **Log Entries**: Easily record activities with timestamps.
- **Print Logs**: View all recorded log entries.
- **Manage Employees**: Add new employees or remove existing ones.
- **Data Persistence**: Automatically saves and loads logs and employee data from files.
- **Integrated Help**: Access detailed help information for each command.

## Getting Started

### Prerequisites

Ensure you have the following tools installed:

- **GCC**: Required to compile the application.
- **Make**: Used for building the project.

### Installation

1. **Clone the Repository**:

```bash
   git clone https://github.com/ehabw57/logger.git
   cd logger
```

2. **Bulid the project**:

```bash
     make logger
```
## Usage

To run the Logger application, execute:

```bash
./logger
```
Once the application starts, you can use the following commands:


.`log <employee_name>`: Record a log entry for the specified employee. For example:

```bash
log JohnDoe
```
This will create a new log entry for John Doe with the current timestamp.

.`print logs`: Display all log entries stored in the system. Use this command to view the history of all recorded activities.

.`print employees`: List all employees currently in the system. This command provides a numbered list of employee names.

.`add <employee_name>`: Add a new employee to the system. Example usage:

```bash
add JaneSmith
```
This command will add Jane Smith to the list of employees.

.`remove <employee_name>`: Remove an employee from the list. Example usage:

```bash
remove JohnDoe
```
This command will delete John Doe from the employee list if they exist.

.`exit`: Exit the application. This command will terminate the program.

.`help [command]:` Display help information for a specific command or general help. For instance:


## Contributing

We welcome contributions! If you'd like to help improve the Logger application, please consider:

Opening issues for bugs or feature requests.
Submitting pull requests with code improvements.
Providing feedback or suggestions.
For more details, refer to the contributing guidelines.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Thank you for using the Logger Application! For any questions or issues, please visit our GitHub issues page. 