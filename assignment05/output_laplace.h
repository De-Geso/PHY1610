// output_laplace.h
// Outputs the final solution in some format that GNUplot can handle.

#ifndef OUTPUT_LAPLACEH
#define OUTPUT_LAPLACEH

#include <rarray>
#include <iostream>
#include <fstream>

// Output the fancy input error message.
int error_message(char* argv[]);

// Dumps the current grid into a file which stores the array in a way
// which GNUplot can easily plot.
// @param  grid	current grid
// @param  n	size of grid
void dump_grid(const rarray<double,2>& grid, int n);

#endif
