#define MAX_LINE 200


struct var{
    char* name;
    enum types {
        Integer,
        Str
    } type;
    union values {
        char* str_value;
        int integer_value;
    }value;
} typedef var;

var* vars;

int add_variable(char* arg); 
int display_all_vars();
