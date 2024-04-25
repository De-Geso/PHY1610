// gsl_polynomial_root_find.cpp
// Find the roots of the given cubic polynomial for the given chemical
// reaction using GSL libraries.

#include <iostream>
#include <stdio.h>
#include <gsl/gsl_poly.h>

int main(void) {
	int i;
	// System initialization.
	const double k1=1., k2=0.7, x0=0.5, y0=1., z0=0.;
	const double c1=x0-2.*y0 , c2=x0+z0;
	double x[3]={0., 0., 0.};
	
	// Coefficients of P(x)
	double a[3] = {-(c1*k1 + 2.*k2) / k1, 4.*c2*k2 / k1, -2.*k2*c2*c2 / k1};
	
	// Use gsl libraries to solve the polynomial
	gsl_poly_solve_cubic (a[0], a[1], a[2], &x[0], &x[1], &x[2]);
	
	// There's one root, which is given as x0. Use our relationships
	// to calculate y and z.
	x[1] = (x[0] - c1) / 2.;
	x[2] = c2 - x[0];
	
	// Output the roots.
	for (i=0; i<3; i++) {
		printf("x%d = %f\n", i, x[i]);
	}
} // end main
