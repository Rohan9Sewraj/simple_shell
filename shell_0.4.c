#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define PROMPT ":) "

void read_command(char *command);
void parse_command(char *command, char *args[], int *num_args);
void execute_command(char *args[], int num_args);

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    int num_args;

    while (1) {
        printf("%s", PROMPT);
        read_command(command);
        parse_command(command, args, &num_args);

        // Handle exit built-in command
        if (strcmp(args[0], "exit") == 0) {
            printf("Exiting the shell...\n");
            exit(0);
        }

        execute_command(args, num_args);
    }

    return 0;
}

void read_command(char *command) {
    fgets(command, MAX_COMMAND_LENGTH, stdin);
}

void parse_command(char *command, char *args[], int *num_args) {
    char *token;
    *num_args = 0;

    // Tokenize the command string by space
    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[*num_args] = token;
        (*num_args)++;
        token = strtok(NULL, " \t\n");
    }

    args[*num_args] = NULL; // Set last argument to NULL for execvp
}

void execute_command(char *args[], int num_args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        printf("Command not found: %s\n", args[0]);
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(&status);
    } else {
        // Fork failed
        perror("fork");
        exit(1);
    }
}
