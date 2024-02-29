// output_laplace.h
// Outputs the final solution in some format that GNUplot can handle.

#ifndef OUTPUT_LAPLACEH
#define OUTPUT_LAPLACEH

#include <rarray>
#include <iostream>
#include <fstream>

void dump_grid(const rarray<double,2>& grid, int n);

#endif
