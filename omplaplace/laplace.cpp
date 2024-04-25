// laplace.cc
//
// reference solution of the laplace equation for assignment 5 of
// PHY1610, Winter 2024

#include <rarray>
#include "boundary.h"
#include "initialize.h"
#include "iteration.h"
#include "output.h"

// Driver function
int main(int argc, char** argv)
{
    // parameters
    const size_t maxsteps = (argc>1)?(std::stol(argv[1])):100000;
    const size_t n = (argc>2)?(std::stol(argv[2])):501;
    const double abstol = (argc>3)?(std::stod(argv[3])):1.0e-6;
    const double fraction = 0.1;
    // initialize
    rmatrix<double> V = init(n,n,fraction);
    rmatrix<double> Vprev(V.shape());
    // iterate
    size_t step = 0;
    for (step = 0; step < maxsteps; step++) {
        apply_average(V, Vprev);
        set_boundary_condition(V, fraction);
        const double maxdiff = get_max_diff(V, Vprev);
        if (maxdiff < abstol)
            break; // convergence
    }
    // done, now output
    ncoutput("laplace.nc", V);
    // check and report if the calculation converged:
    if (step < maxsteps) {
        std::cout << "#Converged in " << step << " steps\n";
        return 0;
    } else {
        std::cout << "#No convergence even after " << step << " steps\n";
        return 1;
    }
}
    
    
    
    
