#ifndef _INITIALIZE_H_
#define _INITIALIZE_H_

#include <rarray>

// Create an initial field, subject to the boundary conditions.
// Calls the boundary_condition, which imposes a value of an inner
// rectangle.
//
// @param n The number of points in the x direction.
// @param m The number of points in the y direction.
// @param fraction What linear fraction is the inner rectangle.
//
rmatrix<double> init(size_t n, size_t m, double fraction);

#endif
