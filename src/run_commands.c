#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "environment_variable_setting.h"

void run_command(char **arguments) {

  pid_t pid;
  int status;

  pid = fork();

  if (pid >= 0) {
    if (pid == 0) {
      //child process
      char *path = strtok(shell.PATH, ":"); //breaks up the PATH with delimiter ':' so that it will check each path, one at a time
      while (path != NULL) {
        char *command = malloc(strlen(path) + 1);
        command = strdup(path);
        command = strcat(strcat(command, "/"), arguments[0]); //will end up with the full path that will run the command
        //runs execv to see whether the path was valid or not
        if (execv(command, arguments) != -1) {
          exit(0); //the path was valid and the command was called successfully
        }
        //breaks up the PATH variable and continues with the next path if the command run successfully 
        path = strtok(NULL, ":");
      }

      //command is not valid and was not found in PATH - error message
      if (path == NULL) {
        fprintf(stderr, "error: command not found\n");
        exit(0);
      }
    } else {
      //parent waits for child process to finish
      waitpid(pid, &status, 0);
    }
  } else {
    perror("fork");
    exit(0);
  }
}

//runs the cd command
void run_cd(char **arguments) {
  if (arguments[1] == NULL) { //will change into HOME directory if no arguments after the 'cd'
    if (chdir(shell.HOME) != 0) {
      fprintf(stderr, "error: No such file or directory\n");
    }
  } else {
    if (chdir(arguments[1]) != 0) { //will change into the directory that was called after 'cd'
      fprintf(stderr, "error: No such file or directory\n");
    }
  }
}
