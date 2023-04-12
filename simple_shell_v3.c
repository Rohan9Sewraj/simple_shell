#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64
#define PATH_SIZE 1024

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char buffer[BUFFER_SIZE]; // Buffer to store user input
    char *args[MAX_ARGS];     // Array to store command line arguments
    int n;                    // Number of characters read by getline
    char path[PATH_SIZE];    // Buffer to store PATH environment variable

    while (1)
    {
        printf("#cisfun$ "); // Display prompt
        n = read(STDIN_FILENO, buffer, BUFFER_SIZE); // Read user input

        if (n == -1)
        {
            perror("read"); // Handle read error
            exit(EXIT_FAILURE);
        }
        else if (n == 0)
        {
            printf("\n"); // Print newline for Ctrl+D (end of file)
            break;
        }

        buffer[n - 1] = '\0'; // Remove newline character from input

        char *token; // Token to store individual arguments
        int i = 0;   // Counter for number of arguments

        // Parse input into arguments using whitespace as delimiter
        token = strtok(buffer, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the arguments array

        pid_t pid = fork(); // Fork a child process

        if (pid == -1)
        {
            perror("fork"); // Handle fork error
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            // Get the PATH environment variable
            char *path_env = getenv("PATH");
            if (path_env == NULL)
            {
                perror("getenv"); // Handle getenv error
                exit(EXIT_FAILURE);
            }

            // Copy the PATH environment variable to a separate buffer
            strncpy(path, path_env, PATH_SIZE - 1);
            path[PATH_SIZE - 1] = '\0';

            char *dir; // Token to store individual directories in PATH

            // Parse the PATH into individual directories using ':' as delimiter
            dir = strtok(path, ":");
            while (dir != NULL)
            {
                // Create a temporary buffer to store the full path of the command
                char cmd_path[PATH_SIZE];
                snprintf(cmd_path, PATH_SIZE, "%s/%s", dir, args[0]);

                // Check if the command exists at the current directory in PATH
                if (access(cmd_path, X_OK) == 0)
                {
                    // Execute the command with arguments
                    if (execvp(cmd_path, args) == -1)
                    {
                        perror("execvp"); // Handle execvp error
                        exit(EXIT_FAILURE);
                    }
                }

                dir = strtok(NULL, ":");
            }

            // If the command was not found in any directory in PATH, exit child process
            printf("%s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for child process to complete
        }
    }

    return 0;
}
