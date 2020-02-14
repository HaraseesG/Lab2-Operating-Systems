#include <stdio.h>
#include <stdlib.h>



int board[9][9];
int rows[9];
int columns[9];
int squares[9];

void *rowCheck(int num) {
	int count = 0;
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			//count how many times current num appears in this row
			if (num == board[9][9]) {
				count++;
			}
		}

		//check for correct number count, 1 is valid board 0 is invalid board
		if (count == 1) {
			rows[r] = 1;
		} else {
			rows[r] = 0;
		}

	}

}


void *columnCheck(int num) {




}

void *squareCheck(int num) {






}

int main(int argc, char const *argv[])
{
	//read in sudoku board state
	//puzzle.txt





	//creation of 3 threads: column, row, square






	return 0;
}