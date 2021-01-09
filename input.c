#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "input.h"
#include "variables.h"
#include "fork_exec.h"

int query_input() {

    printf("Prompt: ");
    char* str = malloc(MAX_LINE);
    fgets(str, MAX_LINE, stdin);
    seperate_expressions(str);
    free(str);
    return 1;
}

int evaluate_expression(char* expr) {
    expr = trim_whitespace(expr);    
    if (check_keywords(expr)) {//check first word for keyword 
        return 1; // expression done   
    } 
    //if no = sign, assume execute
    if (strchr(expr, '=')) {
        // do variable things
        add_variable(expr);
        //display_all_vars();    
    } else {
        //assume it is a program
        fork_and_execute(expr);
    }

    return 1;
}

int check_keywords(char* expr) {
    char* ret;
    if((ret = strstr(expr, "print")) != NULL && ret == expr) {
        printf("The keyword print check result %s\n", ret);
        if (strlen(expr) > 5) {
            // check for variable name after.
            char* name = trim_whitespace(expr + 5);
            var* to_print = find_var(name);
            print_var(to_print); 
        } else {
            display_all_vars();
        }
        return 1;
    }
    return 0;
}

//returns pointer to start within original string.
char* trim_whitespace(char* param) {

    int start = 0, end = strlen(param) - 1;
    while( iswspace(param[start]) ) {
        start++;
    }
    //tailling trim
    while ( iswspace(param[end]) ) {
        end--;
    }
    param[end+1] = '\0';
    return param+start;
}

//calls the perspective expression functions for each expression evalutation.

//also return is the number of expressions.
int seperate_expressions(char* command) {

    //check for &&, if present then split on them and call seperate expressions on each.
    char* split_loc;
    if ((split_loc = strstr(command, "&&")) != NULL) {
        *split_loc = '\0';
        seperate_expressions(command); //first expression
        seperate_expressions(split_loc + 2);
    } else {
        evaluate_expression(command);
    }
    return 1;
}






