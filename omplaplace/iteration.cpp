#include "iteration.h"
#include "boundary.h"

void apply_average(rmatrix<double>&V, rmatrix<double>&Vprev) {
    if (Vprev.extent(0)!=V.extent(0) || Vprev.extent(1)!=V.extent(1))
        Vprev = rmatrix<double>(V.shape());
    std::swap(V, Vprev);
    const size_t n = V.extent(0);
    const size_t m = V.extent(1);
    #pragma omp parallel for collapse(2) default(none) shared(n,m,V,Vprev)
    for (size_t i = 1; i < n-1; i++)
        for (size_t j = 1; j < m-1; j++)
            V[i][j] = 0.25*(Vprev[i-1][j] + Vprev[i+1][j]
                            + Vprev[i][j-1]  +Vprev[i][j+1]);
}

double get_max_diff(const rmatrix<double>& a, const rmatrix<double>& b) {
    double maxdiff = 0.0;
    const size_t n = std::min(a.extent(0), b.extent(0));
    const size_t m = std::min(a.extent(1), b.extent(1));
    #pragma omp parallel for collapse(2) default(none) shared(n,m,a,b) reduction(max:maxdiff)
    for (size_t i = 0; i < n; i++) 
        for (size_t j = 0; j < m; j++) 
            maxdiff = std::max(maxdiff, fabs(b[i][j] - a[i][j]));
    return maxdiff;
}
