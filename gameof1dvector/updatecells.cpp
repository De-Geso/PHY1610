// updatecells.cpp
//
// See updatecells.h for documentation.
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
//

#include "updatecells.h"

// Determine next state of a single cell based on the state of all the cells
bool next_cell_state(const Cells& cell_state, int cell_index) {
    int num_cells = cell_state.size();
    int alive_neighbours = 0;
    for (int j = 1; j <= 2; j++) {
        // note: the modulus operator (%) enforces periodic boundary
        // conditions
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

Cells update_all_cells(const Cells& oldcell) {
    int num_cells = oldcell.size(); 
    Cells newcell(num_cells);
    for (int i = 0; i < num_cells; i++) 
        newcell[i] = next_cell_state(oldcell, i);
    return newcell;
}
