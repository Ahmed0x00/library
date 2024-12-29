#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <crypt.h>

// Function declarations for authentication
int login(char *logged_in_user);
int register_user(const char *role, char *username);
int register_visitor();
int register_member();
void update_logged_in_user_and_role(const char *username, const char *role);
int get_logged_in_user_and_role(char *username, char *role);

#endif // AUTHENTICATION_H
