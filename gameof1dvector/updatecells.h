// updatecells.h
//
// Contains an update routine for cells of the 1d game of life
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef UPDATECELLSH
#define UPDATECELLSH

#include "celltype.h"

// Determine next state of all cells based on the state of all the cells
//
// @param  oldcell  the previous alive/dead values of the cells.  This is a vector that knows its size.
// 
// @returns a new vector with the updated alive/dead values of all cells.
//
Cells update_all_cells(const Cells& oldcell);

#endif
