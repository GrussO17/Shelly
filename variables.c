#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "string.h"
#include "sys/errno.h"
#include "variables.h"

int init_variables(){
    vars_len = 0;
    return 1;
}

int add_variable(char* command) {
    var* variable = malloc(sizeof(var));
    char* temp_str = strsep(&command, "=");
    variable->name = malloc(strlen(temp_str));
    strncpy(variable->name, temp_str, strlen(temp_str));

    char* value = command;
    int temp;
    if ((temp = strtol(value, (char **)NULL, 10)) != 0 && (errno != EINVAL)) {
        variable->value.integer_value = temp;
        variable->type = Integer;
        printf("stored an int \n");
    } else {
        variable->value.str_value = value;
        variable->type = Str;
        printf("stored an str \n");
    }
    vars = realloc(vars, (vars_len + 1) * sizeof(var)); 
    vars[vars_len++] = variable;
    return 1;
}

int cleanup_variables() {
    for (int i = 0; i < vars_len; i++) {
        free(vars[i]->name);
        free(vars + i);
    }
    return 1;
}

int display_all_vars() {
    //special command to list vars
    printf("---Variables---\n");
    for (int i = 0; i < vars_len; i++) {
        if (vars[i]->type == Str) {
            printf("Name '%s': '%s'\n", vars[i]->name, vars[i]->value.str_value);
        } else if (vars[i]->type == Integer) {
            printf("Name '%s': '%d'\n", vars[i]->name, vars[i]->value.integer_value);
        }
    }
    return 1;
}

