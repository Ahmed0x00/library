#include "utility.h"

// List files and directories using 'ls'
void list_files(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "ls -l %s", path);
    system(command);
}

// Create a directory using 'mkdir'
bool create_directory(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p %s", path);
    return system(command) == 0;
}

// Delete a directory using 'rm -r'
bool delete_directory(const char *path) {
    char command[256];
    snprintf(command, sizeof(command), "rm -rf %s", path);
    return system(command) == 0;
}

// Compress a file or directory and save it in 'admin/archive'
bool compress_directory(const char *path) {
    char command[512]; // Increased buffer size for longer paths
    snprintf(command, sizeof(command), "tar -czf admin/archive/%s.tar.gz %s", path, path);
    return system(command) == 0;
} 
