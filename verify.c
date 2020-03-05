#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int board[9][9];

void *rowCheck() {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			//check current number with other locations for duplicate or more of the same num
			for (int x = c+1; x < 9; x++) {
				if (board[r][c] == board[r][x]) {
					printf("Duplicate number found in rows. Exiting.\n");
					exit(0);
				}				
			}
		}
	}
	printf("Rows checked successfully.\n");
	return NULL;
}

void *columnCheck() {
	for (int c = 0; c < 9; c++) {
		for (int r = 0; r < 9; r++) {
			//check current number with other locations for duplicate or more of the same num
			for (int x = r+1; x < 9; x++) {
				if (board[r][c] == board[x][c]) {
					printf("Duplicate number found in columns. Exiting.\n");
					exit(0);
				}				
			}
		}
	}
	printf("Columns checked successfully.\n");
	return NULL;
}

void *squareCheck() {
	int square[9]; 
	int square2[9];
	int square3[9];
	int square4[9];
	int	square5[9];
	int square6[9];
	int square7[9];
	int square8[9];
	int square9[9];
	int count = 0;

	//store numbers from first square
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			square[count] = board[r][c];
			count++;
		}
	}
	//store numbers from second square
	for (int r = 0; r < 3; r++) {
		for (int c = 3; c < 6; c++) {
			square2[count] = board[r][c];
			count++;
		}
	}
	//store numbers from third square
	for (int r = 0; r < 3; r++) {
		for (int c = 6; c < 9; c++) {
			square3[count] = board[r][c];
			count++;
		}
	}
	//store numbers from fourth square
	for (int r = 3; r < 6; r++) {
		for (int c = 0; c < 3; c++) {
			square4[count] = board[r][c];
			count++;
		}
	}
	//store numbers from fifth square
	for (int r = 3; r < 6; r++) {
		for (int c = 3; c < 6; c++) {
			square5[count] = board[r][c];
			count++;
		}
	}
	//store numbers from sixth square
	for (int r = 3; r < 6; r++) {
		for (int c = 6; c < 9; c++) {
			square6[count] = board[r][c];
			count++;
		}
	}
	//store numbers from seventh square
	for (int r = 6; r < 9; r++) {
		for (int c = 0; c < 3; c++) {
			square7[count] = board[r][c];
			count++;
		}
	}
	//store numbers from eighth square
	for (int r = 6; r < 9; r++) {
		for (int c = 3; c < 6; c++) {
			square8[count] = board[r][c];
			count++;
		}
	}
	//store numbers from ninth square
	for (int r = 6; r < 9; r++) {
		for (int c = 6; c < 9; c++) {
			square9[count] = board[r][c];
			count++;
		}
	}

	//checking array of numbers in built square
	for (int i = 0; i < 8; i++) {
		for (int j = i+1; j < 9; j++) {
			if (square[i] == square[j] || square2[i] == square2[j] || square3[i] == square3[j]
				|| square4[i] == square4[j] || square5[i] == square5[j] || square6[i] == square6[j]
				|| square7[i] == square7[j] || square8[i] == square8[j] || square9[i] == square9[j]) {
				printf("Duplicate number found in square. Exiting.\n");
				exit(0);
			}
		}
	}
	printf("Squares checked successfully.\n");
	return NULL;
}

int main(int argc, char const *argv[])
{
	//read in sudoku board state from puzzle.txt
	FILE *fp;
	fp = fopen("puzzle.txt","r");
	char *token;
	char line[100];
	for (int i = 0; i < 9; i++)	{
		fgets(line, sizeof(line), fp);
		line[strlen(line) - 1] = '\0';
		token = strtok(line, " ");
		for (int j = 0; j < 9; j++)	{
			board[i][j] = atoi(token);
			token = strtok(NULL, " ");
		}
	}

	//creation of 3 threads: column, row, square
	pthread_t tid[3];
	pthread_attr_t attr[3];
	for (int i = 0; i < 3; i++)	{
		pthread_attr_init(&attr[i]);
	}
	pthread_create(&tid[0], &attr[0], rowCheck, NULL);
	pthread_create(&tid[1], &attr[1], columnCheck, NULL);
	pthread_create(&tid[2], &attr[2], squareCheck, NULL);

	for (int i = 0; i < 2; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}