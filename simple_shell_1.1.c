#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_NUM_ARGS 64
#define DELIM " \t\r\n\a"

extern char **environ;

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
    char *token = line;
    int in_token = 0;
    while (*line != '\0' && num_tokens < MAX_NUM_ARGS - 1) {
        if (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r' || *line == '\a') {
            *line = '\0';
            in_token = 0;
        } else if (!in_token) {
            tokens[num_tokens++] = token;
            token = line;
            in_token = 1;
        }
        line++;
    }
    tokens[num_tokens++] = token;
    tokens[num_tokens] = NULL;
    return num_tokens;
}

/**
 * @brief Sets the value of an environment variable.
 *
 * @param variable The name of the environment variable to set.
 * @param value The value to set for the environment variable.
 * @return 0 on success, -1 on failure.
 */
int set_environment_variable(const char *variable, const char *value) {
    if (variable == NULL || value == NULL) {
        fprintf(stderr, "Error: Invalid arguments for setenv\n");
        return -1;
    }
    if (setenv(variable, value, 1) != 0) {
        perror("setenv");
        return -1;
    }
    return 0;
}

/**
 * @brief Unsets an environment variable.
 *
 * @param variable The name of the environment variable to unset.
 * @return 0 on success, -1 on failure.
 */
int unset_environment_variable(const char *variable) {
    if (variable == NULL) {
        fprintf(stderr, "Error: Invalid argument for unsetenv\n");
        return -1;
    }
    if (unsetenv(variable) != 0) {
        perror("unsetenv");
       