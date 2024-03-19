// updatelife.h
// Steps the game of life forward.
#ifndef UPDATELIFE_H
#define UPDATELIFE_H

#include "initlife.h"

bool next_cell_state(const Cells& cell_state, int cell_index, int num_cells);

#endif
