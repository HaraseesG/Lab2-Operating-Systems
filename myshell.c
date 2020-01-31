#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dirent.h>
//#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"


int main(int argc, char const *argv[])
{
	//print current working directory
	char cwd[100];
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	}

	//get initial command/string
	char str[100]; 
	fgets(str);
	char command[10];
	char arg[100];

	//loop for command line shell
	do {
		//get command (first token from string)
		char *token = strtok(str, " ");
		strcpy(command, token);

		//get argument (second token)
		while(token != NULL) {
			token = strtok(NULL, " ");
			if (token != NULL) {
				strcpy(arg, token);
			}
		}

		//'cd' command functionality
		//comparing the command token taken with 'cd'
		if (strcmp(command, "cd") == 0) {
			
		
		}










	}while(token != NULL);









	return 0;
}