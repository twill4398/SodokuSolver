#ifndef SODUKU_H
#define SODUKU_H

#include<iostream>
#include<sstream>
#include<vector>
#include<utility>


class Sodoku{
private:
	int board_[9][9]{};
	std::vector<std::pair<int, int>> changeable_coords_;
	int GetBox(int);
	bool ValidCol(int, int);
	bool ValidRow(int, int);
	bool ValidBox(int, int);
	bool ValidValue(int, int);
	bool ValidBoard();
	void GetChangeableCoords();
	

public: 
	Sodoku() = default; 
	Sodoku(std::istringstream&); 
	Sodoku(std::ifstream&);
	bool SolvedBoard();
	friend std::ostream& operator<<(std::ostream&, Sodoku&);
	Sodoku& Solve();

};

#endif 
