/*This program solves a sudoku puzzle. If the board is valid,
 it solves it using backtracking, otherwise prints that the board
 is not valid*/
#include <bits/stdc++.h>
using namespace std;
const int N = 9;
bool check_row(int board[N][N], int row, int digit) {
	/*This function checks the row for digit
	 if digit is found, it returns false
	 otherwise, returns true*/
	for(int i = 0; i < N; i ++) {
		if(board[row][i] == digit) {
			return false;
		}
	}
	return true;
}
bool check_col(int board[N][N], int col, int digit) {
	/*This function checks the column for digit
	 if digit is found, it returns false
	 otherwise, returns true*/
	for(int i = 0; i < N; i ++) {
		if(board[i][col] == digit) {
			return false;
		}
	}
	return true;
}
bool check_box(int board[N][N], int row, int col, int digit) {
	/*This function checks the bol (row, col) is part of for digit
	 if digit is found, it returns false
	 otherwise, returns true*/
	int box_row = row - (row % 3), box_col = col - (col % 3);
	for(int i = 0; i < 3; i ++) {
		for(int j = 0; j < 3; j ++) {
			if(board[i + box_row][j + box_col] == digit) {
				return false;
			}
		}
	}
	return true;
}
bool valid(int board[N][N], int row, int col, int digit) {
	/*This function checks if the digit can be placed at (row, col) or not
	 returns true if it can be placed
	 otherwise returns false*/
	return check_box(board, row, col, digit) & check_row(board, row, digit) & check_col(board, col, digit);
}
bool find_empty_location(int board[N][N], int &row, int &col) {
	/*This functions finds an empty cell
	 if not empty cell is found, it returns false
	 otherwise it changes row and col to coordinates of the empty cell and returns true*/
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			if(board[i][j] == 0) {
				row = i, col = j;
				return true;
			}
		}
	}
	return false;
}
bool solve(int board[N][N]) {
	/*This function solves the board*/
	int row, col;
	if(!find_empty_location(board, row, col)) {
		/*If no empty cell is found, the board is solved*/
		return true;
	}
	for(int digit = 1; digit <= 9; digit ++) {
		/*Iterating over each digit and checking if it can be placed in that cell*/
		if(valid(board, row, col, digit)) {
			board[row][col] = digit;
			/*Checking if the board can be solved by placing the digit at this location*/
			if(solve(board)) {
				/*If board can be solved, return true*/
				return true;
			}
			/*Clear the cell and find another digit*/
			board[row][col] = 0;
		}
	}
	/*If no digit can be placed to the current location, sending a signal to the previous call
	 that board cannot be solved, hence triggering backtracking*/
	return false;
}
void print(int board[N][N]) {
	/*This function prints the board*/
	for(int i = 0; i < N; i ++) {
		for(int j = 0; j < N; j ++) {
			cout << board[i][j] << " \n"[j == N - 1];
		}
	}
}
int main() {
	int board[N][N] = {{8, 0, 0, 0, 0, 0, 0, 0, 0},
		    		   {0, 0, 3, 6, 0, 0, 0, 0, 0},
			    	   {0, 7, 0, 0, 9, 0, 2, 0, 0},
		    		   {0, 5, 0, 0, 0, 7, 0, 0, 0},
		    		   {0, 0, 0, 0, 4, 5, 7, 0, 0},
					   {0, 0, 0, 1, 0, 0, 0, 3, 0},
				       {0, 0, 1, 0, 0, 0, 0, 6, 8},
				       {0, 0, 8, 5, 0, 0, 0, 1, 0},
				       {0, 9, 0, 0, 0, 0, 4, 0, 0}};
	cout << "The unsolved board : \n";
	print(board);
	if(solve(board)) {
		cout << "The solved board : \n";
		print(board);
	}
	else {
		cout << "The board is not valid!\n";
	}
 	return 0;
}
