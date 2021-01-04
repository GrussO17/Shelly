#define MAX_LINE 200


struct var{
    char* name;
    enum types {
        integer,
        str
    } type;
    union values {
        char* str_value;
        int integer_value;
    }value;
} typedef var;

var* vars;

int add_variable(char* arg); 
