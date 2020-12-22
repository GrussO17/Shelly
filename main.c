#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"


int main(){
    printf("this is a main");
    fork_to_execute();
    return 0;
}

int fork_to_execute(){
    int pid;
    if ((pid = fork()) == 0) {
        printf("Hello from Child!\n");
        
        execute("/bin/ls");

        exit(0); 
    
    }
    else {
        printf("Hello from Parent! I will be waiting now....\n"); 
        int wstatus = 0;
        wait(&wstatus);
        printf("wait has returned");
    }
    return 0;
}


int execute(char* path) {
    
    //call exec
    execl(path, "ls");
    return 0;
}
