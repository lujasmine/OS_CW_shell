#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "environment_variable_setting.h"

//initialises the struct to store the environment variables (PATH and HOME) and also a 'status' of the shell
struct shell;

//reads from profile and calls the function to set the environment variables
void read_file_and_set_env_var() {
	FILE *fp;
	fp = fopen("profile", "r");
	char str[MAX_LENGTH];
	
  //throws an error if file does not exist
	if (fp == NULL) {
		perror("Error");
	} else {
    while(1) {
      //reads line from profile and breaks out of loop if file is empty
      if (fgets(str, MAX_LENGTH, fp) == NULL) {
        break;
      } else {
        //checks whether the line read from profile is valid or not
        if (strncmp( "PATH=", str, 5) == 0 || strncmp("HOME=", str, 5) == 0) {
          //calls the function to configure the environment variable (arguments explained below)
          set_environment_variable(str, 0);
        }
      }
    }
  }
  //close file when finished reading
	fclose(fp);
}

/* configures the relevant environment variable
    - env_var is the whole string of an environment variable configuration call (e.g. HOME=/Users/jasminelu)
    - reassign is either 1 - a reassignment (i.e. when a user calls $HOME=...)
      or 0 - first time assignment (i.e. reading from profile at the beginning)
*/
void set_environment_variable(char *env_var, int reassign) {
  char *env_variable;
  char *env_variable_value;
  char *search = "=";

  //breaking up the string env_var, with '=' as the delimiter
  env_variable = strtok(env_var, search);
  //breaks up the string further so that all the characters after the '=' are stored as the string, env_variable_value so that it can be assigned to the relevant environment variable later
  env_variable_value = strtok(NULL, search);

  //checks whether env_variable_value was assigned properly or not
  if (env_variable_value == NULL) {
    fprintf(stderr, "error: could not assign environment variable\n");
    return;
  }

  //checks whether it is PATH that is being configured
  if (strcmp("PATH", env_variable) == 0) {
    int pathLength = strlen(env_variable_value) + 1;
    if (reassign == 0) { //if it is the first time that PATH is being configured, then malloc, otherwise realloc
      shell.PATH = (char*) malloc(pathLength * sizeof(char));
    } else {
      shell.PATH = (char *) realloc(shell.PATH, pathLength * sizeof(char));
    }
    shell.PATH = strdup(env_variable_value);
    shell.PATH[pathLength-1] = '\0';
    remove_new_line(shell.PATH); //make sure there is no trailing newline character
  } else if (strcmp("HOME", env_variable) == 0) {   //checks whether it is HOME that is being configured
    int homeLength = strlen(env_variable_value) + 1;
    if(reassign == 0) { //if it is the first time that HOME is being configured, then malloc, otherwise realloc
      shell.HOME = (char*) malloc(homeLength * sizeof(char));
    } else {
      shell.HOME = (char *) realloc(shell.HOME, homeLength * sizeof(char));
    }
    shell.HOME = strdup(env_variable_value);
    shell.HOME[homeLength-1] = '\0';
    remove_new_line(shell.HOME); //make sure there is no trailing newline character
  }
}

//removes any trailing newline character from str
void remove_new_line(char *str) {
  if (str[strlen(str) - 1] == '\n') {
    str[strlen(str) - 1] = '\0';
  }
}
