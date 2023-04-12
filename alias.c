#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIASES 100  // Maximum number of aliases
#define MAX_ALIAS_NAME 50 // Maximum length of alias name
#define MAX_ALIAS_VALUE 50 // Maximum length of alias value

// Structure to store an alias
typedef struct {
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
} Alias;

Alias aliases[MAX_ALIASES]; // Array to store aliases
int numAliases = 0; // Number of aliases currently defined

// Function to print a list of all aliases
void printAliases() {
    for (int i = 0; i < numAliases; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

// Function to print the aliases with given names
void printAliasesByName(char* names[]) {
    for (int i = 0; names[i] != NULL; i++) {
        for (int j = 0; j < numAliases; j++) {
            if (strcmp(names[i], aliases[j].name) == 0) {
                printf("%s='%s'\n", aliases[j].name, aliases[j].value);
                break;
            }
        }
    }
}

// Function to define or update aliases
void defineAlias(char* name, char* value) {
    for (int i = 0; i < numAliases; i++) {
        if (strcmp(name, aliases[i].name) == 0) {
            strncpy(aliases[i].value, value, MAX_ALIAS_VALUE);
            return;
        }
    }

    if (numAliases < MAX_ALIASES) {
        strncpy(aliases[numAliases].name, name, MAX_ALIAS_NAME);
        strncpy(aliases[numAliases].value, value, MAX_ALIAS_VALUE);
        numAliases++;
    } else {
        printf("Too many aliases defined. Maximum allowed: %d\n", MAX_ALIASES);
    }
}

int main() {
    char input[MAX_ALIAS_NAME + MAX_ALIAS_VALUE + 2]; // +2 for the space and '=' character
    char* token;
    char* name;
    char* value;

    while (1) {
        printf("Enter alias command: ");
        fgets(input, sizeof(input), stdin);

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Parse input command
        token = strtok(input, " ");
        name = token;
        token = strtok(NULL, " ");
        value = token;

        // Execute alias command
        if (strcmp(name, "alias") == 0) {
            if (value == NULL) {
                // Print all aliases
                printAliases();
            } else if (value[0] == '=') {
                // Define or update alias
                defineAlias(name, &value[1]);
            } else {
                // Print aliases with given names
                char* names[MAX_ALIASES];
                int i = 0;
                while (value != NULL) {
                    names[i++] = value;
                    value = strtok(NULL, " ");
                }
                names[i] = NULL;
                printAliasesByName(names);
            }
        } else {
            // Execute other commands or handle aliases
            // ...
        }
    }

    return 0;
}
