// gameof1d.cpp
//
// This code computes the evolution of a one-dimensional variant of Conway's Game of Life,
// as conceived by Jonathan K. Millen and published in BYTE magazine in December, 1978.
//
// This system is a linear set of cells that are either "alive" or "dead".
// Time in this system progresses in discrete steps.
//
// The state of each cell at the next time step depends on its present
// state and that of its neighbors, in the following way:
//
//   - First, count the number of alive neighbors at most 2 cells away
//   - An alive cell stays alive if that count is 2 or 4, else it dies
//   - A dead cell becomes alive if that count is 2 or 3, else it stays dead.
//
// Since the first two and the last two cells would not have enough neighbours to apply
// this rule, we use cells on the other side as neighbours, i.e., 'periodic boundaries'.
//
// The initial state of this system is constructed with a given fraction of alive
// cells which are (nearly) equally spaced among dead cells.
//
// The code computes the time evolution for 120 steps, and for each step, prints out
// a line with a representation of the state and fraction of alive cells.
//
// This code is part of assignment 2 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2023-2024, University of Toronto

#include <iostream>
#include <memory>
#include "initlife.h"
#include "outputlife.h"
#include "updatelife.h"

// We use bool to store the state of each cell, but for convenience define the following
// Constants and definitions now live in initlife.h.

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
    int num_cells = 70;
    int num_steps = 120;
    double target_alive_fraction = 0.35;
    try {
        if (argc > 1)
            num_cells = std::stoi(argv[1]);
        if (argc > 2)
            num_steps = std::stoi(argv[2]);
        if (argc > 3)
            target_alive_fraction = std::stod(argv[3]);
    } catch(...) {
        std::cout <<
            "Computes a 1d version of Conway's game of life\n\n"
            "Usage:\n"
            "  gameof1d [-h | --help] | [NUMCELLS [NUMSTEPS [FRACTION]]]\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }
    
    // Simulation creation
    Cells cell(std::make_unique<bool[]>(num_cells));
    // Initialize state of the system. Lives in initcell.cpp
    initcells(cell, num_cells, target_alive_fraction);
    
    // Output time step, state of cells, and fraction of alive cells. Lives in outputlife.cpp
    dump_cells(cell, num_cells, 0);
    
    // Evolution loop
    for (int t = 0; t < num_steps; t++) {
        // Update cells
        Cells newcell = std::make_unique<bool[]>(num_cells);
        for (int i = 0; i < num_cells; i++) 
            newcell[i] = next_cell_state(cell, i, num_cells);
        std::swap(cell, newcell);  // swap without a copy
        // Output time step, state of cells, and fraction of alive cells
        dump_cells(cell, num_cells, t+1);
    }
} // end main
/*

Study the code, make sure you understand what's going on.

You are going to reorganize ('refactor') this code to be more modular.
The aim is to have separate functionalities be implemented in separate
functions. I.e., you should

  - Extract the part of the code that first fills the cell array, put
    it in a separate initialization function that then gets called
    from the main function, so that the program still produce the same
    output (check the output!).

  - Make this into a module, i.e., take out that initialization
    function and put it in a separate .cpp file and create a
    corresponding header file to be included in the original file.
  
  - Create a Makefile that can build the application.

  - Next, repeat these steps to create a module for the 
    part of the code that updates the cell array.

  - Next, repeat these steps to create a module for the output part of
    the code.

  - Be sure to comment your code.
  
Your submission should consist of all source files, headerfiles, and
the Makefile.  You may put them in a zip file or tar ball, in fact,
that is the recommended way.
    
*/
