// initcell.h
// Holds initializations and global constants.
#ifndef INITLIFE_H
#define INITLIFE_H

#include <iostream>
#include <memory>

const bool alive = true;
const bool dead = false;
using Cells = std::unique_ptr<bool[]>;

void initcells(Cells& cell, int const num_cells, double const target_alive_fraction);

#endif
