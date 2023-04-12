#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 1024

void execute_command(const char *cmd) {
    // You can implement the logic to execute the command here
    // For example, using system() or execvp() functions
    printf("Executing command: %s\n", cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char cmd[MAX_CMD_LEN];
    while (fgets(cmd, MAX_CMD_LEN, file) != NULL) {
        // Remove trailing newline character
        cmd[strcspn(cmd, "\n")] = '\0';

        execute_command(cmd);
    }

    fclose(file);
    return 0;
}
