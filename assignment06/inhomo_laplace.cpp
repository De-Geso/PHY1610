#include <iostream>
#include <fstream>
#include <rarray>
#include <math.h>
#include <lapacke.h>
#include <netcdf>
using namespace netCDF;

// Parameters
// Number of points in grid.
const int N = 10000;
// Spacing of points in grid.
const double dx = 1./N;
// Boundary conditions
const double V0 = 0., VN = 1.;


double f (double x) {
	return 1. + 10.*cos(2.*M_PI*x);
}

void init (rarray<double,1>& dl, rarray<double,1>& d, rarray<double,1>& du,
		rarray<double,1>& x, rarray<double,1>& b) {
	// Initialize mesh, matrix, and solution vector.
	
	// Make the mesh of x positions
	for (int i = 0; i < N+1; i++) {
		x[i] = i*dx;
	}
	// Make the diagonal
	for (int i = 1; i < N; i++) {
		d[i-1] = -(f(x[i]+dx/2) + f(x[i]-dx/2));
	}
	// Make the off diagonals
	for (int i = 1; i < N-1; i++) {
		du[i-1] = f(x[i]+dx/2);
		dl[i-1] = f(x[i]-dx/2);
	}
	// Make b
	b = 0.;
	b[N-2] = -f(x[N-1]+dx/2) * VN;
}

rarray<double,1> solve (rarray<double,1> dl, rarray<double,1> d, rarray<double,1> du, rarray<double,1> b) {
	// Use Lapack to solve system.
	int info;
	// Copies for Lapack to eat
	rarray<double,1> Au = du.copy();
	rarray<double,1> A = d.copy();
	rarray<double,1> Al = dl.copy();

	// Use Lapack to solve
	info = LAPACKE_dgtsv(LAPACK_ROW_MAJOR, N-1, 1,
			Al.data(), A.data(), Au.data(), b.data(), 1);
//	std::cout << "INFO: " << info << "\n";
//	std::cout << "Solutions x:\n" << b << "\n";
	return (b);
}

void dump2file (rarray<double,1> x, rarray<double,1> v){
	// Dumps results to file using netcdf. Also dumps to file normally
	// so we have something readable to compare to. Don't do this when
	// we want speed.
	
	// Dump to a regular file so we can GNUplot it to check what we have
	std::ofstream df("data.txt");
	for (int i = 0; i < N-1; i++) {
		df << x[i+1] << '\t' << f(x[i+1]) << '\t' << v[i] << '\n';
	}
	df.close();
		
	// Output for real using netcdf
	// Create data array in memory
	int nx = N-1, ny = 3;
	rmatrix<double> dataOut(nx,ny);
	for (int i = 0; i < nx; i++) {
		dataOut[i][1] = x[i+1];
		dataOut[i][2] = f(x[i+1]);
		dataOut[i][3] = v[i];
	}
	// Create the netCDF file
	NcFile* dataFile = new NcFile("solution.nc", NcFile::replace);
	// Create the two dimensions
	NcDim xDim = dataFile->addDim("x", nx);
	NcDim yDim = dataFile->addDim("y", ny);
	
	NcVar data = dataFile->addVar("matrix", ncDouble, {xDim,yDim});
	// Put the data in the file
	data.putVar(&dataOut[0][0]);
	// Add an attribute
	dataFile->putAtt("Creation date:","15 Mar 2024");
	// Close the file
	delete dataFile;
}

int main() {
	rarray<double,1> v(N-1), dl(N-2), du(N-2), d(N-1), x(N+1), b(N-1);
	
	// Initialize matrix, x points, and b
	init(dl, d, du, x, b);
	// Use lapack to solve for V
	v = solve(dl, d, du, b);
	// Dump results to file
	dump2file(x, v);
}
