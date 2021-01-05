#define MAX_LINE 200

union Values {
    char* str_value;
    int integer_value;
};

struct var{
    char* name;
    enum Types {
        Integer,
        Str
    } type;
    union Values value;
} typedef var;

int vars_len;
var** vars;

int add_variable(char* arg); 
int display_all_vars();
int init_variables();
