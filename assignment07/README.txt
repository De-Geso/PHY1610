Submission for assignment 7, Gravitational Waves.
Basic idea is to import the data file, get the power spectrum using FFTW, then compute the correlation coefficient.
Finally, sort through the correlation coefficients to find the 5 best candidates. Also output all the candidates so we can plot if we want.
Indexing works by leaving the correlations alone, but changing around a vector that holds the indices, in order.
When outputting, output the ith index + 1, to match files, which start counting at 1, not 0.
I hope the path is correct on Teach, it worked for me. If it doesn't work, there is a const variable "path" that can be changed to
specify the correct path to gwdata.

On Teach, should require the modules:
module load gcc/13.2.0 rarray/2.7.0 hdf5/1.10.9 netcdf/4.9.0 fftw/3.3.10

The order of loading may matter. Teach complained when I tried to load netcdf early.
