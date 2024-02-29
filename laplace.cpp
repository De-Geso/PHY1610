#include <iostream>
#include <rarray>
#include "init_laplace.h"
#include "iter_laplace.h"
#include "output_laplace.h"

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
    int err = 0;
	int n = 500;
	double eps = 1E-6;
	
	// Try to get the user input and avoid errors (impossible).
	try {
		if (argc > 1) {
			try{
				n = std::stoi(argv[1]);
				if (n <= 3) {
					std::cout << "If n<=3 the solution is trivial. Try again.\n";
					err = 1;
				}
			} catch (...){
				err = error_message(argv);
			}
			if (argc > 2){
				try{
					eps = std::stod(argv[2]);
				} catch (...) {
					err = error_message(argv);
				}
			}
		}
	} catch(...) {
		err = error_message(argv);
	}
	// If something illegal happened, (or we asked for help) exit the program
	if (err != 0) {
		exit(EXIT_FAILURE);
	}
	
	// Output our parameters for book keeping, and to visually check input
	std::cout << "grid size = " << n << std::endl;
	std::cout << "epsilon = " << eps << std::endl;	
	
	// Initialize grid, and make a copy for updates
	rarray<double,2> grid = initial_grid(n);
	rarray<double,2> grid_next = grid.copy();
	
	int counter = 0;
	double max_change = eps + 1;
	// Drive the iterations
	do {
		// Update the grid
		grid_next = update_grid(grid, n);
		// Every x steps, check the change. Checking too often or too seldom
		// increases run time. Faster than checking every single iteration.
		// Even if we check as we update.
		if (counter > 1E3) {
			max_change = get_max_change(grid, grid_next, n);
			counter = 0;
		}
		grid = grid_next;
		counter++;
	} 
	while (max_change > eps);
	
	// Dump to file
	dump_grid(grid, n);	
} // end main
