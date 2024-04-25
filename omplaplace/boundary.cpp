#include "boundary.h"

// Impose the boundary conditions: 0 on the outer boundary, 1 on an
// inner rectangle. 
//
// @param V        Matrix containing the (laplace) field;
// @param fraction What linear fraction is the inner rectangle.
//  
void set_boundary_condition(rmatrix<double>& V, double fraction) {
    const size_t n = V.extent(0);
    const size_t m = V.extent(1);
    const size_t imid = (n-1)/2;
    const size_t jmid = (m-1)/2;
    const size_t iflat1 = imid - fraction*n/2;
    const size_t iflat2 = imid + fraction*n/2;
    const size_t jflat1 = jmid - fraction*n/2;
    const size_t jflat2 = jmid + fraction*n/2;
    for (size_t i = 0; i < n; i++) 
         V[0][i] = V[n-1][i] = 0.0;
    for (size_t j = 0; j < m; j++) 
         V[j][0] = V[j][m-1] = 0.0;
    for (size_t i = iflat1; i <  iflat2; i++)
        for (size_t j = jflat1; j <  jflat2; j++)
            V[i][j] = 1.0;
}

    
