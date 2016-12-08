#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "environment_variable_setting.h"
#include "read_and_parse.h"

#define PATH_MAX  4096

int main() { 

  //sets the shell status as 'running' at the beginning
  shell.status = 1;

  //first calls the function to read from profile
  read_file_and_set_env_var();

  //error messages if failed to configure environment variables from profile
  if (shell.PATH == NULL) {
    fprintf(stderr, "error: error assigning PATH\n");
    return(-1);
  } else if (shell.HOME == NULL) {
    fprintf(stderr, "error: error assigning HOME\n");
    return(-1);
  }
  
  //loop for the shell to run, until the shell status is set to 0 (not running)
  while(1) {
    if (shell.status == 0) {
      break;
    }

    //gets the current working directory
    char buff[PATH_MAX + 1];
    char *cwd = getcwd(buff, PATH_MAX + 2);
    
    //starts reading from shell
    read_from_shell(cwd);
  }

  free(shell.PATH);
  free(shell.HOME);

  return 0;
}
