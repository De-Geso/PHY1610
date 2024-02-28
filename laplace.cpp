#include <iostream>
#include <rarray>
#include "init_laplace.h"
#include "iter_laplace.h"

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
	int n = 10;
	double eps = 1E-6;
	
	try {
		if (argc > 1)
			n = std::stoi(argv[1]);
		if (argc > 2)
			eps = std::stoi(argv[2]);
    } catch(...) {
        std::cout <<
            "Solves a 2D Laplace equation\n\n"
            "Usage:\n"
            "  laplace [-h | --help] | [GRIDSIZE [EPSILON]]\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
			return 0;
	}
	
	// Initialize grid, and make a copy for updates.
	rarray<double,2> grid = initial_grid(n);
	rarray<double,2> grid_next = grid.copy();
	grid_next[0][0] = 10;
	std::cout << grid << std::endl;
	std::cout << grid_next << std::endl;
	
	grid = update_grid(grid_next, n);
	
	
} // end main
