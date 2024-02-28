// init_laplace.h
// Contains an initialization routine for a grid.

#ifndef INIT_LAPLACEH
#define INIT_LAPLACEH

#include <rarray>

// Get the side length of the inner box
int get_n_inner(int n);

// Fill grid such that the outer box edge is V=0, and there is a 
// centered inner box with side lengths one tenth the length of the
// outer box set to V=1. The inner box size is as close as possible, 
// and position may be off centre by 1 point, biased to top left.
// @param  n	size of grid to initialize
// @returns a 2d grid with the boundary conditions set
rarray<double,2> initial_grid(int n);

#endif
