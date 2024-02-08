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

// We use bool to store the state of each cell, but for convenience define the following
const bool alive = true;
const bool dead = false;
using Cells = std::unique_ptr<bool[]>;
// Determine next state of a single cell based on the state of all the cells
bool next_cell_state(const Cells& cell_state, int cell_index, int num_cells) {
    // the modulus operator (%) enforces periodic boundary conditions
    int alive_neighbours = 0;
    for (int j = 1; j <= 2; j++) {
        if (cell_state[(cell_index+j+num_cells)%num_cells] == alive)
            alive_neighbours++;
        if (cell_state[(cell_index-j+num_cells)%num_cells] == alive)
            alive_neighbours++;
    }
    if (cell_state[cell_index] == alive  and
        (alive_neighbours == 2 or alive_neighbours == 4))
        return alive;
    else if (cell_state[cell_index] == dead  and
               (alive_neighbours == 2 or alive_neighbours == 3))
        return alive;
    else
        return dead;
}

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
    // Fill cells such that the fraction of alive cells is approximately target_alive_fraction.
    double fill = 0.0;
    for (int i = 0; i < num_cells; i++) {
        fill += target_alive_fraction;
        if (fill >= 1.0) {
            cell[i] = alive;
            fill -= 1.0;
        } else
            cell[i] = dead;
    }
    // Output time step, state of cells, and fraction of alive cells
    const char on_char = 'I', off_char = '-';
    double alive_fraction = 0.0;
    for (int i = 0; i < num_cells; i++) 
        if (cell[i] == alive)
            alive_fraction++;
    alive_fraction /= num_cells;
    std::cout << 0 << "\t";
    for (int i = 0; i < num_cells; i++)
        if (cell[i] == alive)
            std::cout << on_char;
        else
            std::cout << off_char;
    std::cout << " " << alive_fraction << "\n";
    // Evolution loop
    for (int t = 0; t < num_steps; t++) {
        // Update cells
        Cells newcell = std::make_unique<bool[]>(num_cells);
        for (int i = 0; i < num_cells; i++) 
            newcell[i] = next_cell_state(cell, i, num_cells);
        std::swap(cell, newcell);  // swap without a copy
        // Output time step, state of cells, and fraction of alive cells
        alive_fraction = 0.0;
        for (int i = 0; i < num_cells; i++)
            alive_fraction += cell[i];
        alive_fraction /= num_cells;
        std::cout << t+1 << "\t";
        for (int i = 0; i < num_cells; i++)
            if (cell[i] == alive)
                std::cout << on_char;
            else
                std::cout << off_char;
        std::cout << " " << alive_fraction << "\n";
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
