#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include "fork_exec.h"

int fork_and_execute(char* path){
    int pid;
    if ((pid = fork()) == 0) {
        execute(path);
        exit(0); 
    }
    else {
        int wstatus = 0;
        wait(&wstatus);
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

int file_exists(char* path){
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }
    return 1;
}
