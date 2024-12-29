#include "authentication.h"
#include "utility.h"
#include "common_operations.h"

// Function to register a new user
int register_user(const char *role, char *username) {
    char command[200];
    char group_name[20];

    // Ask for the username
    printf("Enter username to register: ");
    scanf("%s", username);

    // Determine the group based on the role
    if (strcmp(role, "member") == 0) {
        strcpy(group_name, "members");
    } else if (strcmp(role, "visitor") == 0) {
        strcpy(group_name, "visitors");
    } else {
        printf("Invalid role specified. Registration aborted.\n");
        log_action("Invalid role specified during registration.");
        return 0;
    }

    // Create the system user and assign to the group
    snprintf(command, sizeof(command), "sudo useradd -g %s %s", group_name, username);
    if (system(command) != 0) {
        printf("Failed to create user '%s'. Ensure you have sudo privileges.\n", username);
        log_action("Failed to create user.");
        return 0;
    }

    snprintf(command, sizeof(command), "sudo usermod -aG %s %s", group_name, username);
    if (system(command) != 0) {
        printf("Failed to create user '%s'. Ensure you have sudo privileges.\n", username);
        log_action("Failed to create user.");
        return 0;
    }

    // Set the password interactively
    snprintf(command, sizeof(command), "sudo passwd %s", username);
    printf("Set a password for user '%s':\n", username);
    if (system(command) != 0) {
        printf("Failed to set password for user '%s'.\n", username);
        log_action("Failed to set password.");
        return 0;
    }

    // Log successful user creation
    char log_entry[100];
    snprintf(log_entry, sizeof(log_entry), "User '%s' created successfully with role '%s'.", username, role);
    log_action(log_entry);

    printf("User '%s' registered successfully with role '%s'.\n", username, role);
    return 1;
}


// Helper function to create member-specific files and directories
bool setup_member_files(const char *username) {
    char path[256];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char join_date[20];

    // Format the current date as YYYY-MM-DD
    strftime(join_date, sizeof(join_date), "%Y-%m-%d", t);

    // Path to members_data file
    snprintf(path, sizeof(path), "librarian/members_data/%s.txt", username);
    if (!create_file(path)) {
        printf("Failed to create member data file for '%s'.\n", username);
        log_action("Failed to create member data file.");
        return false;
    }

    // Write default content to the member data file
    FILE *file = fopen(path, "w");
    if (!file) {
        printf("Failed to write to member data file for '%s'.\n", username);
        log_action("Failed to write to member data file.");
        return false;
    }
    fprintf(file, "username: %s\njoin date: %s\nnumber of borrowed books: 0\n", username, join_date);
    fclose(file);
    log_action("Member data file created successfully.");

    // Set ownership and permissions for members_data file
    char command[300];
    snprintf(command, sizeof(command), "sudo chown %s:librarian %s", username, path);
    if (system(command) != 0) {
        printf("Failed to change ownership for '%s'.\n", path);
        log_action("Failed to change ownership.");
        return false;
    }
    if (chmod(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) != 0) {
        printf("Failed to change permissions for '%s'.\n", path);
        log_action("Failed to change permissions.");
        return false;
    }

    // Path to the member's personal directory
    snprintf(path, sizeof(path), "members/%s", username);
    if (!create_directory(path)) {
        printf("Failed to create directory for member '%s'.\n", username);
        log_action("Failed to create member directory.");
        return false;
    }
    log_action("Member directory created successfully.");

    // Set ownership and permissions for member's personal directory
    snprintf(command, sizeof(command), "sudo chown %s:librarian %s", username, path);
    if (system(command) != 0) {
        printf("Failed to change ownership for '%s'.\n", path);
        log_action("Failed to change ownership.");
        return false;
    }
    if (chmod(path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP) != 0) {
        printf("Failed to change permissions for '%s'.\n", path);
        log_action("Failed to change permissions.");
        return false;
    }

    // Remove access for others
    snprintf(command, sizeof(command), "sudo chmod o-rwx %s", path);
    if (system(command) != 0) {
        printf("Failed to restrict permissions for '%s'.\n", path);
        log_action("Failed to restrict permissions.");
        return false;
    }

    // Create subdirectories and files in the member's directory
    snprintf(path, sizeof(path), "members/%s/borrowed_books", username);
    if (!create_directory(path)) {
        printf("Failed to create borrowed_books directory for '%s'.\n", username);
        log_action("Failed to create borrowed_books directory.");
        return false;
    }
    log_action("Borrowed_books directory created successfully.");

    snprintf(path, sizeof(path), "members/%s/account_details.txt", username);
    if (!create_file(path)) {
        printf("Failed to create account_details.txt for '%s'.\n", username);
        log_action("Failed to create account_details.txt.");
        return false;
    }
    file = fopen(path, "w");
    if (!file) {
        printf("Failed to write to account_details.txt for '%s'.\n", username);
        log_action("Failed to write to account_details.txt.");
        return false;
    }
    fprintf(file, "username: %s\njoin date: %s\nnumber of borrowed books: 0\n", username, join_date);
    fclose(file);
    log_action("Account details file created successfully.");

    snprintf(path, sizeof(path), "members/%s/borrowing_history.txt", username);
    if (!create_file(path)) {
        printf("Failed to create borrowing_history.txt for '%s'.\n", username);
        log_action("Failed to create borrowing_history.txt.");
        return false;
    }
    log_action("Borrowing history file created successfully.");

    return true;
}


// Function to register a visitor
int register_visitor() {
    char username[50];
    int result = register_user("visitor", username);
    if (result) {
        char log_entry[100];
        snprintf(log_entry, sizeof(log_entry), "visitor '%s' registered successfully.", username);
        log_action(log_entry);
    }
    return result;
}

// Function to register a member
int register_member() {
    char username[50];
    if (!register_user("member", username)) {
        return 0;
    }

    // Set up member-specific files and directories
    if (!setup_member_files(username)) {
        printf("Failed to set up member files for '%s'.\n", username);
        log_action("Failed to set up member files.");
        return 0;
    }

    char log_entry[100];
    snprintf(log_entry, sizeof(log_entry), "Member '%s' registered successfully.", username);
    log_action(log_entry);
    printf("Member '%s' registered successfully.\n", username);
    return 1;
}


// function to register librarian, only use once
int register_librarian() {
    char username[50];
    int result = register_user("librarian", username);
    if (result) {
        char log_entry[100];
        snprintf(log_entry, sizeof(log_entry), "librarian '%s' registered successfully.", username);
        log_action(log_entry);
    }
    return result;
}