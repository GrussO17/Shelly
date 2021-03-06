#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"
#include "sys/errno.h"
#include "variables.h"
#include "input.h"

//TODO add hard limit to variable names and so forth

int init_variables(){
    vars_len = 0;
    return 1;
}

int add_variable(char* command) {
    var* variable = malloc(sizeof(var));
    char* temp_str = strtok(command, "=");
    trim_whitespace(temp_str);
    variable->name = malloc(strlen(temp_str));
    int len = strlen(temp_str);
    strncpy(variable->name, temp_str, len);
    char* value = strtok(NULL, "\0");
    int temp;
    if ((temp = strtol(value, (char **)NULL, 10)) != 0 && (errno != EINVAL)) {
        variable->value.integer_value = temp;
        variable->type = Integer;
    } else {
        variable->value.str_value = malloc(strlen(value));
        strncpy(variable->value.str_value, value, strlen(value)); 
        variable->type = Str;
    }
    vars = realloc(vars, (vars_len + 1) * sizeof(var)); 
    vars[vars_len++] = variable;
    return 1;
}

int cleanup_variables() {
    for (int i = 0; i < vars_len; i++) {
        free(vars[i]->name);
        if (vars[i]->type==Str) {
            free(vars[i]->value.str_value);
        }
        free(vars + i);
    }
    return 1;
}

int display_all_vars() {
    //special command to list vars
    printf("---Variables---\n");
    for (int i = 0; i < vars_len; i++) {
        print_var(vars[i]);
    }
    return 1;
}

int print_var(var* variable){     
    if (variable->type == Str) {
        printf("Name '%s': '%s'\n", variable->name, variable->value.str_value);
    } else if (variable->type == Integer) {
        printf("Name '%s': '%d'\n", variable->name, variable->value.integer_value);
    } else {
        printf("Error printing variable");
        return 0;
    }
    return 1;
}
var* find_var(char* name) {
    for (int i = 0; i < vars_len; i++) {
        if (strcmp(name, vars[i]->name) == 0) {
           return vars[i]; 
        }
    }
    return NULL;
}
