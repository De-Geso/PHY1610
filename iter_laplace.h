// iter_laplace.h
// Steps one iteration forward.
#ifndef ITER_LAPLACEH
#define ITER_LAPLACEH

#include <rarray>
#include "init_laplace.h"

rarray<double,2> update_grid(const rarray<double,2>& oldgrid, int n);

#endif
