// testfillcells.cpp
#include "fillcells.h"
#include <fstream>

#include <catch2/catch_all.hpp>

TEST_CASE("fillcells test")
{
    // This n is general, and can be changed.
    const int n = 10;
    
    // These n's should not be changed unless the user also changes the expected output.
    const int n_odd = 5;
    const int n_even = 4;

    // Test case where all cells are alive.
    Cells all_alive(n);
    fill(all_alive.begin(), all_alive.end(), "alive");
    REQUIRE( initial_cells(n, 1.0) == all_alive );

    // Test case where all cells are dead.
    Cells all_dead(n);
    fill(all_dead.begin(), all_dead.end(), "dead");
    REQUIRE( initial_cells(n, 1.0) == all_dead );

    // Test case where half of cells are alive for an even number.
    Cells half_even(n_even);
//    half_even = { "true", "dead", "alive", "dead" };
    half_even = { false, true, false, true };
    REQUIRE( initial_cells(n_even, 0.5) == half_even );
    
}
