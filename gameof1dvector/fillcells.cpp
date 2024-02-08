// filecells.cpp
// 
// See filecells.h for documentation
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "fillcells.h"

Cells initial_cells(int num_cells, double target_alive_fraction)
{
    Cells cell(num_cells);
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
    return cell;
}
