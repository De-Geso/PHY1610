// output_laplace.cpp
// See output_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "output_laplace.h"

void dump_grid(const rarray<double,2>& grid, int n) {
	std::ofstream myfile;
	myfile.open ("laplace_solution.dat");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			myfile.width(16);
			myfile << std::left << grid[i][j];
		}
		myfile << '\n';
	}
	myfile.close();
}
