// Define utility functions in here. These are functions used by myshell.c

/*
OS Lab 2 

Harasees Singh Gill, Siddharth Tripathi, *WRITE YOUR NAMES HERE*
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
}

void help()
{
	//print commands available to user
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
