// iter_laplace.cpp
// See iter_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "iter_laplace.h"


double get_max_change(const rarray<double,2>& oldgrid, 
	const rarray<double,2>& newgrid, 
	int n) {
		
	double max_change = 0;
	// Check entire grid for largest change.
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < n-1; j++) {
			// If the current change is bigger than the last biggest
			// change, it becomes the biggest change.
			if (fabs(oldgrid[i][j]-newgrid[i][j]) > max_change) {
				max_change = fabs(oldgrid[i][j]-newgrid[i][j]);
			}
		}
	}
	return max_change;
}


double next_grid_val(const rarray<double,2>& grid_state, int ii, int jj) {
	double V;
	V = (grid_state[ii+1][jj] +
		grid_state[ii-1][jj] +
		grid_state[ii][jj+1] +
		grid_state[ii][jj-1]) / 4;
	return V;
}

rarray<double,2> update_grid(const rarray<double,2>& oldgrid, int n) {
	int n_inner = get_n_inner(n);
	double max_change = 0.0;
	rarray<double,2> newgrid(n,n);
	
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < n-1; j++) {
			if ((abs(i-(n-1)/2) <= n_inner/2) && (abs(j-(n-1)/2) <= n_inner/2))
				newgrid[i][j] = 1;
			else
				newgrid[i][j] = next_grid_val(oldgrid, i, j);
		}
	}
	// The edges start to take some weird ~E-300 values after a while,
	// so reset them as we do to the inner box.
	for (int i = 0; i < n; i++) {
		newgrid[i][0] = 0.;
		newgrid[i][n-1] = 0.;
		newgrid[0][i] = 0.;
		newgrid[n-1][i] = 0.;
	}
	return newgrid;	
}
