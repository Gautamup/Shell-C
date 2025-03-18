# SHL

SHL is a basic command-line shell implemented in C. It supports built-in commands like `cd`, `help`, and `exit`, along with the ability to execute external commands.

## Features
- Reads and parses user input.
- Executes built-in commands (`cd`, `help`, `exit`).
- Launches external programs using `execvp()`.

## Getting Started

### Prerequisites
- A C compiler (e.g., `gcc`).
- A Unix-based system (Linux/macOS).

### Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/Gautamup/Shell-C
   ```
2. Navigate to the project directory:
   ```sh
   cd Shell-C
   ```
3. Compile the shell:
   ```sh
   gcc -o main main.c
   ```
4. Run the shell:
   ```sh
   ./main
   ```

## Usage
- Type commands as you would in a regular terminal:
  ```sh
  > ls -l
  > cd ..
  > echo "Hello, World!"
  > exit
  ```
- Use `help` to see available built-in commands:
  ```sh
  > help
  ```

## Built-in Commands
| Command  | Description |
|----------|------------|
| `cd`     | Change directory |
| `help`   | Display help information |
| `exit`   | Exit the shell |

## Future Enhancements
- **Pipelining (`|`) and redirection (`>`, `<`)**.
- **Background process handling (`&`)**.
- **Improved error handling** for invalid commands.
## Contributing
Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature-name`).
3. Commit your changes (`git commit -m "Add new feature"`).
4. Push to your branch (`git push origin feature-name`).
5. Create a Pull Request.
