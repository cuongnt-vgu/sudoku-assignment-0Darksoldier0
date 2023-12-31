#include "ShowPossible.h"

// Go to each cell in the sudoku board
// Check if that cell is solved
// If that cell is solved, skip the 'if statement' and continue the loop
// If that cell is unsolved, enter the 3rd loop
// Check if each element of that cell == any solved cells
// If any element == a solved cell, set that element = 0
int showPossible(int sudokuVal[9][9][9]) {
	int returnValue = 0;

	int solvedValue = 0;
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			if (isSolved(sudokuVal[row][column]) == 0) { // If cell is solved, 'continue', if not enter the loop
				for (int box = 0; box < 9; box++) {
					if (sudokuVal[row][column][box] == 0) { // if element in the this position == 0, 'continue' to save time
						continue;
					}
					else if (isExisted(sudokuVal, row, column, sudokuVal[row][column][box])) { // if element exist anywhere in its ROW, COLUMN, or 3x3 BOX, set it = 0
						sudokuVal[row][column][box] = 0;
						returnValue = 1;
					}
				}
			}

		}
	}
	return returnValue;
}
