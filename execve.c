#include "real_shell.h"

/**
 * Execute a command, searching in built-ins and the file system.
 * @data: Pointer to the ProgramData structure containing program information.
 * Return: 0 on success, -1 on failure.
 */
int execute(ProgramData *data)
{
    int returned_value = 0, status;
    pid_t pid;

    /* Check if the command is a built-in */
    returned_value = is_builtin(data);
    if (returned_value != -1)
    {/* is it a built-in, execute it and return its result */
        return (returned_value);
    }
    // Check if the command exists in the file system
    returned_value = locate_executable_cmd(data);
    if (returned_value)
    { /* Ifis not found, return the error code */
        return (returned_value);
    }
    else
    {/*fork a new process, if found*/
        pid = fork();

        if (pid == -1)
        {/* If fork fails, print an error and exit */
            perror(data->command_name);
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        { /* Child process: execute the program */
            returned_value = execve(data->tokens[0], data->tokens, data->env);

            if (returned_value == -1)
            {
                perror(data->command_name);
                exit(EXIT_FAILURE);
            }
        }
        else
        {/* Parent process: wait for the child to complete and check its exit status */
            wait(&status);
            if (WIFEXITED(status))
                errno = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                errno = 128 + WTERMSIG(status);
        }
    }
    return (0);
}
