# minishell 🧑‍💻

## Thanks to Minishell, we were able to travel through time and come back to problems people faced when Windows didn’t exist

### This project involved creating a basic Unix shell with capabilities such as command parsing and execution, signal handling, environment variable management, support for pipes and redirections, and implementation of built-in commands

![Minishell GIF](https://i.imgur.com/Wo8GYQ7.gif)

## How to use it
Use `make` to create the executable and run it using:
```bash
./minishell
```
After that you can execute any command just like you would do in your terminal.

On a Linux environment, you can change the variable in the `permission` file inside `/assets/` to 1, and the minishell will open on a new window.

## List of requirements 🫡

- Have a working history
- Handle `’` (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$` (dollar sign).
- Implement redirections:
    - `<` should redirect input.
    - `>` should redirect output.
    - `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    - `>>` should redirect output in append mode.
- Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
    - `ctrl-C` displays a new prompt on a new line.
    - `ctrl-D` exits the shell.
    - `ctrl-\` does nothing.
- Implement the following builtins:
    - `echo` with option `-n`
    - `cd` with only a relative or absolute path
    - `pwd` with no options
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

## Bonus features 💡

- `&&` and `||` with parenthesis for priorities.
- Wildcards `*` work for the current working directory.

## Grade 🏆
![Minishell Score](https://i.imgur.com/BVdCiaq.png)