CC=gcc
CFLAGS=-g -Wall

all:	program

program:shell.o environment_variable_setting.o run_commands.o read_and_parse.o
	$(CC) -o shell shell.o environment_variable_setting.o run_commands.o read_and_parse.o $(CFLAGS) 

clean:
	rm -f *.o
