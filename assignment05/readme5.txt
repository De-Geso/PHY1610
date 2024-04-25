Finds the solution of the Laplace equation for a particular set of boundary equations.
On a square, the outside edge is set to V=0, and a centered inner box with 1/10 the sidelength of the outer box is set to V=1.

Basic idea is to build the grid, then update each point on the grid by taking the mean of its 4 neighbours.
Do this iteratively, and you'll eventually have the solution to some precision we decide.

On teach, you'll have to module load gcc/13 and rarray.
From the makefile, make run should make and run the program with defaults set to n=500, epsilon=1e-6.

To help speed things up, I make a lazy initial guess that sets all nonboundary nodes to 0.5. This is legal because Laplace's equation
has a unique solution for Dirichlet boundary conditions.
When thinking about output, I had GNUplot in mind. Final solution is output as the whole matrix, with each number taking 16 width.
I also decided to just output the final solution, because I'm not sure when I'd care about intermediate bits. Especially because
I'm cheating initial steps by initializing the grid to some nonzero value.

To make a pretty picture, try
$ gnuplot
$ set size square
$ set view map
$ splot 'laplace_solution.dat' matrix with image

Note that the picture is upside down because (0,0) is top left for GNUplot, not bottom right. This can be fixed with
$ set yaxis [*:*] reverse.
