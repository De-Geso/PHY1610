#include <complex>
#include <math.h>
#include <numeric>
#include <fstream>
#include <rarray>
#include <netcdf>
#include <fftw3.h>
using namespace netCDF;

rvector<std::complex<double>> get_data(std::string fname) {
	// Import observed data
	NcFile ncfile(fname, NcFile::read);
	rvector<std::complex<double>> obs(ncfile.getDim("nt").getSize());
	ncfile.getVar("f").getVar(obs.data());
	return (obs);
}

void fftw(rvector<std::complex<double>>& f, rvector<std::complex<double>>& fhat, bool inverse) {
// Perform forward fast Fourier transform
	const int n = f.size();
	const int sign = inverse*FFTW_BACKWARD+(1-inverse)*FFTW_FORWARD;
	fftw_plan p = fftw_plan_dft_1d(n,
			reinterpret_cast<fftw_complex*>(f.data()),
			reinterpret_cast<fftw_complex*>(fhat.data()),
			sign,
			FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
}

rvector<double> power_spectrum(rvector<std::complex<double>> f) {
// Get the power spectrum using FFTW
	const int nt = f.size();
	rvector<double> pow(nt);
	rvector<std::complex<double>> fhat(nt);
	
	// Do Fourier transform
	fftw(f, fhat, false);
	// Take modulus squared
	for (int i=0; i < nt; i++) {
		pow[i] = std::norm(fhat[i]);
	}
	return (pow);
}

rvector<int> sort_indices(rvector<double> vec) {
// Return a vector of indices for a given vector. The indices are sorted
// from largest to smallest.
	const int n = vec.size();
	rvector<int> ind(n);
	// Looking for biggest value less than the mask.
	// Correlation should be normalized to [-1, 1], so 10 is lots of padding.
	double mask = 10.0;
	
	// Some kind of bubble sort like thing. Could be faster by working
	// from both min and max side.
	for(int i=0; i < n; i++){
		double max = -10.;
		for(int j=0; j < n; j++){
			if(vec[j] > max && vec[j] < mask){
				max = vec[j];
				ind[i] = j;
		   }		   
		}
		mask = max;
	}
	return(ind);
}

int main(){
	// Path to folder with GW data.
//	const std::string fpath = "gwdata/";
    const std::string fpath = "/scinet/course/phy1610/gwdata/";
	// Number of data files.
	const int nf = 32;

	// Import the predicted signal and get nt. This one is hardcoded. It shouldn't change.
	NcFile ncfile(fpath+"GWprediction.nc", NcFile::read);
	rvector<std::complex<double>> prediction(ncfile.getDim("nt").getSize());
	ncfile.getVar("f").getVar(prediction.data());

	// All file lengths should be the same, so we'll also get nt here.
	int nt = ncfile.getDim("nt").getSize();
	
	// Get power spectrum of prediction
	rvector<double> pred_pow(nt), obs_pow(nt);
	pred_pow = power_spectrum(prediction);
	
	// Start looping over all our data files.
	rvector<std::complex<double>> observed;
	std::string fname;
	rvector<double> corr(nf);
	rvector<double> inner(3);
	
	// Initialize inner product vector
	inner.form({0., 0., 0.});
	// The predicted inner product doesn't change, so take out of loop.
	inner[2] = std::inner_product(pred_pow.begin(), pred_pow.end(), pred_pow.begin(), 0.);
	
	for (int file=1; file < nf+1; file++) {
		// Make the filename
		if (file < 10) {
			fname = "detection0"+std::to_string(file)+".nc";
		} else {
			fname = "detection"+std::to_string(file)+".nc";
		}
		
		// Get observation data and power spectrum
		observed = get_data(fpath+fname);
		obs_pow = power_spectrum(observed);
		
		// Make inner products for correlation.
		inner[0] = std::inner_product(obs_pow.begin(), obs_pow.end(), pred_pow.begin(), 0.);
		inner[1] = std::inner_product(obs_pow.begin(), obs_pow.end(), obs_pow.begin(), 0.);
		
		// Combine the inner products to make the correlation
		corr[file-1] = inner[0] / std::sqrt(inner[1] * inner[2]);
	}
	// Make the indices that we'll swap around, then sort them.
	rvector<int> ind(nf);
	ind = sort_indices(corr);
	
	// Output best candidates
	std::cout << "Best candidates are: " << '\n';
	std::cout << "File" << '\t' << "Correlation" << '\n';
	for (int i=0; i < 5; i++) {
		std::cout << ind[i]+1 << '\t' << corr[ind[i]] << '\n';
	}
	// Output all data for plotting purposes.
	std::ofstream outfile("data.txt");
	outfile.precision(16);
	for (int i=0; i < nf; i++) {
		outfile << i+1 << '\t' << corr[i] << '\t' << corr[ind[i]] << '\n';
	}
	outfile.close();
}
