#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_ARG_LEN 256

// Function to replace variables in command
void replaceVariables(char *command, int status, int pid) {
    char statusStr[16];
    char pidStr[16];

    // Convert status and pid to string
    snprintf(statusStr, sizeof(statusStr), "%d", status);
    snprintf(pidStr, sizeof(pidStr), "%d", pid);

    // Replace "$?" with status value
    char *statusPtr = strstr(command, "$?");
    while (statusPtr != NULL) {
        strncpy(statusPtr, statusStr, strlen(statusStr));
        statusPtr = strstr(command, "$?");
    }

    // Replace "$$" with pid value
    char *pidPtr = strstr(command, "$$");
    while (pidPtr != NULL) {
        strncpy(pidPtr, pidStr, strlen(pidStr));
        pidPtr = strstr(command, "$$");
    }
}

int main() {
    char input[MAX_ARGS * MAX_ARG_LEN];
    char *args[MAX_ARGS];
    int status = 0;
    int pid = getpid();

    while (1) {
        printf("$ ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline character
        input[strcspn(input, "\n")] = '\0';

        // Tokenize input into arguments
        char *token = strtok(input, " ");
        int argCount = 0;
        while (token != NULL) {
            args[argCount++] = token;
            token = strtok(NULL, " ");
        }
        args[argCount] = NULL;

        // Check for exit command
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        // Fork to create child process
        pid_t childPid = fork();
        if (childPid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (childPid == 0) {
            // Child process
            // Replace variables in command
            replaceVariables(args[0], status, pid);
            // Execute command
            execvp(args[0], args);
            perror("Command failed");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            // Wait for child process to complete
            waitpid(childPid, &status, 0);
        }
    }

    return 0;
}
