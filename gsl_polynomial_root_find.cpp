// gsl_polynomial_root_find.cpp

#include <iostream>
#include <stdio.h>
#include <gsl/gsl_poly.h>

int main(void) {
	int i;
	// System initialization.
	double k1=1., k2=0.7, x0=0.5, y0=1., z0=0.;
	double c1=x0-2.*y0 , c2=x0+z0;
	double x[3];
	
	// Coefficients of P(x)
	double a[3] = {-(c1*k1 + 2.*k2) / k1, 4.*c2*k2 / k1, -2.*k2*c2*c2 / k1};
	
	gsl_poly_solve_cubic (a[0], a[1], a[2], &x[0], &x[1], &x[2]);
	
	
} // end main
