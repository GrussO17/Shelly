#include "string.h"
#include "sys/errno.h"
#include "variables.h"



int add_variable(char* command){
    var* variable = malloc(sizeof(var));
    variable->name = strtok(command, "=");
    char* value = strtok(NULL, "=");
    int temp;
    if (temp = strtol(value, (char **)NULL, 10) != 0 && errno != EINVAL) {
        //it is an int
        variable->integer_value = temp;
        variable->type = integer;
    } else {
        variable->str_value = value;
        variable->type = str;
    }
    return 1;
}



