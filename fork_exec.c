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
                char* alloced = malloc(strlen(path) + 1);
                strncpy(alloced, path, strlen(path));
                execute(alloced);
                free(alloced);
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
        if (!find_in_path(executable)) {
            execute(executable);
        }
        return 1;
    } else if ((special_char = strstr(param, ">")) != NULL) {
        //handle a redirect
        char* file_path = trim_whitespace(special_char + 2);
        *special_char = '\0';
        char* executable = trim_whitespace(param);
        freopen(file_path, "w", stdout);
        if (!find_in_path(executable)) {
            execute(executable);
        }
        return 1;
    } else if ((special_char = strstr(param, "|")) != NULL) {
        char* temp_file = "/tmp/shellys";
        *special_char = '\0';
        char* first_exec = trim_whitespace(param);
        char* second_exec = trim_whitespace(special_char + 1);
        printf("First exec '%s', second exec '%s'\n", first_exec, second_exec);
        freopen(temp_file, "w", stdout);
        if (!find_in_path(first_exec)) {
            execute(first_exec);
        }
        freopen("/dev/stdout", "w", stdout);
        printf("is stdout printing fixed\n");
        freopen(temp_file, "r", stdin);
        if (!find_in_path(second_exec)) {
            execute(second_exec);
        }
        return 1;
    }
    return 0;
}

int execute(char* path) {
    //call exec
    printf("Fork_and_execute: '%s' \n", path);
    char* argv[80];
    int count = 0;
    char* temp;
    argv[0] = strtok(path, " ");
    while ((temp = strtok(NULL, " ")) != NULL) {
        argv[++count] = temp;
    }
    printf("----path %s----\n----argv[0] is: %s-----\n----len %d----\n", path, argv[0], count); 
    int result = execv(path, argv);
    printf("result %d, error %s\n", result, strerror(errno));
    return result;
}

int find_in_path(char* executable) {
    //check for variable named PATH
    var* path;
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
                    *space = ' ';
                    printf("executing %s\n", full_path);
                    execute(full_path);
                    return 1;
                }
            } else {
                if (file_exists(full_path)) {
                    printf("executing %s\n", full_path);
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

