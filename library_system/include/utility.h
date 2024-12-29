#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

void list_files(const char *path);
bool create_file(const char *path);
bool create_directory(const char *path);
bool delete_file(const char *path);
bool delete_directory(const char *path);
bool copy_file(const char *source, const char *destination);
bool move_file(const char *source, const char *destination);
bool compress_directory(const char *path);
void view_file_content(char *file_path);

#endif // UTILITY_H
