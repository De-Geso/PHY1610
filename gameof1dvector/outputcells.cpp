// outputcells.cpp
//
// see outputcells.h for documentation
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "outputcells.h"

void output_cells(std::ostream& out, int step, const Cells& cell)
{
    int num_cells = cell.size();
    const char on_char = 'I', off_char = '-';
    double alive_fraction = 0.0;
    for (int i = 0; i < num_cells; i++) 
        if (cell[i] == alive)
            alive_fraction++;
    alive_fraction /= num_cells;
    out << step << "\t";
    for (int i = 0; i < num_cells; i++)
        if (cell[i] == alive)
            out << on_char;
        else
            out << off_char;
    out << " " << alive_fraction << "\n";

}
