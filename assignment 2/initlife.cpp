// initcell.cpp
// Holds initializations and constants.
#include "initlife.h"

void initcells(Cells& cell, int const num_cells, double const target_alive_fraction){
    // Simulation creation
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
}
