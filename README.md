# mini-bash

mini-bash is a simple Unix shell designed as a learning and educational project. It supports a variety of basic shell functionalities including command execution, redirections, pipes, built-in commands, environment variable handling, and signal management. This project is primarily written in C, with a small portion of Makefile code for building the project.

## Features

- **Command Execution:** mini-bash can execute built-in commands as well as external binaries available on the system.
- **Redirections:** The shell supports redirection of input and output, enabling users to run commands with files as input or output.
- **Pipes:** Users can chain commands together using pipes, passing the output of one command as the input to the next.
- **Built-ins:** The shell includes common built-in commands which are implemented directly in the program.
- **Environment Variables:** mini-bash reads and manages environment variables, which can be used within the shell or passed to executed programs.
- **Signal Handling:** The shell appropriately handles signals, making it robust against interruptions and ensuring smooth execution of background and foreground processes.

## How It Works

1. **Initialization:** When mini-bash starts, it sets up the environment and initializes necessary variables and signal handlers.
2. **Input Parsing:** It reads user input and parses the command line to identify commands, arguments, and special symbols such as redirection operators or pipes.
3. **Command Execution:** Depending on whether the command is built-in or external, mini-bash either executes the command directly or spawns a child process to run an external binary.
4. **Redirection & Pipes:** The shell processes redirections and pipes by manipulating file descriptors, ensuring that data flows correctly between commands.
5. **Signal Handling:** Special attention is given to signal management, so that signals like SIGINT (Ctrl+C) are correctly interpreted, allowing the shell to maintain stable operation.

## Building and Running

A Makefile is provided for easy compilation. To build the project, simply run:

```bash
make
```

Then, launch the shell with:

```bash
./mini-bash
```

## Project Structure

- **C Source Files:** The bulk of the project is written in C, implementing the core shell functionalities.
- **Makefile:** Contains build instructions for compiling the project.

## Conclusion

mini-bash is a compact and efficient implementation of a Unix shell. It serves as an excellent example of system programming in C and provides a hands-on approach to understanding shell mechanics.

Happy hacking!