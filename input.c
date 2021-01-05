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
    
    trim_whitespace(command);    
    printf("trimmed '%s'\n", command);
    //if no = sign, assume execute
    if (strchr(command, '=')) {
        // do variable things
        add_variable(command);
        display_all_vars();    
    } else {
        //assume it is a program
        fork_and_execute(command);
    }

    return 1;
}

//remove space from front and back by maninpulating given string
int trim_whitespace(char* param){

    int start = 0, end = strlen(param) - 1;
    while( iswspace(param[start]) ){
        start++;
    }
    //tailling trim
    while ( iswspace(param[end]) ){
        end--;
    }
    char* new_str = malloc(end - start + 2);
    memcpy(new_str, param + start, end-start + 1);
    new_str[end-start+1] = '\0';
    param = realloc(param, end - start + 2);
    memcpy(param, new_str, end-start + 2);
    free(new_str); 
    return 1;
}


