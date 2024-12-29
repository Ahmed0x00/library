#include "authentication.h"
#define LOGGED_IN_FILE "logged_in.txt"

// Function to update the logged-in user's information in logged_in.txt
void update_logged_in_user_and_role(const char *username, const char *role)
{
    FILE *file = fopen(LOGGED_IN_FILE, "w");
    if (file == NULL)
    {
        printf("Error: Could not open %s for writing.\n", LOGGED_IN_FILE);
        return;
    }
    fprintf(file, "Logged in user: %s\n", username);
    fprintf(file, "Role: %s\n", role);
    fclose(file);
}

// Function to get the logged-in user's information from logged_in.txt
int get_logged_in_user_and_role(char *username, char *role)
{
    FILE *file = fopen(LOGGED_IN_FILE, "r");
    if (file == NULL)
    {
        printf("Error: Could not open %s for reading.\n", LOGGED_IN_FILE);
        return 0;
    }
    if (fscanf(file, "Logged in user: %s\nRole: %s\n", username, role) != 2)
    {
        printf("Error: Malformed %s file.\n", LOGGED_IN_FILE);
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}