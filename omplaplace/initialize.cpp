#include "initialize.h"
#include "boundary.h"

rmatrix<double> init(size_t n, size_t m, double fraction) {
    rmatrix<double> V(n,m);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            V[i][j] = 0.0;
    set_boundary_condition(V, fraction);
    return V;
}

