# Makefile for gravitational_waves
# Part of assignment 7 for 2024 PHY1610

CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=gravitational_waves.o
LDLIBS=-lfftw3 -lnetcdf -lnetcdf_c++4
LDFLAGS=-L/usr/include/ -L/usr/bin

all: gravitational_waves

run: all
	./gravitational_waves

gravitational_waves: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gravitational_waves.o: gravitational_waves.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

.PHONY.: all clean
