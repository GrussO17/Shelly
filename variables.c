#include <stdlib.h>
#include <string.h>

#include "string.h"
#include "sys/errno.h"
#include "variables.h"



int add_variable(char* command){
    var* variable = malloc(sizeof(var));
    variable->name = strtok(command, "=");
    char* value = strtok(NULL, "=");
    int temp;
    if ((temp = strtol(value, (char **)NULL, 10)) != 0 && (errno != EINVAL)) {
        //it is an int
        variable->value.integer_value = temp;
        variable->type = Integer;
        printf("stored an int \n");
    } else {
        variable->value.str_value = value;
        variable->type = Str;
        printf("stored an str \n");
    }
    return 1;
}

int display_all_vars(){
    //special command to list vars
    

}

