//creates a fork and calls exec 
int fork_and_execute();

//execute overwrite for protecting streams
int execute(char* path);

int check_for_redirects(char* param);

int find_in_path(char* executable);

int file_exists(char* path);
