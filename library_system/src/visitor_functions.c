#include <stdio.h>
#include "common_operations.h"
#include "visitor_functions.h"

// Visitor menu function
void visitor_menu() {
    int choice;

    while (1) {
        printf("\nVisitor Menu:\n");
        printf("1. List files in /visitors\n");
        printf("2. Search for book titles\n");
        printf("3. Browse available books\n");
        printf("4. Check book catalog\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_files("visitors");
                break;
            case 2:
                search_books_titles();
                break;
            case 3:
                browse_books();
                break;
            case 4:
                view_file_content("visitors/book_catalog/catalog.txt");
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to search for book titles
void search_books_titles() {
    char search_term[256];
    printf("Enter search term: ");
    scanf("%255s", search_term);

    // Use Linux command to search for files in the directory
    char command[512];
    snprintf(command, sizeof(command),
             "ls librarian/books | grep -i '%s'", search_term);

    printf("Searching for books containing '%s':\n", search_term);
    int result = system(command);

    // Check if grep found anything
    if (result != 0) {
        printf("Book not found.\n");
    }
}

// Function to browse books
void browse_books() {
    char book_name[256];
    printf("Enter book name: ");
    scanf("%255s", book_name);

    // Use Linux command to check if the book exists and display its content
    char command[512];
    snprintf(command, sizeof(command),
             "cat librarian/books/%s.txt || echo 'Book not found.'",
             book_name, book_name);

    printf("Displaying content of '%s':\n", book_name);
    system(command);
}

