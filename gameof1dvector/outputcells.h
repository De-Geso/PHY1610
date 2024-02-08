// outputcells.h
//
// Contains an output routine for cells 
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef OUTPUTCELLSH
#define OUTPUTCELLSH

#include "celltype.h"
#include <ostream>

// Output time step, state of cells, and fraction of alive cells 
// on one line into a output stream.
//
// @param  out   an out-stream (for instance std::cout or an std::ofstream) to write to
// @param  step  the step value to include in the output
// @param  cell  the alive/dead cells
// 
void output_cells(std::ostream& out, int step, const Cells& cell);

#endif
