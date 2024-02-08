// testfillcells.cpp
#include "fillcells.h"
#include <fstream>

#include <catch2/catch_all.hpp>

TEST_CASE("fillcells test")
{
    int n = 5;

    // Test case where all cells are alive.    
    Cells all_alive(n);
    fill(all_alive.begin(), all_alive.end(), "alive");
    REQUIRE( initial_cells(n, 1.0) == all_alive );

    // Test case where all cells are dead.
    Cells all_dead(n);
    fill(all_dead.begin(), all_dead.end(), "dead");
    REQUIRE( initial_cells(n, 1.0) == all_dead );    
}
