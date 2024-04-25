#include "output.h"
#include <netcdf>

// Print a matrix in a form that gnuplot can visualize, i.e., as x,y,z
// pairs.
//
// @param o An ostream to sent the output to.
// @param a The matrix to write.
//
void ncoutput(const std::string& filename, const rmatrix<double>& a) {
    using namespace netCDF;
    const size_t n = a.extent(0);
    const size_t m = a.extent(1);
    NcFile f(filename, NcFile::replace);
    NcDim ndim = f.addDim("n",n);
    NcDim mdim = f.addDim("m",m);
    NcVar var = f.addVar("a",ncDouble,{ndim,mdim});
    var.putVar(a.data());
    // for (size_t i = 0; i < n; i++) {
    //     for (size_t j = 0; j < m; j++) {
    //         const double x = 2*i/double(n-1) - 1.0;
    //         const double y = 2*j/double(m-1) - 1.0;
    //         o << x << '\t' << y << '\t' << a[i][j] << '\n';
    //     }
    //     o << "\n";
    // }
}

