// outputlife.cpp
// Screen output for game of life
#include "outputlife.h"

void dump_cells(std::unique_ptr<bool[]>& cell, int const num_cells, int const step){
	// Dumps the current state of the system to output. NOTE: it will output
	// the current step, but I chose not to track or increment the step within
	// the function. Step is completely controlled by main.
	
	// Characters for dead/alive
    const char on_char = 'I', off_char = '-';
    double alive_fraction = 0.0;
    // Calculate fraction of alive cells
    for (int i = 0; i < num_cells; i++) 
        if (cell[i] == alive)
            alive_fraction++;
    alive_fraction /= num_cells;
    // Output line of cells to screen
    std::cout << step << "\t";
    for (int i = 0; i < num_cells; i++)
        if (cell[i] == alive)
            std::cout << on_char;
        else
            std::cout << off_char;
    std::cout << " " << alive_fraction << "\n";
}
