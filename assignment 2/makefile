# Makefile for the 'gameof1d' program
CXX=g++
CXXFLAGS=-std=c++17 -O3
LDFLAGS=-O3

all: gameof1d clean

gameof1d: gameof1d.o initcell.o
	$(CXX) $(LDFLAGS) -o gameof1d gameof1d.o initcell.o

gameof1d.o: gameof1d.cpp initcell.h
	$(CXX) -c $(CXXFLAGS) -o gameof1d.o gameof1d.cpp

initcell.o: initcell.cpp initcell.h
	$(CXX) -c $(CXXFLAGS) -o initcell.o initcell.cpp

clean:
	$(RM) gameof1d.o initcell.o
.PHONY.: all clean
