#include "utility.h"
#include "common_operations.h"

// Create a file using 'touch'
bool create_file(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "touch %s", path);
    return system(command) == 0;
}

// Delete a file using 'rm'
bool delete_file(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "rm -f %s", path);
    return system(command) == 0;
}

// Copy a file using 'cp'
bool copy_file(const char *source, const char *destination) {
    char command[256];
    snprintf(command, sizeof(command), "cp -r %s %s", source, destination);
    return system(command) == 0;
}

// Move a file using 'mv'
bool move_file(const char *source, const char *destination) {
    char command[256];
    snprintf(command, sizeof(command), "mv %s %s", source, destination);
    return system(command) == 0;
}

void view_file_content(char *file_path) {
    char command[10];
    char full_command[266];

    printf("Enter command (cat, head, tail): ");
    scanf("%s", command);

    // Check if the command is valid
    if (strcmp(command, "cat") == 0 || strcmp(command, "head") == 0 || strcmp(command, "tail") == 0) {
        // Construct and execute the command
        snprintf(full_command, sizeof(full_command), "%s %s", command, file_path);
        system(full_command);
        log_action("Viewed file content using cat/head/tail.");
    } else {
        printf("Invalid command. Use 'cat', 'head', or 'tail'.\n");
    }
}

