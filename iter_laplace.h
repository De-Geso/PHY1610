// iter_laplace.h
// Steps one iteration forward.
#ifndef ITER_LAPLACEH
#define ITER_LAPLACEH

#include <rarray>
#include "init_laplace.h"

double get_max_change(const rarray<double,2>& oldgrid, const rarray<double,2>& newgrid, int n);

double next_grid_val(const rarray<double,2>& grid_state, int ii, int jj);

rarray<double,2> update_grid(const rarray<double,2>& oldgrid, int n);

#endif
