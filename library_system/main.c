#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "authentication.h"
#include "utility.h"
#include "librarian_functions.h"
#include "member_functions.h"
#include "visitor_functions.h"
#include "common_operations.h"

void display_role_menu(const char *role);

void member_menu() {
    printf("------------\n");
    printf("Member Menu\n");
    printf("------------\n");
}

// Main function
int main()
{
    log_action("Library Management System Started");
    int choice;

    do
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            // Login logic
            char username[50];
            char role[50];

            if (login(username))
            {
                printf("Welcome, %s!\n", username);

                // Retrieve the logged-in user's role
                if (get_logged_in_user_and_role(username, role))
                {
                    display_role_menu(role); // Call role-specific menu
                }
                else
                {
                    printf("Error retrieving logged-in user details. Returning to Main Menu.\n");
                }
            }
            else
            {
                printf("Login failed. Please try again.\n");
            }
            break;
        }
        case 2:
        {
            // Registration logic
            printf("\n--- Registration Menu ---\n");
            printf("1. Register as Member\n");
            printf("2. Register as Visitor\n");
            printf("3. Back to Main Menu\n");
            int reg_choice;
            printf("Enter your choice: ");
            scanf("%d", &reg_choice);

            switch (reg_choice)
            {
            case 1:
                register_member();
                break;
            case 2:
                register_visitor();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Returning to Main Menu...\n");
                break;
            }
            break;
        }
        case 3:
            printf("Exiting the program. Goodbye!\n");
            log_action("System Exited\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}

// Function to display the menu based on user role
void display_role_menu(const char *role)
{
    if (strcmp(role, "librarian") == 0)
    {
        librarian_menu();
    }
    else if (strcmp(role, "members") == 0)
    {
        member_menu();
    }
    else if (strcmp(role, "visitors") == 0)
    {
        visitor_menu();
    }
    else
    {
        printf("Unknown role. Returning to Main Menu.\n");
    }
}
