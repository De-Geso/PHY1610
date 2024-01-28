// initcell.cpp
#include "initcell.h"

const bool alive = true;
const bool dead = false;
using Cells = std::unique_ptr<bool[]>;

std::unique_ptr<bool[]> initcells (int const num_cells, double const target_alive_fraction){
	// Simulation creation
	Cells cell(std::make_unique<bool[]>(num_cells));
	// Fill cells such that the fraction of alive cells is approximately target_alive_fraction.
	double fill = 0.0;
	for (int i = 0; i < num_cells; i++) {
		fill += target_alive_fraction;
		if (fill >= 1.0) {
			//cell[i] = alive;
			fill -= 1.0;
		} else
		cell[i] = dead;
	}
	return cell;
}
