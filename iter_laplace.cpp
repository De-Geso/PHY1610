// iter_laplace.cpp
// See iter_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "iter_laplace.h"

double next_grid_val(const rarray<double,2>& V, int ii, int jj) {
	
}

rarray<double,2> update_grid(const rarray<double,2>& oldgrid, int n) {
	int n_inner = get_n_inner(n);
	rarray<double,2> newgrid(n,n);
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < n-1; j++) {
			if (abs(i-n/2) > n_inner/2 && abs(j-n/2) > n_inner/2)
				newgrid[i][j] = next_grid_val(oldgrid, i, j);
		}
	}
	return newgrid;	
}
