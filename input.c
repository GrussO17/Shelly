#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "input.h"
#include "variables.h"
#include "fork_exec.h"

int query_input(){

    printf("Prompt: ");
    char* str = malloc(MAX_LINE);
    fgets(str, MAX_LINE, stdin);
    
    switch_inputs(str);
    free(str);
    return 1;
}

int switch_inputs(char* command){

    //here is where i decide what is happening
    trim_whitespace(command);    

    printf("trimmed %s\n", command);

    //if no = sign, assume execute
    if (strstr(command, "=")) {
       // do variable things
       add_variable(command); 
    } else {
        //assume it is a program
        fork_and_execute(command);
    }

    return 1;
}

//remove space from front and back by maninpulating given string
int trim_whitespace(char* param){

    //leading trim
    char* temp = malloc(strlen(param));
    void* alloc = temp;// for freeing.
    strncpy(temp, param, strlen(param));
    while( iswspace(*temp) ){
        temp++;
    }
    //tailling trim
    int last = strlen(temp) - 1;
    while ( iswspace(temp[last]) ){
        last --;
    }
    last ++;
    bzero(param, MAX_LINE);
    strncpy(param, temp, last);
    printf("return: '%s'\n", param); 
    free(alloc);
    return 1;
}


