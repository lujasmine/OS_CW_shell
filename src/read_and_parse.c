#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "environment_variable_setting.h"
#include "run_commands.h"
#include "read_and_parse.h"

//function to read any commands from user input - takes the current working directory as an argument
void read_from_shell(char *cwd){
  //part of spec to print the cwd followed by >
	printf("%s", cwd);
  printf(">");
  
  int max_length = 1; //temporary 'max length' of the input from the command line
  int current_size = 0; //int to track the size of the input from the command line
  
	char *command = malloc(max_length * sizeof(char *)); //initial malloc for the string that will store the input from the command line
  current_size = max_length; //updates the current size
  
  if (command != NULL) { //checks to see whether anything was typed
    int c = EOF;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF) { //while loop to read every character from the input
      command[i++] = (char) c;
      if(i == current_size) {
        //increases the size of the char array and realloc to account for this for every new character
        current_size = i + max_length;
        command = realloc(command, current_size * sizeof(char *));
      }
    }

    //checks whether the command called was to configure an environment variable or not
    if (strncmp( "$", &command[0], 1) == 0) {
      if (strcmp(command, "$HOME") == 0) { //checks to see whether the command called was just to display the HOME path
        printf("HOME: %s\n", shell.HOME);
      } else if (strcmp(command, "$PATH") == 0) { //checks to see whether the command called was just to display the PATH variable
        printf("PATH: %s\n", shell.PATH);
      } else {
        //if the call was to reassign an environment variable, then the set_enviroment_variable function is called
        set_environment_variable(command + 1, 1); 
      }
    } else {
      //otherwise, for all other command calls, the parse_command function is called, with the command string as an argument
      command[i] = '\0';
      parse_command(command);
    }
  }

  free(command);
  command = NULL;
}

//function to parse the command and separate the arguments for the function called
void parse_command(char *command){
  int max_size = 1; //temporary 'max size' for the 'token_array' that will store the arguments
  int current_size = 0;
  int index = 0;
  
	char **token_array = malloc(max_size * sizeof(char *)); //array to store all the separated arguments

	if (command[0] == '\0') {
		return;
	} else {
    char *token = strtok(command, TOKEN_DELIM); //breaks up the string when there is blank space
    while (token != NULL) {
      int max_length = strlen(token) + 1;
      token_array[index] = malloc(max_length * sizeof(char *));
      //duplicates the token into the token array
      token_array[index] = strdup(token);
      token_array[index++][max_length] = '\0';
      if (index >= current_size) {
        current_size = index + max_size;
        token_array = realloc(token_array, (current_size * sizeof(char *))); //allocating more memory for each argument added
      }
      token = strtok(NULL, TOKEN_DELIM);
    }
    token_array[index] = NULL;
  }

	int i;

  if (strcmp("exit", token_array[0]) == 0) { //checking whether the 'exit' command is called
    shell.status = 0; //sets the shell status to 0 which means the shell is no longer running
  } else if (strcmp("cd", token_array[0]) == 0) { //checking whether the 'cd' command is called
    run_cd(token_array);
  } else { //otherwise, calls the run_command function, where the 'token_array' is passed on as an argument - these are the ones that are found in PATH
    run_command(token_array); 
  }

	for(i = 0; i < current_size; i++) {
    free(token_array[i]);
    token_array[i] = NULL;
	}

  free(token_array);
  token_array = NULL;
}
