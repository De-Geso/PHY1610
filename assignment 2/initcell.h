// initcell.h
#include <iostream>
#include <memory>

std::unique_ptr<bool[]> initcells (int const num_cells, double const target_alive_fraction);
