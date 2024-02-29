// output_laplace.cpp
// See output_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "output_laplace.h"

// Output fancy error message.
int error_message(char* argv[]) {
	std::cout <<
		"Solves a 2D Laplace equation\n\n"
		"Usage:\n"
		"  laplace [-h | --help] | [int GRIDSIZE(Default 500) [double EPSILON (Default 1e-6)]]\n\n";
	if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
		std::cerr << "Error in arguments!\n";
	}
	return 1;
}

// Dump to file
void dump_grid(const rarray<double,2>& grid, int n) {
	// get the file.
	std::ofstream myfile;
	myfile.open ("laplace_solution.dat");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// make it kinda tab separated so that GNUplot can just plot it.
			myfile.width(16);
			myfile << std::left << grid[i][j];
		}
		myfile << '\n';
	}
	myfile.close();
}
