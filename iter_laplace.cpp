// iter_laplace.cpp
// See iter_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "iter_laplace.h"


double get_max_change(const rarray<double,2>& oldgrid, 
	const rarray<double,2>& newgrid, 
	int n) {
		
	double max_change = 0;
	
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < n-1; j++) {
			if (fabs(oldgrid[i][j]-newgrid[i][j]) > 0)
				max_change = fabs(oldgrid[i][j]-newgrid[i][j]);
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
			if (oldgrid[i][j] != 1)
				newgrid[i][j] = next_grid_val(oldgrid, i, j);
			else
				newgrid[i][j] = 1;
		}
	}
	return newgrid;	
}
