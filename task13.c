#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_command(char* command) {
    // Fork a child process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        // Split the command into individual arguments
        char* args[256];
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Execute the command
        execvp(args[0], args);

        // If execvp fails, print an error message and exit
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        // Forking failed, print an error message and exit
        perror("fork");
        exit(1);
    } else {
        // Parent process
        // Wait for the child process to complete
        int status;
        waitpid(pid, &status, 0);

        // Check if the command exited with a non-zero status
        if (WEXITSTATUS(status) != 0) {
            printf("Command failed with return code %d\n", WEXITSTATUS(status));
        } else {
            printf("Command succeeded with return code %d\n", WEXITSTATUS(status));
        }
    }
}

int main() {
    while (1) {
        // Get user input
        char command[256];
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin);

        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Check if command contains '&&' logical operator
        char* and_operator = strstr(command, "&&");
        if (and_operator != NULL) {
            *and_operator = '\0';  // Replace '&&' with null terminator
            execute_command(command);
            // If the first command succeeded, execute the second command
            if (WEXITSTATUS(system(command)) == 0) {
                execute_command(and_operator + 2);  // Skip '&&'
            }
        }
        // Check if command contains '||' logical operator
        else {
            char* or_operator = strstr(command, "||");
            if (or_operator != NULL) {
                *or_operator = '\0';  // Replace '||' with null terminator
                execute_command(command);
                // If the first command failed, execute the second command
                if (WEXITSTATUS(system(command)) != 0) {
                    execute_command(or_operator + 2);  // Skip '||'
                }
            }
            // If no logical operator found, execute the command as is
            else {
                execute_command(command);
            }
        }
    }

    return 0;
}
