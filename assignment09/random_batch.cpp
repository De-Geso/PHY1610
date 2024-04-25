// random_batch.cpp
 
#include "prng.h"
#include <iostream>
#include <rarray>
#include <mpi.h>
#include <string>
#include <math.h>


double randomDouble(int ndiscard=0) {
// Ripped directly out of prng_example.cpp
    int seed = 13;
    static PRNG gen(seed);
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    if (ndiscard==0) {
        return dis(gen);
    } else {
        gen.discard(ndiscard);
        return -1;
    } 
}


rvector<int> computeHistogram(const rvector<double>& data, double dx, int nBins) {
// Given a vector of data, make a histogram of bin width dx, and bin number nBins
	// Initialize bins
	rvector<int> histogram(nBins);
	histogram.fill(0);
	// Fill bins
	for (double point : data) {
		int index = static_cast<int>(point / dx);
		histogram[index]++;
	}
	
	return histogram;
}


int main(int argc, char** argv) {
	int rank, size;
	const int root = 0;
	MPI_Status rstatus;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	// Parameters
	const int N = 1E9;
	const int Z = 1E6;
	const double dx = 1./64;
	const int nBins = static_cast<int>(1.0 / dx);

	// Figure out how we're going to distribute the workload
	const long nxper = (N/Z+size-1)/size;
	const long nxstart = 2*(nxper*rank*Z+2);
	const int nxown = (rank<size-1)?nxper:(N/Z-nxper*(size-1));
	
	// Initialize accumulator histograms
	rvector<int> globalHist(size*nBins);
	rvector<int> mergedHist(nBins);
	mergedHist.fill(0);
		
	randomDouble(nxstart);
	// Z batches
	for (int j=0; j<Z; j++) {
		// Make random numbers
		rvector<double> localData(nxown);
		for (int i=0; i<nxown; i++) {
			localData[i] = randomDouble();
		}
		
		rvector<int> localHist = computeHistogram(localData, dx, nBins);

		globalHist.fill(0);
		MPI_Gather(localHist.data(), nBins, MPI_INT,
				globalHist.data(), nBins, MPI_INT,
				0, MPI_COMM_WORLD);
		//std::cout << localHist << " on " << rank << '\n';
		//std::cout << globalHist << " on " << rank << '\n';
		//std::cout << localData << " on " << rank << '\n';
		
		// Update the merged histogram. Loop through the big global histogram
		// and parse out which bins belong where.
		if (rank==0){
			for (int k=0; k<size; k++) {
				for (int l=0; l<nBins; l++) {
					mergedHist[l] += globalHist[k*nBins + l];
				}
			}
			//std::cout<< mergedHist << '\n';
		}
	}
	
	// Print the normalized histogram
	if (rank == 0) {
		std::cout << "Normalized histogram:\n";
		for (int bin : mergedHist) {
			std::cout << static_cast<double>(bin)/(N) << " ";
		}
		std::cout << '\n';
	}
	
	MPI_Finalize();
}
