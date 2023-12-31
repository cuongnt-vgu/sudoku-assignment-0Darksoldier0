#include <stdio.h>
#include <stdlib.h>
#include "ShowPossible.h"
#include "HiddenSingle.h"




int main()
{
	// Copy and paste the test case here
	char unsolvedSudoku[81] = "000105000140000670080002400063070010900000003010090520007200080026000035000409000";
	// Copy and paste the output of the test case here
	char result[81] = "672145398145983672389762451263574819958621743714398526597236184426817935831459267";

	// This is where the output of the algorithm saved to
	char myResult[81] = { 0 };

	// Create a 3D array, and assign 0 to all element
	int sudokuVal[9][9][9] = { 0 };

	// Code below this line start the testing process
	// For the current stage of my program it can only solve upto the 'gentle' difficulty on this website: https://www.sudokuwiki.org/sudoku.htm
	generateInitialPossible(unsolvedSudoku, sudokuVal);
	int flag = 1; // Indication when to exit the loop
	while (flag) {
		flag = 0;
		while (showPossible(sudokuVal)) {
			flag = 1;
		}
		while (hiddenSingle(sudokuVal)) {
			flag = 1;
		}
	}
	checkResult(sudokuVal, myResult, result);
}