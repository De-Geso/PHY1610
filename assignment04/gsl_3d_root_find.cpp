// gsl_3d_root_find.cpp

#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

// Parameters
struct rparams {
	double k1, k2, x0, y0, z0, c1, c2;
};

// Define the system of equations
int reaction (const gsl_vector * x, void * p, gsl_vector * f) {
	// Get all the parameters
	struct reaction_params * params = (struct reaction_params *)p;
	double k1 = ((struct rparams *) params)->k1;
	double k2 = ((struct rparams *) params)->k2;
	double x0 = ((struct rparams *) params)->x0;
	double y0 = ((struct rparams *) params)->y0;
	double z0 = ((struct rparams *) params)->z0;
	double c1 = ((struct rparams *) params)->c1;
	double c2 = ((struct rparams *) params)->c2;
	
	// Get x, y, z
	const double r0 = gsl_vector_get (x,0);
	const double r1 = gsl_vector_get (x,1);
	const double r2 = gsl_vector_get (x,2);
	
	// The actual equations we want to solve
	const double f0 = k2*r2*r2 - k1*r0*r0*r1;
	const double f1 = c1 - r0 + 2.*r1;
	const double f2 = c2 - r0 - r2;
	
	// Give the functions their new evaluations
	gsl_vector_set (f, 0, f0);
	gsl_vector_set (f, 1, f1);
	gsl_vector_set (f, 2, f2);
	
	// Hopefully it was successful
	return GSL_SUCCESS;
}

// This is just to watch the action. Print out our current x, y, z, and 
// function values.
int print_state (size_t iter, gsl_multiroot_fsolver * s) {
		printf ("iter = %3u x = % .3f % .3f % .3f "
			"f(x) = % .3e %.3e % .3e\n",
			iter,
			gsl_vector_get (s->x,0),
			gsl_vector_get (s->x,1),
			gsl_vector_get (s->x,2),
			gsl_vector_get (s->f,0),
			gsl_vector_get (s->f,1),
			gsl_vector_get (s->f,2));
		return 0;
}


int main(void) {
	const gsl_multiroot_fsolver_type *T;
	gsl_multiroot_fsolver *s;
	
	int status;
	size_t i, iter = 0;
	
	// Number of equations
	const size_t n=3;
	// Give the values for the parameters
	struct rparams p = {1., 0.7, 0.5, 1., 0., -1.5, 0.5};
	// Feed gsl the function
	gsl_multiroot_function f = {&reaction, n, &p};
	
	// Initial values to start our search from.
	double x_init[3] = {10.0, -10.0, 5.0};
	gsl_vector *x = gsl_vector_alloc (n);
	
	// Initialize x, y, z vector.
	gsl_vector_set (x, 0, x_init[0]);
	gsl_vector_set (x, 1, x_init[1]);
	gsl_vector_set (x, 2, x_init[2]);
	
	// Choose the hybrids algorithm and make the solver.
	T = gsl_multiroot_fsolver_hybrids;
	s = gsl_multiroot_fsolver_alloc (T, 3);
	
	// Initialize the solver
	gsl_multiroot_fsolver_set (s, &f, x);
	
	print_state (iter, s);
	
	do {
		iter++;
		status = gsl_multiroot_fsolver_iterate (s);
		
		print_state (iter, s);
		
		// If the solver is done, stop iterating
		if (status)
			break;
			
		// Check if our residual is smaller than the threshold.
		status = gsl_multiroot_test_residual (s->f, 1e-6);
	}
	while (status == GSL_CONTINUE && iter < 1000);
	
	// Print final values
	printf ("status = %s\n", gsl_strerror (status));
	printf ("x0 = %f\n"
		"x1 = %f\n"
		"x2 = %f\n",
		gsl_vector_get (s->x,0),
		gsl_vector_get (s->x,1),
		gsl_vector_get (s->x,2)
		);
	
	// Free up the memory we were using.
	gsl_multiroot_fsolver_free (s);
	gsl_vector_free (x);
	return 0;
} // end main
