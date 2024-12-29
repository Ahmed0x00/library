#include "utility.h"

// Logs an action with a timestamp and user information

void log_action(const char *message)
{
    FILE *file;
    char timestamp[20];
    char log_entry[512];

    // Get the current time
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    // Create the log entry
    snprintf(log_entry, sizeof(log_entry), "[%s] %s\n", timestamp, message);

    // Open the file in append mode
    file = fopen("librarian/logs.txt", "a");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Write the log entry
    if (fputs(log_entry, file) == EOF)
    {
        perror("Error writing to file");
    }

    // Close the file
    fclose(file);
}

// Create a file or directory
void create_file_or_directory()
{
    int choice;
    char path[256];

    printf("1. Create a File\n");
    printf("2. Create a Directory\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the path: ");
    scanf("%s", path);

    if (choice == 1)
    {
        if (create_file(path))
        {
            printf("File created successfully: %s\n", path);
            log_action("Created a file.");
        }
        else
        {
            printf("Failed to create file: %s\n", path);
            log_action("Failed to create a file.");
        }
    }
    else if (choice == 2)
    {
        if (create_directory(path))
        {
            printf("Directory created successfully: %s\n", path);
            log_action("Created a directory.");
        }
        else
        {
            printf("Failed to create directory: %s\n", path);
            log_action("Failed to create a directory.");
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

// Delete a file or directory
void delete_file_or_directory()
{
    int choice;
    char path[256];

    printf("1. Delete a File\n");
    printf("2. Delete a Directory\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter the path: ");
    scanf("%s", path);

    if (choice == 1)
    {
        if (delete_file(path))
        {
            printf("File deleted successfully: %s\n", path);
            log_action("Deleted a file.");
        }
        else
        {
            printf("Failed to delete file: %s\n", path);
            log_action("Failed to delete a file.");
        }
    }
    else if (choice == 2)
    {
        if (delete_directory(path))
        {
            printf("Directory deleted successfully: %s\n", path);
            log_action("Deleted a directory.");
        }
        else
        {
            printf("Failed to delete directory: %s\n", path);
            log_action("Failed to delete a directory.");
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}

// Copy a file or directory
void copy_file_or_directory()
{
    char source[256], destination[256];

    printf("Enter source path: ");
    scanf("%s", source);

    printf("Enter destination path: ");
    scanf("%s", destination);

    if (copy_file(source, destination))
    {
        printf("File/Directory copied successfully from %s to %s\n", source, destination);
        log_action("Copied a file or directory.");
    }
    else
    {
        printf("Failed to copy file/directory.\n");
        log_action("Failed to copy a file or directory.");
    }
}

void create_alias()
{
    char alias_name[50], command[200], shell_command[300];
    char shell_config[100];

    // Get alias name and command from the user
    printf("Enter alias name: ");
    scanf("%s", alias_name);
    printf("Enter command for alias: ");
    scanf(" %[^\n]", command); // Read a full line with spaces

    // Format the alias command
    snprintf(shell_command, sizeof(shell_command), "alias %s='%s'", alias_name, command);

    // Append the alias to the appropriate shell configuration file
    snprintf(shell_config, sizeof(shell_config), "%s/.zshrc", getenv("HOME")); // Use .zshrc for zsh

    FILE *file = fopen(shell_config, "a");
    if (file)
    {
        fprintf(file, "\n%s\n", shell_command);
        fclose(file);
        printf("Alias '%s' added to %s successfully.\n", alias_name, shell_config);
        log_action("Alias added to .zshrc successfully.");
    }
    else
    {
        perror("Error opening .zshrc file");
        log_action("Failed to open .zshrc file.");
    }

    // Notify the user to reload their zsh configuration
    printf("Please run the following command to apply the changes immediately:\n");
    printf("source ~/.zshrc\n");
}
