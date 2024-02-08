// fillcells.h
//
// Contains an initialization routine for a one-dimensional array of cells 
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef FILECELLSH
#define FILECELLSH

#include "celltype.h"

// Fill cells such that the fraction of alive cells is approximately
// target_alive_fraction. Approximately, because the fraction might not 
// be expressible as a fraction with a denominator of num_cells. 
//
// @param  num_cells              the number of cells to generate
// @param  target_alive_fraction  the fraction of cells to be alive
//
// @returns a 1d array of cells that are alive or dead.
//
Cells initial_cells(int num_cells, double target_alive_fraction);

#endif
