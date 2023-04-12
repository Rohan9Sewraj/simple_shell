#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void process_command(char *command) {
    // Remove newline character from the end of the command
    command[strcspn(command, "\n")] = '\0';

    // Check for comments (indicated by '#' character)
    char *comment = strchr(command, '#');
    if (comment != NULL) {
        // If a comment is found, truncate the command at the '#' character
        *comment = '\0';
    }

    // Process the remaining command
    printf("Command: %s\n", command);
    // Add your code here to execute the command
}

int main() {
    char input[MAX_INPUT_SIZE];
    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        if (feof(stdin)) {
            break;
        }
        process_command(input);
    }
    return 0;
}
