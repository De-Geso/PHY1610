#include <iostream>
#include <rarray>
#include "init_laplace.h"
#include "iter_laplace.h"
#include "output_laplace.h"

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
	int n = 500;
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
	
	int counter = 0;
	double max_change = eps + 1;
	do {
		grid_next = update_grid(grid, n);
		if (counter > n/eps*1E-5) {
			max_change = get_max_change(grid, grid_next, n);
			counter = 0;
			std::cout << counter << '\t';
		}
		grid = grid_next;
		counter++;
	} 
	while (max_change > eps);
	
	dump_grid(grid, n);	
} // end main
