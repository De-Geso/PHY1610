# Makefile for the 'gameof1d' program
cxx=g++
cxxflags=-std=c++17 -O3
ldflags=-O3
all: gameof1d

gameof1d: gameof1d.o initcell.o
	$(cxx) $(ldflags) -o gameof1d gameof1d.o initcell.o $(LDLIBS)

gameof1d.o: gameof1d.cpp initcell.h
	$(cxx) -c $(cxxflags) -o gameof1d.o gameof1d.cpp

initcell.o: initcell.cpp initcell.h
	$(cxx) -c $(cxxflags) -o initcell.o initcell.cpp
