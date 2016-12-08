COMP 3005 | Operating Systems Coursework 1: Unix Command Shell

by Jasmine Lu

TO MAKE: make
TO CLEAN FILES: make clean
TO RUN SHELL: ./shell

FILE DESCRIPTION: shell.c shell.h
This contains the main function, which first calls the function to read from profile. It gets the current working directory and also consists of the loop that keeps the shell running until the shell 'status' is set to 0 meaning that the shell is no longer running. The shell status is set to 0 only when the 'exit' command is called in read_and_parse.c

FILE DESCRIPTION: environment_variable_setting.c environment_variable_setting.h
This contains the functions (read_file_and_set_env_var) that reads from profile and actually configures the environment variables (set_environment_variable) if called correctly in profile. The struct that contains the environment variables and the status of the shell is initialised here. 

FILE DESCRIPTION: read_and_parse.c read_and_parse.h
This file contains the functions to read input from the command line (read_from_shell) and also parses the command into the separate arguments (parse_command) so that the command called is stored at index 0 and any arguments stored from index 1 onwards. In 'read_from_shell', if $HOME or $PATH is called on the command line, the relevant functions will be called, whether to display the HOME/PATH or to configure them (for example if $HOME=/Users/jasmine was input by the user). 'parse_command' also checks to see whether 'exit' is called (where the shell status is set to 0, and the shell no longer runs) or 'cd', where the function 'run_cd' is called. Otherwise, 'run_command' is called, where the command will be searched in the PATH and ran if found.

FILE DESCRIPTION: run_command.c run_commands.h
This file contains the function that forks the process and the child process is where the command is ran. Each separate path in PATH will be searched in order until the command called is found, then the command is run, or if it's not found in any of the paths (i.e. /usr/bin, /bin or /usr/local/bin) then, an error message will be displayed stating that the command was not found. The run_cd function is also in this file, where the directory will be changed depending on the input from the command line.

FILE DESCRIPTION: profile
This file contains the HOME and PATH assignments as in the example in the spec pdf

NOTES:
Tested on frontal.cs.ucl.ac.uk, the ^? character is used as backspace, so the error message stating that the command not found will appear.
