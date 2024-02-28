# Makefile for laplace
#
# Part of assignment 5 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=laplace.o init_laplace.o

all: laplace clean

# Run all tests and clean up.
# test: run_fillcells_test run_outputcells_test run_updatecells_test integrated_test clean


run: laplace
	./laplace

originalgameof1d: originalgameof1d.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

laplace: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

laplace.o: laplace.cpp init_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

init_laplace.o: init_laplace.cpp init_laplace.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

gameof1d.o: gameof1d.cpp fillcells.h updatecells.h outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

fillcells.o: fillcells.cpp fillcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

updatecells.o: updatecells.cpp updatecells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

outputcells.o: outputcells.cpp outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

.PHONY.: all clean
