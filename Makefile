# Makefile for laplace
#
# Part of assignment 5 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=laplace.o init_laplace.o iter_laplace.o output_laplace.o

all: laplace clean

# Run all tests and clean up.
# test: run_fillcells_test run_outputcells_test run_updatecells_test integrated_test clean


run: laplace
	./laplace

laplace: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

laplace.o: laplace.cpp init_laplace.h iter_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

init_laplace.o: init_laplace.cpp init_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

iter_laplace.o: iter_laplace.cpp iter_laplace.h init_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

output_laplace.o: output_laplace.cpp output_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

.PHONY.: all clean
