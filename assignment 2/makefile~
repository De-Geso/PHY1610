# Makefile for the 'gameof1d' program
CXX=g++
CXXFLAGS=-std=c++17 -O3
LDFLAGS=-O3

all: gameof1d clean

gameof1d: gameof1d.o initlife.o outputlife.o updatelife.o
	$(CXX) $(LDFLAGS) -o gameof1d.out gameof1d.o initlife.o outputlife.o updatelife.o

gameof1d.o: gameof1d.cpp initlife.h
	$(CXX) -c $(CXXFLAGS) -o gameof1d.o gameof1d.cpp

initlife.o: initlife.cpp initlife.h
	$(CXX) -c $(CXXFLAGS) -o initlife.o initlife.cpp
	
outputlife.o: outputlife.cpp outputlife.h initlife.h
	$(CXX) -c $(CXXFLAGS) -o outputlife.o outputlife.cpp

updatelife.o: updatelife.cpp updatelife.h initlife.h
	$(CXX) -c $(CXXFLAGS) -o updatelife.o updatelife.cpp


clean:
	$(RM) gameof1d.o initlife.o outputlife.o updatelife.o
.PHONY.: all clean
