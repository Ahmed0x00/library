#ifndef COMMON_OPERATIONS_H
#define COMMON_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void list_files(const char *path);
void create_file_or_directory();
void delete_file_or_directory();
void copy_file_or_directory();
void log_action(const char *message);
void create_alias();
void display_role_menu(const char *role);

#endif // COMMON_OPERATIONS_H
