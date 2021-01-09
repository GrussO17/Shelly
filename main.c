#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "main.h"
#include "input.h"
#include "variables.h"

int main(){
    //fork_and_execute();
    init_variables();
    while (1) {
        if (query_input() == -1) {
            break;
        }
    }
    return 0;
}

