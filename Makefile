# Makefile for using gsl to solve chemical reaction steady state.
#
# Part of assignment 4 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native -lgsl
OBJS=gsl_3d_root_find.o gsl_polynomial_root_find.o
LDLIBS=-lgsl -lgslcblas -lm
LDFLAGS=-L/usr/include/gsl

all: gsl_3d_root_find gsl_polynomial_root_find

gsl_polynomial_root_find.o: gsl_polynomial_root_find.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

gsl_polynomial_root_find: gsl_polynomial_root_find.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gsl_3d_root_find.o: gsl_3d_root_find.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

gsl_3d_root_find: gsl_3d_root_find.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

runall: gsl_polynomial_root_find gsl_3d_root_find
	./gsl_3d_root_find
	./gsl_polynomial_root_find

clean:
	$(RM) $(OBJS)

.PHONY.: all clean
