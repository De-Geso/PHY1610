// init_laplace.cpp
// See init_laplace.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "init_laplace.h"


int get_n_inner(int n)
{
	int n_inner;
	n_inner = round(0.1*n);
    // Make sure the inner box is actually there.
    if (n_inner < 1)
		n_inner = 1;
	return n_inner;
}

rarray<double,2> initial_grid(int n)
{
    rarray<double,2> grid(n,n);
    int n_inner = get_n_inner(n);
    
    // Fill outer boundary. These should technically already be zero,
    // but it's probably good to be sure.
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = 0.5;
		}
		// Fill top and bottom edges
		grid[0][i] = 0.;
		grid[n-1][i] = 0.;
		// Fill left and right edges
		grid[i][0] = 0.;
		grid[i][n-1] = 0.;
    }
    // Fill inner boundary. Round to side length as close as possible
    // to one tenth of outer sidelength. Try to place inner box in
    // middle, otherwise bias centre to top left.
    for (int i = (n-n_inner)/2; i < (n+n_inner)/2; i++) {
		for (int j = (n-n_inner)/2; j < (n+n_inner)/2; j++) {
			grid[i][j] = 1;
		}
	}
    return grid;
}
