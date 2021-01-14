#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <unistd.h>

#include "input.h"
#include "variables.h"
#include "fork_exec.h"

int query_input() {

    char wd[100];
    getcwd(wd, 80);
    char* dir = get_dir_from_wd(wd);
    printf("Prompt(%s): ", dir);
    char* str = malloc(MAX_LINE);
    fgets(str, MAX_LINE, stdin);
    if (strlen(str) == 0 || seperate_expressions(str) == -1) {
        return -1;
    }
    free(str);
    return 1;
}

int evaluate_expression(char* expr) {
    expr = trim_whitespace(expr);  
    int keyword_check = 0;
    if ((keyword_check = check_keywords(expr)) == 1) {//check first word for keyword 
        return 1; // expression done   
    } else if (keyword_check == -1) {
        //quit
        return -1;
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
    char* ret = NULL;
    if ((ret = strstr(expr, "print")) != NULL && ret == expr) {
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
    } else if ((ret = strstr(expr, "quit")) != NULL && ret == expr) {
        printf("The keyword print check result %s\n", ret);
        return -1;
    } else if ((ret = strstr(expr, "cd")) != NULL && ret == expr) {
        strtok(expr, " ");
        change_dir(strtok(NULL, " "));
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
        if (seperate_expressions(command) == -1 ||  
            seperate_expressions(split_loc + 2) == -1){
            return -1;
        }
    } else {
        if (evaluate_expression(command) == -1) {
            return -1;
        }
    }
    return 1;
}


int change_dir(char* loc) {
    char* param = trim_whitespace(loc);
    chdir(param);
    return 1;
}


char* get_dir_from_wd(char* wd) {
    int count = strlen(wd) - 1;
    while(wd[count] != '/') {
        count --;
    }
    return wd + count + 1;
}
