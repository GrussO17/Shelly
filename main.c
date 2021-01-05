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
        query_input();
    }
    return 0;
}

