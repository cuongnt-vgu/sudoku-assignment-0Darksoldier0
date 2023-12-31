#pragma once
#include <stdio.h>

void  generateInitialPossible(char sudoku[81], int sudokuVal[9][9][9]);
int isExisted(int sudokuVal[9][9][9], int row, int column, int data);
int isUnique(int sudokuVal[9][9][9], int row, int column, int data);
int isSolved(int sudokuVal[9]);
void display(int sudokuVal[9][9][9]);
void checkResult(int sudokuVal[9][9][9], char myResult[81], char result[81]);