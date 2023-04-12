#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char buffer[BUFFER_SIZE];  // Buffer to store user input
    char *args[MAX_ARGS];  // Array to store command line arguments
    int n;  // Number of characters read by getline

    while (1)
    {
        printf("#cisfun$ ");  // Display prompt
        n = read(STDIN_FILENO, buffer, BUFFER_SIZE);  // Read user input

        if (n == -1)
        {
            perror("read");  // Handle read error
            exit(EXIT_FAILURE);
        }
        else if (n == 0)
        {
            printf("\n");  // Print newline for Ctrl+D (end of file)
            break;
        }

        buffer[n - 1] = '\0';  // Remove newline character from input

        char *token;  // Token to store individual arguments
        int i = 0;  // Counter for number of arguments

        // Parse input into arguments using whitespace as delimiter
        token = strtok(buffer, " ");
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // Null-terminate the arguments array

        pid_t pid = fork();  // Fork a child process

        if (pid == -1)
        {
            perror("fork");  // Handle fork error
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process
            if (execvp(args[0], args) == -1)
            {
                perror("execvp");  // Handle execvp error
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            wait(NULL);  // Wait for child process to complete
        }
    }

    return 0;
}
