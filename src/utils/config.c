#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "log.h"

// Singleton instance
static Config* instance = NULL;

Config* config_get_instance() {
    if (instance == NULL) {
        instance = calloc(1, sizeof(Config));
    }
    return instance;
}

bool config_load() {
    FILE* config_file = fopen("config.properties", "r");
    if (config_file == NULL) {
        return false;
    }
    
    Config* config = config_get_instance();
    
    char line[256];
    char key[128];
    char value[128];
    
    while (fgets(line, sizeof(line), config_file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        
        // Parse key=value
        char* delimiter = strchr(line, '=');
        if (delimiter == NULL) continue;
        
        // Split key and value
        *delimiter = '\0';
        strncpy(key, line, sizeof(key));
        strncpy(value, delimiter + 1, sizeof(value));
        
        // Remove trailing newline from value
        char* newline = strchr(value, '\n');
        if (newline) *newline = '\0';
        
        // Trim key and value
        char* k = key;
        char* v = value;
        while (*k == ' ') k++;
        while (*v == ' ') v++;
        
        // Set config values based on key
        if (strcmp(k, "server.log.display") == 0) {
            config->show_log = (strcmp(v, "true") == 0);
        } else if (strcmp(k, "server.port") == 0) {
            config->port = atoi(v);
        } else if (strcmp(k, "game.login.limit") == 0) {
            config->ip_address_limit = atoi(v);
        } else if (strcmp(k, "db.host") == 0) {
            config->db_host = strdup(v);
        } else if (strcmp(k, "db.port") == 0) {
            config->db_port = atoi(v);
        } else if (strcmp(k, "db.user") == 0) {
            config->db_user = strdup(v);
        } else if (strcmp(k, "db.password") == 0) {
            config->db_password = strdup(v);
        } else if (strcmp(k, "db.dbname") == 0) {
            config->db_name = strdup(v);
        }
    }
    
    fclose(config_file);
    return true;
}

bool config_get_show_log() {
    return config_get_instance()->show_log;
}

int config_get_port() {
    return config_get_instance()->port;
}

int config_get_ip_address_limit() {
    return config_get_instance()->ip_address_limit;
}

const char* config_get_db_host() {
    return config_get_instance()->db_host;
}

int config_get_db_port() {
    return config_get_instance()->db_port;
}

const char* config_get_db_user() {
    return config_get_instance()->db_user;
}

const char* config_get_db_password() {
    return config_get_instance()->db_password;
}

const char* config_get_db_name() {
    return config_get_instance()->db_name;
}

void config_cleanup() {
    if (instance != NULL) {
        free(instance->db_host);
        free(instance->db_user);
        free(instance->db_password);
        free(instance->db_name);
        free(instance);
        instance = NULL;
    }
}