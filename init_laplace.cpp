// init_laplace.cpp
// See filecells.h for documentation
// This code is part of assignment 5 of the 2024 Winter PHY1610 course.
#include "init_laplace.h"

rarray<double,2> initial_grid(int n)
{
    rarray<double,2> grid(n,n);
    int n_inner = round(0.1*n);
    if (n_inner==0)
		n_inner = 1;
    
    // Fill outer boundary. These should technically already be zero,
    // but it's probably good to be sure.
    for (int i = 0; i < n; i++) {
		// Fill top and bottom edges
		grid[0][i] = 0;
		grid[n-1][i] = 0;
		// Fill left and right edges
		grid[i][0] = 0;
		grid[i][n-1] = 0;
    }
    
    // Fill inner boundary. Round to side length as close as possible
    // to one tenth of outer sidelength. Try to place inner box in
    // middle, otherwise bias centre to top left.
    for (int i = (n-n_inner)/2; i < (n+n_inner)/2; i++) {
		for (int j = (n-n_inner)/2; j < (n+n_inner)/2; j++) {
			std::cout << i << '\t' << j << std::endl;
			grid[i][j] = 1;
		}
	}
    return grid;
}
