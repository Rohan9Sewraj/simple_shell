#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGS 64
#define DELIM " \t\r\n\a"

static char input[MAX_COMMAND_LENGTH];
static int input_len = 0;
static int input_pos = 0;

/**
 * @brief Custom implementation of getline function.
 *
 * @param line Pointer to a buffer to store the input line.
 * @param len Maximum length of the input line.
 * @return The number of characters read, or -1 on error.
 */
ssize_t custom_getline(char *line, size_t len) {
    if (input_pos >= input_len) {
        input_len = read(STDIN_FILENO, input, MAX_COMMAND_LENGTH);
        if (input_len <= 0) {
            return -1;
        }
        input_pos = 0;
    }

    int i = 0;
    while (input_pos < input_len && i < len - 1) {
        if (input[input_pos] == '\n') {
            line[i++] = input[input_pos++];
            break;
        }
        line[i++] = input[input_pos++];
    }
    line[i] = '\0';

    return i;
}

/**
 * @brief Splits a string into tokens based on delimiter characters.
 *
 * @param line The input string to be tokenized.
 * @param tokens Array of strings to store the resulting tokens.
 * @return The number of tokens.
 */
int tokenize(char *line, char *tokens[]) {
    int num_tokens = 0;
    char *token = strtok(line, DELIM);
    while (token != NULL && num_tokens < MAX_NUM_ARGS - 1) {
        tokens[num_tokens++] = token;
        token = strtok(NULL, DELIM);
    }
    tokens[num_tokens] = NULL;
    return num_tokens;
}

int main() {
    char args[MAX_NUM_ARGS][MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");
        fflush(stdout);

        ssize_t len = custom_getline(input, MAX_COMMAND_LENGTH);
        if (len == -1) {
            break;
        }

        int num_args = tokenize(input, args);

        if (num_args > 0) {
            // Check for built-in commands
            if (strcmp(args[0], "exit") == 0) {
                exit(0);
            } else if (strcmp(args[0], "env") == 0) {
                // Print the current environment
                extern char **environ;
                for (char **env = environ; *env != NULL; env++) {
                    printf("%s\n", *env);
                }
                continue;
            }

            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(1);
            } else if (pid == 0) {
                // Child process
                execvp(args[0], args);
                perror("execvp");
                exit(1);
            } else {
                // Parent process
                wait(NULL);
            }
        }
    }

    return 0;
}
