#ifndef _BOUNDARY_H_
#define _BOUNDARY_H_

#include <rarray>

// Impose the boundary conditions: 0 on the outer boundary, 1 on an
// inner rectangle. 
//
// @param V        Matrix containing the (laplace) field;
// @param fraction What linear fraction is the inner rectangle.
//  
void set_boundary_condition(rmatrix<double>& V, double fraction);

#endif
