// iter_laplace.h
// Steps one iteration forward.
#ifndef ITER_LAPLACEH
#define ITER_LAPLACEH

#include <rarray>
#include "init_laplace.h"


// Check for largest difference between old and new grid by checking
// all coordinates.
// @param  oldgrid	grid from 1 step previous
// @param  newgrid	current grid
// @param  n	size of grid to initialize
// @returns	largest change in a single cell between grids
double get_max_change(const rarray<double,2>& oldgrid, const rarray<double,2>& newgrid, int n);

// Apply Laplace step according to rules in Assignment 5
// Basically cell value becomes average of its nearest neighbours
// @param  grid_state	current grid
// @param  ii	together with jj, position of cell we're evaluating.
// @param  jj	
// @returns	largest change in a single cell between grids
double next_grid_val(const rarray<double,2>& grid_state, int ii, int jj);

// Updates all cells on the grid.
// @param  oldgrid	current grid
// @param  n	size of grid
// @returns	grid updated according to Laplace's equation.
rarray<double,2> update_grid(const rarray<double,2>& oldgrid, int n);

#endif
