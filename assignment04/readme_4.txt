Finds the steady state solution for the chemical reaction 2X + Y <=> 2Z using GSL.

Solves the equation in two ways, first using a multidimensional root finder in gsl,
second using the polynomial root finder for the chemical reaction's polynomial.

From the makefile, make runall should make and run both programs. Otherwise, make
just compiles both programs. On the teach cluster, before using make, use
module load gcc/13 gsl/2.7
