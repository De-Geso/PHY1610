// updatelife.cpp
// Updates the state of the cells in the game of life.
// See gameof1d.cpp for rules of the game.
#include "updatelife.h"
#include "initlife.h"

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
