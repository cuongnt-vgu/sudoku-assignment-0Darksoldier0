#include "Utilities.h"

// This function purpose is to populate the 3D array 'sudokuVal[9][9][9]'
// If 'unsolvedSudoku[i]' == 0, assign number from '1 to 9' to the cell 'sudokuVal[i][j]'
// If 'unsolvedSudoku[i]' != 0, assign number 'unsolvedSudoku[i]' to 'sudokuVal[i][j][0]', and assign '0' to the remaining elements
void  generateInitialPossible(char unsolvedSudoku[81], int sudokuVal[9][9][9]) {
	for (int row = 0; row < 9; row++) {
		for (int column = 0; column < 9; column++) {
			if (unsolvedSudoku[9 * row + column] - 48 == 0) {
				for (int box = 0; box < 9; box++) {
					sudokuVal[row][column][box] = box + 1;
				}
			}
			else {
				sudokuVal[row][column][0] = unsolvedSudoku[9 * row + column] - 48;
			}
		}
	}
}

// Check if 'data' equal a 'solved cell' (cell that has number of element greater than '1' == 1) in either its ROW, COLUMN, or 3x3 BOX, 
// If 'data' == any 'solved cell' return 1, otherwise return 0;
int isExisted(int sudokuVal[9][9][9], int row, int column, int data) {
	int row_temp;
	int column_temp;

	column_temp = 0;
	// Check for element in cells of its ROW that == 'data'
	for (column_temp; column_temp < 9; column_temp++) {
		if (column_temp == column) { // Prevent checking for itself
			continue;
		}
		if (data == isSolved(sudokuVal[row][column_temp])) {
			return 1;
		}
	}

	row_temp = 0;
	// Check for elements in cells of its COLUMN that == 'data'
	for (row_temp; row_temp < 9; row_temp++) {
		if (row_temp == row) { // Prevent checking for itself
			continue;
		}
		if (data == isSolved(sudokuVal[row_temp][column])) {
			return 1;
		}
	}


	// These 4 lines tell which 3x3 BOX the 'data' is in
	row_temp = (row / 3) * 3;
	int row_limit = row_temp + 3;
	column_temp = (column / 3) * 3;
	int column_limit = column_temp + 3;

	// Check for elements in cells in a 3x3 box that == 'data'
	for (row_temp; row_temp < row_limit; row_temp++) {
		for (column_temp; column_temp < column_limit; column_temp++) {
			if (row_temp == row && column_temp == column) { // Prevent checking to itself
				continue;
			}
			if (data == isSolved(sudokuVal[row_temp][column_temp])) {
				return 1;
			}
		}
		column_temp = (column / 3) * 3;
	}

	return 0;
}

// Check if 'data' appear only once in either its ROW, COLUMN, or 3x3 BOX
int isUnique(int sudokuVal[9][9][9], int row, int column, int data)
{
	int row_unique = 1;
	int column_unique = 1;
	int box_unique = 1;
	int solvedValue = 0;
	int row_temp;
	int column_temp;

	// Check if 'data' is unique in a row
	column_temp = 0;
	for (column_temp; column_temp < 9 && row_unique == 1; column_temp++) {
		if (column_temp != column) {
			for (int box = 0; box < 9 && row_unique == 1; box++) {
				if (data == sudokuVal[row][column_temp][box]) {
					row_unique = 0;
				}
			}
		}
	}

	// Check if 'data' is unique in a column
	row_temp = 0;
	for (row_temp; row_temp < 9 && column_unique == 1; row_temp++) {
		if (row_temp == row) { // Prevent checking for itself
			continue;
		}
		else {
			for (int box = 0; box < 9 && column_unique == 1; box++) {
				if (data == sudokuVal[row_temp][column][box]) {
					column_unique = 0;
				}
			}
		}
	}

	// These 4 line tell which 3x3 BOX the 'data' is in
	row_temp = (row / 3) * 3;
	int row_limit = row_temp + 3;
	column_temp = (column / 3) * 3;
	int column_limit = column_temp + 3;

	// Check if 'data' is unique in a 3x3 box
	for (row_temp; row_temp < row_limit && box_unique == 1; row_temp++) {
		for (column_temp; column_temp < column_limit && box_unique == 1; column_temp++) {
			if (row_temp == row && column_temp == column) { // Prevent checking for itself
				continue;
			}
			else {
				for (int box = 0; box < 9 && box_unique == 1; box++) {
					if (data == sudokuVal[row_temp][column_temp][box]) {
						box_unique = 0;
					}
				}
			}
		}
		column_temp = (column / 3) * 3;
	}

	return row_unique || column_unique || box_unique;
}

// Count the number of elements in the cell is greater than 0,
// if only 1 element greater than 0 return 1 (that cell is solved)
// If more than 1 element greater than 0, return 0 (that cell is not solved);
int isSolved(int sudokuVal[9]) {
	int count = 0;
	int solvedValue = 0;
	for (int i = 0; i < 9; i++) {
		if (sudokuVal[i] != 0) {
			solvedValue = sudokuVal[i];
			count++;
			if (count > 1) {
				return 0;
			}
		}
	}
	return solvedValue;
}

// Display all elements in each cell of the sudoku board. 
void display(int sudokuVal[9][9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("[%d][%d]: ", i + 1, j + 1);
			for (int k = 0; k < 9; k++) {
				printf("%d ", sudokuVal[i][j][k]);
			}
			printf("\n");
		}
	}
}

// Check if elements in 'myResult' == elements in 'result'
void checkResult(int sudokuVal[9][9][9], char myResult[81], char result[81])
{
	// Go to each cell, and copy element != 0 and put it in 'myResult'
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			for (int k = 0; k < 9; k++) {
				if (sudokuVal[i][j][k] != 0) {
					myResult[9 * i + j] = (char)sudokuVal[i][j][k];
				}
			}
		}
	}

	// Print out the 'Correct Result' of the puzzle 
	printf("Correct Result: \n");
	for (int i = 0; i < 81; i++) {
		printf("%d", result[i] - 48);
	}

	// Print out the 'My Result' of the puzzle
	printf("\n");
	printf("My Result:\n");
	for (int i = 0; i < 81; i++) {
		printf("%d", myResult[i]);
	}

	//  Compare the 2 outputs, if match print 'Sucessfully Solved!!!!!!' otherwise print 'Unsucessfully Solved :(((((((((('
	printf("\n");
	for (int i = 0; i < 81; i++) {
		if (myResult[i] != result[i] - 48) {
			printf("Unsucessfully Solved :((((((((((");
			return;
		}
	}
	printf("Sucessfully Solved!!!!!!");
}
