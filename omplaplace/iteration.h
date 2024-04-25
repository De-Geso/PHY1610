#ifndef _ITERATION_H_
#define _ITERATION_H_

#include <rarray>

// Apply local average of V surrounding points; requires a helper
// array to be passed in. Upon return, new values will be in V, old
// values are stored in Vprev.
//
// @param V     Field to locally average
// @param Vprev Helper array
//
void apply_average(rmatrix<double>&V, rmatrix<double>&Vprev); 

// Compute the maximum absolute difference of the corresponding
// elements of two arrays.
//
// @param a First array with values.
// @param b Second array with values.
//
// @returns Maximum absolute difference.
//
double get_max_diff(const rmatrix<double>& a, const rmatrix<double>& b);

#endif
