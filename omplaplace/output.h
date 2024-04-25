#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <string>
#include <rarray>

// Print a matrix in a form that gnuplot can visualize, i.e., as x,y,z
// pairs.
//
// @param o An ostream to sent the output to.
// @param a The matrix to write.
//
void ncoutput(const std::string& filename, const rmatrix<double>& a);

#endif
