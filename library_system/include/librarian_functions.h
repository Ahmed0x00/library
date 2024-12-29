#ifndef LIBRARIAN_FUNCTIONS_H
#define LIBRARIAN_FUNCTIONS_H

#include <utility.h>
#include <common_operations.h>

// Function prototypes
void librarian_menu();
void update_permissions();
void create_symbolic_link();
void search_record(const char *type, const char *query);
void move_files_to_archive();
void add_book(const char *book_details);
void remove_book(char *book_name);
void update_library_policies(const char *policies);
void update_permissions();
void create_symbolic_link();

#endif // LIBRARIAN_FUNCTIONS_H