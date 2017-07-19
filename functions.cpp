#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility> 
#include<iostream>
#include "functions.h"



Sodoku::Sodoku(std::istringstream& iss){
/* Input: a subsection of the file from project Euler problem 96
   Constructs, in row-major order, a sodoku board from the values given 
   TODO: add more constructors 
*/ 

	if (iss) {
		std::string line; 
		for (auto row = 0; row != 9; ++row) {
			getline(iss, line);
			for (auto col = 0; col != 9; ++col) 
				 board_[row][col] = line[col] - '0';
		}
	}
}  //ctor


Sodoku::Sodoku(std::ifstream& infile){
/* Input: a subsection of the file from project Euler problem 96
   Constructs, in row-major order, a sodoku board from the values given 
   TODO: add more constructors 
*/ 

	if (infile) {
		std::string line; 
		for (auto row = 0; row != 9; ++row) {
			getline(infile, line);
			for (auto col = 0; col != 9; ++col) 
				 board_[row][col] = line[col] - '0';
		}
	}
}  //ctor


bool Sodoku::ValidRow(int row_num, int col_num) {
/* Input: A number 0 - 8 representing the row to be checked
   If the row has no duplicate numbers 1-9, returns true
   col_num argument is just for ease/consistency
*/ 

	std::vector<int> v;
	for (auto i = 0; i != 9; ++i) {
		int *val = &board_[row_num][i];
		if (*val != 0 && std::find(v.begin(), v.end(), *val) != v.end()) 
				return false;
			else 
				v.push_back(*val);
	} //for 
	return true;
}


bool Sodoku::ValidCol(int row_num, int col_num) {
/* Input: A number 0 - 8 representing the column to be checked
   If the column has no duplicate numbers 1-9, returns true
   row_num argument is just for ease/consistency
*/ 

	std::vector<int> v;
	for (auto i = 0; i != 9; ++i) {
		int *val = &board_[i][col_num];
		if (*val != 0 && std::find(v.begin(), v.end(), *val) != v.end()) 
				return false;
			else 
				v.push_back(*val);
	} //for 
	return true; 
}

int Sodoku::GetBox(int num) {
/* Returns the number of the first row or column in any given box, ie 2->0, 4->3
   Input: a number 0-8 representing the row or column
*/ 
	switch(num){
	case 0:
	case 1:
	case 2: num = 0;
			break;
	case 3:
	case 4:
	case 5: num = 3;
			break;
	case 6:
	case 7:
	case 8: num = 6; 
			break;
	}
	return num; 
}


bool Sodoku::ValidBox(int row_num, int col_num) {
/*  Input: two numbers 0-8 representing the value to be checked
	Checks the box surrounding the number; if no numbers 0-9 are duplicate, 
	returns true
*/
	std::vector<int> v;
	row_num = GetBox(row_num); col_num = GetBox(col_num);
	for(auto row = row_num; row != row_num + 3; ++row){
		for(auto col = col_num; col != col_num + 3; ++col){
			int *val = &board_[row][col];
			if ( (*val != 0 && std::find(v.begin(), v.end(), *val) != v.end())
				|| *val > 9) 
				return false;
			else 
				v.push_back(*val);
		} //for
	} //for
	return true; 
} 


bool Sodoku::ValidValue(int row_num, int col_num) {
/* Input: two numbers 0-8 representing the position to be checked
   Checks the value at the given row and column number on having 
   a valid column, row, and box.
*/ 
	if (!ValidCol(row_num, col_num) ||
        !ValidRow(row_num, col_num) ||
        !ValidBox(row_num, col_num))
       return false; 
	else return true; 
} 


bool Sodoku::ValidBoard() {
/* Selects 9 key points in the board that can determine whether every row, 
   column, and box is sound.  Returns true if all points return true.
   TODO: find a more elegant approach for picking points
*/ 
	std::vector<std::pair<int, int>> key_points;
	key_points = {{0,0}, {1,3}, {2,6}, {3,1}, {4,4}, {5,7}, {6,2}, {7,5}, {8,8}};
	for(auto iter = key_points.begin(); iter != key_points.end(); ++iter){
		if (!ValidValue(iter->first, iter->second))
			return false;
	}
	return true; 
}


bool Sodoku::SolvedBoard() {
/* Returns true if a given board is solved, with entirely valid values and no 0's
*/
	if (ValidBoard()) {
		for (auto row = 0; row != 9; ++row){
			for (auto col = 0; col != 9; ++col){
				if (board_[row][col] == 0)
					return false; 
				}
			}
		}
	else if (!ValidBoard()) return false;
	return true; 
}


void Sodoku::GetChangeableCoords() {
/* Parses the board to see which coords are initially set to 0; 
   Returns a list of malleable coords
*/ 

	for (auto row = 0; row != 9; ++row){
		for (auto col = 0; col != 9; ++col){
			if (board_[row][col] == 0)
				changeable_coords_.push_back(std::make_pair(row, col));
		}
	}
}

Sodoku& Sodoku::Solve(){
/* Input: an unsolved Sodoku board
   For every value in the board, increments the value until the board is valid, 
   then moves to the next value.  If the value reaches 10 and the board is still
   not valid, move to the previous cell an continue to increment
*/
	int *val; 
	GetChangeableCoords();
	auto pos = changeable_coords_.begin();
	while(pos != changeable_coords_.end()){
		val = &board_[pos->first][pos->second];
		*val += 1;
		if(ValidBoard())
			pos++; 
		else if (*val > 9) {
			*val = 0;
			pos--;
		}
	}
	return *this;
}



std::ostream& operator<<(std::ostream& out, Sodoku& soduku) {
/* Inputs: a Sodoku object and an ostream to print to
   Prints a current visual representation of the Sodoku board
*/

	out << std::string(23, '-') << std::endl;
	for(auto row = 0; row != 9; ++ row) {
		out << "|";
		for(auto col = 0; col != 9; ++col) {
			out << soduku.board_[row][col] << " ";
			if (col == 2 || col == 5 || col == 8) {
				out << "| ";
				} //if
			} //inner for 
		if (row == 2 || row == 5 || row == 8) {
			out << std::endl << std::string(23, '-');
			} //if
		out << std::endl;
	} //outer for 
	return out; 
} //operator<<
