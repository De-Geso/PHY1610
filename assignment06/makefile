# Makefile for inhomo_laplace
#
# Part of assignment 6 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=inhomo_laplace.o
LDLIBS=-llapacke -lnetcdf -lnetcdf_c++4
LDFLAGS=-L/usr/include/ -L/usr/bin

all: inhomo_laplace

run: all
	./inhomo_laplace

inhomo_laplace: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

inhomo_laplace.o: inhomo_laplace.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

.PHONY.: all clean
