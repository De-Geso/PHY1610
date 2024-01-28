// initcell.h
#ifndef INITCELL_H
#define INITCELL_H

#include <iostream>
#include <memory>

void initcells(std::unique_ptr<bool[]>& cell, int const num_cells, double const target_alive_fraction);

#endif
