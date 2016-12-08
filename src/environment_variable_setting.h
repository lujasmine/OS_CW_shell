#define MAX_LENGTH	4096

//struct will store the environment variables, PATH and MAX
/* status is either 1 or 0, depending on state of the shell
	- 1 means the shell is running
	- 0 means the shell is no longer running
*/
struct {
	char *PATH;
	char *HOME;
  int status;
} shell;

void read_file_and_set_env_var();
void set_environment_variable(char *env_var, int reassign);
void remove_new_line(char *str);
