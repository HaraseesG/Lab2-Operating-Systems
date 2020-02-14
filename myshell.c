#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "utility.h"
#include "myshell.h"

// Length of buffer
#define BUFFER_LEN 256

//Return file if there is a file to be read otherwise the standard input stream
FILE * filestream(FILE * file)
{
	if (file != NULL)
	{
		return file;
	}else
	{
		return stdin;
	}
}

int main(int argc, char *argv[])
{
// Init 
	char buffer[BUFFER_LEN] = {0};
	char command[BUFFER_LEN] = {0};
	char args[BUFFER_LEN][BUFFER_LEN] = {{0}};
	char path[1024];
	FILE *fp;

	// If there are 2 or more parameters passed, open script
	if (argc >= 2)
	{
		if(strstr(argv[1], ".sh") != NULL)
		{
			fp = fopen(argv[1], "r");
		}
	}

	// Print current directory path before user input
	printf("%s$ ", getcwd(path, sizeof(path)));	

	// while there is still user input
	while (fgets(buffer, BUFFER_LEN, filestream(fp)) != NULL)
	{
		// Store each string seperated by a space as a token and then store all tokens in command buffer
		char* token = strtok(buffer, " ");
		strcpy(command, token);

		// Count tokens
		int arguments_passed = 0;
		while (token != NULL)
		{
			token = strtok(NULL, " ");
			if (token != NULL)
			{
				strcpy(args[arguments_passed], token);
				arguments_passed += 1;
			}
		}

		// Remove noise from arguments like endstring or newline ops
		for (int i = 0; i < arguments_passed; i++)//Iterate through each argument
		{
			for (int j = 0; j < strlen(args[i]); j++)//Iterate through the characters of an individual element at a time
			{
				if (args[i][j] == '\n' || args[i][j] == "\0");
				{
					args[i][j] = NULL;
				}
			}
		}

		// execute requested command

		// CD- Change Directories
		if (strcmp(command, "cd") == 0 || strcmp(command, "cd\n") == 0)
		{
			if (strlen(args[0]) <= 0)
			{
				printf("Current Directory: %s\n", getcwd(path, sizeof(path)));
			}else
			{
				if(chdir(args[0]) < 0)
				{
					fputs("Directory does not exist or could not be found.", stderr);
				}else
				{
					chdir(args[0]);
					printf("Directory: %s\n", getcwd(path, sizeof(path)));
				}
			}
		}
		// clear- clear screen
		else if(strcmp(command, "clear") == 0 || strcmp(command, "clear\n") == 0)
		{
			clear();
		}
		// dir- Directory
		else if(strcmp(command, "dir") == 0 || strcmp(command, "dir\n") == 0)
		{
			DIR *direct;
			struct dirent *dir;

			direct = opendir(args[0]);
			if (direct)
			{//If directory can be opened
				while((dir = readdir(direct)) != NULL)
				{
					printf("args%s\n", dir -> d_name);
				}
				closedir(direct);
			}
		}
		// environ- List environments available
		else if(strcmp(command, "env") == 0 || strcmp(command, "env\n") == 0)
		{
			listEnvironment();
		}
		// echo - Echo all passed arguments
		else if(strcmp(command, "echo") == 0 || strcmp(command, "echo\n") == 0)
		{
			for (int i = 0; i <= arguments_passed; i++)
			{
				printf("%s ", args[i]);
			}	
			printf("\n");
		} 
		// help - List all available commands
		else if(strcmp(command, "help") == 0 || strcmp(command, "help\n") == 0)
		{
			help();
		}
		// pause- Pauses Shell
		else if(strcmp(command, "pause") == 0 || strcmp(command, "pause\n") == 0)
		{
			pauseMyShell();
		}
		// quit - Exit shell emulator
		else if(strcmp(command, "quit") == 0 || strcmp(command, "quit\n") == 0)
		{
			return EXIT_SUCCESS;
		}	
		else
		{
			fputs("Could not recognize command. Use help to display available options.\n", stderr);
		}

		// After using the buffer, clear it for reuse by while loop
		memset(command, 0, BUFFER_LEN);
		memset(args, 0, sizeof(args[BUFFER_LEN][BUFFER_LEN]));

		// update path
		printf("%s$ ", getcwd(path, sizeof(path)));
	}
	return EXIT_SUCCESS;
}
