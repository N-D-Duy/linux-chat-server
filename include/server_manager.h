#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <pthread.h>
#include "user.h"

#define MAX_USERS 1000

typedef struct {
    User *users[MAX_USERS];
    int user_count;
    char *ips[MAX_USERS];
    int ip_count;
    pthread_rwlock_t lock_user;
    pthread_rwlock_t lock_session;
} ServerManager;

void server_manager_get_users(User *buffer[], int *count);
int server_manager_get_number_online();
int server_manager_frequency(const char *ip);
User *server_manager_find_user_by_id(int id);
User *server_manager_find_user_by_username(const char *username);
void server_manager_add_user(User *user);
void server_manager_remove_user(User *user);
void server_manager_add_ip(const char *ip);
void server_manager_remove_ip(const char *ip);

void init_server_manager();
void destroy_server_manager();

#endif






