# Makefile for gameof1d
#
# Part of assignment 3 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=gameof1d.o fillcells.o updatecells.o outputcells.o

all: gameof1d originalgameof1d

integrated_test: originaltestoutput.txt testoutput.txt
	diff originaltestoutput.txt testoutput.txt

originaltestoutput.txt: originalgameof1d
	./originalgameof1d > originaltestoutput.txt

testoutput.txt: gameof1d
	./gameof1d > testoutput.txt

originalgameof1d: originalgameof1d.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gameof1d: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gameof1d.o: gameof1d.cpp fillcells.h updatecells.h outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

fillcells.o: fillcells.cpp fillcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

updatecells.o: updatecells.cpp updatecells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

outputcells.o: outputcells.cpp outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: gameof1d
	./gameof1d

clean:
	$(RM) $(OBJS)
