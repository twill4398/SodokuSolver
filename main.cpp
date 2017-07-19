#include<fstream>
#include<iostream>
#include<vector>
#include<utility>
#include<sstream>
#include "functions.h"


int main(){
	std::ifstream input_file("p096_sudoku.txt");
	std::ofstream output_file("p096_sodoku_solns.txt");
	std::string line; 
	std::string puzzle; 
	size_t p = 1;  
	input_file.ignore(10, '\n');
	while (input_file.good()){
		if (isdigit(input_file.peek())) {
			getline(input_file, line);
			puzzle += line + '\n';
		}
		else{
			std::istringstream iss(puzzle);
			Sodoku sodoku(iss);
			puzzle = "";
			sodoku.Solve();
			output_file << "Puzzle: " << p << std::endl;
			if (sodoku.SolvedBoard())
				output_file << sodoku << std::endl;
			input_file.ignore(10, '\n');
			p++; 
		}
	
	}
}
/*
int main(){
	std::ifstream infile("test1.txt");
	Sodoku sodoku(infile);
	sodoku.changeable_coords_ = sodoku.GetChangeableCoords();
	// for (auto i = sodoku.changeable_coords_.begin(); i != sodoku.changeable_coords_.end(); ++i)
	//	std::cout << i->first << " " << i->second << std::endl;
	std::cout << sodoku.Solve() << std::endl;
}
*/
