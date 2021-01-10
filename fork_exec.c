#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

#include "fork_exec.h"
#include "input.h"
#include "variables.h"

int fork_and_execute(char* path){
    int pid;
    if ((pid = fork()) == 0) {
        //child
        if (!check_for_redirects(path)) {
            if (!find_in_path(path)) {
                execute(path);
            }
        }
        exit(0); 
    }
    else {
        int wstatus = 0;
        wait(&wstatus);
    }
    return 0;
}

int check_for_redirects(char* param) {
    char* special_char;
    if ((special_char = strstr(param, ">>")) != NULL) {
        //handle a redirect
        char* file_path = trim_whitespace(special_char + 2);
        *special_char = '\0';
        char* executable = trim_whitespace(param);
        freopen(file_path, "a", stdout);
        execute(executable);
        return 1;
    } else if ((special_char = strstr(param, ">")) != NULL) {
        //handle a redirect
        char* file_path = trim_whitespace(special_char + 2);
        *special_char = '\0';
        char* executable = trim_whitespace(param);
        freopen(file_path, "w", stdout);
        execute(executable);
        return 1;
    }
    return 0;
}

int execute(char* path) {
    //call exec
    printf("Fork_and_execute: '%s' \n", path);
    int result = execl(path, path);
    printf("exec result %d, error %s\n", result, strerror(errno));
    return 0;
}

int find_in_path(char* executable) {
    //check for variable named PATH
    var* path;
    char* temp;
    if ((path = find_var("PATH")) != NULL) {
        //split path on :
        char* token = strtok(path->value.str_value, ":");
        do {
            char* full_path = malloc(strlen(token) + 
                strlen(executable) + 1);
            strncpy(full_path, token, strlen(token));
            strcat(full_path, executable);
            char* space = strstr(full_path, " ");
            if (space != NULL) {
                *space = '\0';
                if (file_exists(full_path)) {
                    execute(full_path);
                    return 1;
                }
            } else {
                if (file_exists(full_path)) {
                    execute(full_path);
                    return 1;
                }
            }
            free(full_path);
        } while ((token = strtok(NULL, ":")) != NULL);
    }
    return 0;
}

int file_exists(char* path) {
    FILE *file;
    if ((file = fopen(path, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

