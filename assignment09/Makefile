# Makefile for the laplace solver
#
# Note: plotting was not required for this assignment, nor was a
# separate 'boundary' module.

CXX = mpicxx
CXXFLAGS = -march=native -O2
LDFLAGS =
LDLIBS =

all: random_batch

run: random_batch
	mpirun -n 2 ./random_batch

random_batch: random_batch.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) *.o
