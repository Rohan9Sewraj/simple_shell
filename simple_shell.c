#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char buffer[BUFFER_SIZE];  // Buffer to store user input
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

		pid_t pid = fork();  // Create child process

		if (pid == -1)
		{
			perror("fork");  // Handle fork error
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// Child process
			if (execve(buffer, NULL, NULL) == -1)
			{
				perror("execve");  // Handle execve error
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// Parent process
			wait(NULL);  // Wait for child process to finish
		}
	}

	return (0);
}
