// Define utility functions in here. These are functions used by myshell.c

/*
OS Lab 2 

Harasees Singh Gill, Siddharth Tripathi, Peter Levine
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"


void pauseMyShell()
{
	//While enter has not been pressed, sleep
	while (true)	{
		printf("Paused, press Enter to continue");
		sleep(10);
		if (getchar = "\n")	{
			break;
		}
	}
}

void help()
{
	//print commands available to user
	printf("Welcome to the help manual, here are the following commands: \n");
	printf("cd <directory> will change the current working directory \n");
	printf("clr will clear the screen \n");
	printf("environ will list all environment strings \n");
	printf("echo <comment> will display <comment> on the screen \n");
	printf("help will display help manual \n");
	printf("pause will pause terminal, press 'Enter' to continue \n");
	printf("quit will exit the shell \n");
}

//List all environments on the user PATH
void listEnvironment()
{	
	printf("PATH: %s\n", getenc("PATH"));
}

void clear()
{
	//print 50 blan lines to clear screen
	for (x = 1; x <= 50; x++)	{
		printf("\n");
	}
}
