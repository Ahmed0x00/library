#include "authentication.h"
#include "common_operations.h"
#include "utility.h"

int change_log_ownership(const char *log_file, uid_t user_uid, gid_t user_gid)
{
    // Change ownership of the log file to the specified UID and GID
    if (chown(log_file, user_uid, user_gid) != 0)
    {
        perror("Error changing ownership of logs.txt");
        return 0; 
    }
    return 1;
}

int login(char *logged_in_user)
{
    char username[50], password[50], *encrypted_password, *user_password, command[200];
    struct passwd *user_entry;
    struct spwd *shadow_entry;

    printf("Enter username to log in: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Get the user's passwd entry
    user_entry = getpwnam(username);
    if (!user_entry)
    {
        printf("User '%s' does not exist.\n", username);
        char log_entry[100];
        snprintf(log_entry, sizeof(log_entry), "Failed login attempt for non-existent user '%s'.", username);
        log_action(log_entry);
        return 0;
    }

    // Get the user's shadow password entry (requires root access)
    shadow_entry = getspnam(username);
    if (!shadow_entry)
    {
        printf("Error: Could not access shadow entry for user '%s'.\n", username);
        return 0;
    }

    // Encrypt the entered password and compare it with the stored one
    encrypted_password = crypt(password, shadow_entry->sp_pwdp);
    if (strcmp(encrypted_password, shadow_entry->sp_pwdp) != 0)
    {
        printf("Invalid password for user '%s'.\n", username);
        char log_entry[100];
        snprintf(log_entry, sizeof(log_entry), "Invalid password attempt for user '%s'.", username);
        log_action(log_entry);
        return 0;
    }

    // Change ownership of the logs file
    if (!change_log_ownership("librarian/logs.txt", user_entry->pw_uid, user_entry->pw_gid))
    {
        printf("Warning: Could not change ownership of the log file.\n");
    }

    // Change ownership of the logs file
    if (!change_log_ownership("logged_in.txt", user_entry->pw_uid, user_entry->pw_gid))
    {
        printf("Warning: Could not change ownership of the log file.\n");
    }

    // Switch to the user's privileges
    if (setgid(user_entry->pw_gid) != 0)
    {
        perror("Failed to switch to the user's GID");
        return 0;
    }

    if (setuid(user_entry->pw_uid) != 0)
    {
        perror("Error switching to user privileges");
        return 0;
    }

    // Determine user's role based on their group
    char role[20];
    struct group *grp = getgrgid(user_entry->pw_gid);
    if (grp == NULL) {
        printf("Error: Could not retrieve group information.\n");
        return 0;
    }
    strcpy(role, grp->gr_name);

    // Update the logged-in user information
    strcpy(logged_in_user, username);
    printf("Login successful for user '%s'.\n", username);
    char log_entry[100];
    snprintf(log_entry, sizeof(log_entry), "User '%s' logged in successfully.", username);
    log_action(log_entry);

    // Update logged_in.txt
    update_logged_in_user_and_role(username, role);
    return 1;
}
