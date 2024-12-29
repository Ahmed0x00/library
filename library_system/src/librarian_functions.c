#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "librarian_functions.h"
#include "common_operations.h"
#include "utility.h"

void librarian_menu() {
    int choice;
    char path[256], type[50], query[256], book_name[50], book_details[256], policies[256];

    while (1) {
        printf("\nLibrarian Menu:\n");
        printf("1. List files/dirs in /librarian\n");
        printf("2. Change permissions\n");
        printf("3. Create file/dir\n");
        printf("4. Delete file/dir\n");
        printf("5. Create symbolic link\n");
        printf("6. Copy file/dir\n");
        printf("7. Create alias\n");
        printf("8. Move to archive\n");
        printf("9. Search for book or member record\n");
        printf("10. Add book\n");
        printf("11. Remove book\n");
        printf("12. Check books catalog\n");
        printf("13. Update library policies\n");
        printf("14. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_files("librarian");
                break;
            case 2:
                update_permissions();
                break;
            case 3:
                create_file_or_directory();
                break;
            case 4:
                delete_file_or_directory();
                break;
            case 5:
                create_symbolic_link();
                break;
            case 6:
                copy_file_or_directory();
                break;
            case 7:
                create_alias();
                break;
            case 8:
                move_files_to_archive();
                break;
            case 9:
                printf("Enter type (book/member): ");
                scanf("%s", type);
                printf("Enter search term: ");
                scanf("%s", query);
                search_record(type, query);
                break;
            case 10:
                add_book(book_details);
                break;
            case 11:
                printf("Enter book name: ");
                scanf("%s", book_name);
                remove_book(book_name);
                break;
            case 12:
                view_file_content("visitors/book_catalog/catalog.txt");
                break;
            case 13:
                printf("Enter updated library policies: ");
                getchar(); // Clear newline
                fgets(policies, sizeof(policies), stdin);
                update_library_policies(policies);
                break;
            case 14:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void move_files_to_archive() {
    char source[256];
    const char *destination = "librarian/archive";

    printf("Enter the source path: ");
    scanf("%s", source);

    if (move_file(source, destination)) {
        printf("successfully moved to archive.\n");
    } else {
        perror("Error moving files to archive");
    }
}

// Function to search for books
void search_books(const char *book_name) {
    char path[512];
    FILE *file;

    // Construct the file path
    snprintf(path, sizeof(path), "librarian/books_inventory/%s.txt", book_name);
    // Debugging: Print the constructed path
    printf("Searching for book: %s\n", path);

    // Open the file
    file = fopen(path, "r");
    if (file) {
        printf("Book found. Details are displayed below:\n");
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Book not found in the inventory.\n");
    }
}

// Function to search for members
void search_members(const char *member_name) {
    char path[512];
    FILE *file;

    // Construct the file path
    snprintf(path, sizeof(path), "librarian/members_data/%s.txt", member_name);

    // Debugging: Print the constructed path
    printf("Searching for member: %s\n", path);

    // Open the file
    file = fopen(path, "r");
    if (file) {
        printf("Member found. Details are displayed below:\n");
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Member not found.\n");
    }
}

void search_record(const char *type, const char *query) {
    if (strcmp(type, "book") == 0) {
        search_books(query);
    } else if (strcmp(type, "member") == 0) {
        search_members(query);
    } else {
        printf("Invalid type. Use 'book' or 'member'.\n");
    }
}

void add_book(const char *book_details) {
    char title[50], author[50], content[256], path_inventory[256], path_books[256];

    // Prompt the user for the book title
    printf("Enter book title: ");
    scanf(" %[^\n]", title); // Reads input until newline

    // Prompt the user for the book author
    printf("Enter book author: ");
    scanf(" %[^\n]", author); // Reads input until newline

    // Prompt the user for the book content
    printf("Enter book content: ");
    scanf(" %[^\n]", content); // Reads input until newline

    snprintf(path_inventory, sizeof(path_inventory), "librarian/books_inventory/%s.txt", title);
    snprintf(path_books, sizeof(path_books), "librarian/books/%s.txt", title);

    if (create_file(path_inventory) && create_file(path_books)) {
        FILE *inventory_file = fopen(path_inventory, "w");
        FILE *book_file = fopen(path_books, "w");

        if (inventory_file && book_file) {
            fprintf(inventory_file, "title: %s\nauthor: %s\nnumber of borrowers: 0\ncontent: %s\n", title, author, content);
            fprintf(book_file, "title: %s\nauthor: %s\ncontent: %s\n", title, author, content);
            fclose(inventory_file);
            fclose(book_file);
            printf("\nBook added successfully. \n");
            log_action("Book added successfully.");
        } else {
            printf("Failed to open files for writing.\n");
            log_action("Failed to open files for writing.");
            if (inventory_file) fclose(inventory_file);
            if (book_file) fclose(book_file);
        }
    } else {
        printf("Failed to create book files.\n");
        log_action("Failed to create book files.");
    }
}

void remove_book(char *book_name) {
    char path_inventory[256], path_books[256];

    snprintf(path_inventory, sizeof(path_inventory), "librarian/books_inventory/%s.txt", book_name);
    snprintf(path_books, sizeof(path_books), "librarian/books/%s.txt", book_name);

    if (delete_file(path_inventory) && delete_file(path_books)) {
        printf("Book '%s' removed successfully.\n", book_name);
    } else {
        perror("Error deleting book files");
    }
}  


void update_library_policies(const char *policies) {
    FILE *policy_file = fopen("librarian/policy.txt", "w");
    if (policy_file) {
        fprintf(policy_file, "%s\n", policies);
        fclose(policy_file);
        printf("Library policies updated successfully.\n");
    } else {
        perror("Error updating library policies");
    }
}

void create_symbolic_link() {
    char target[256], link_path[256];
    printf("Enter target file/directory: ");
    scanf("%s", target);
    printf("Enter symbolic link path: ");
    scanf("%s", link_path);

    char command[512];
    snprintf(command, sizeof(command), "ln -s %s %s", target, link_path);

    if (system(command) == 0) {
        printf("Symbolic link created successfully: %s -> %s\n", link_path, target);
        log_action("Created a symbolic link.");
    } else {
        printf("Failed to create symbolic link.\n");
        log_action("Failed to create a symbolic link.");
    }
}

void update_permissions() {
    char path[256];
    mode_t mode;

    // Get the file/directory path and permissions from the user
    printf("Enter file/directory path: ");
    scanf("%s", path);
    printf("Enter new permissions in octal (e.g., 0755): ");
    scanf("%o", &mode);

    // Attempt to update permissions using chmod
    if (chmod(path, mode) == 0) {
        printf("Permissions updated successfully for %s.\n", path);
        log_action("Updated permissions successfully.");
    } else {
        perror("Error changing permissions"); // Print detailed error
        printf("Failed to update permissions for %s.\n", path);
        log_action("Failed to update permissions.");
    }
}