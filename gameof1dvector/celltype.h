// celltype.h
//
// Header only modules hat defines a type to hold the cell values and
// the constants alive and dead
//
// This code is part of assignment 3 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef CELLTYPEH
#define CELLTYPEH

// We use bool to store the state of each cell, but for convenience define the following

#include <vector>

const bool alive = true;
const bool dead = false;
using Cells = std::vector<bool>;

#endif
