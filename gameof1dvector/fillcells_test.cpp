// testfillcells.cpp
#include "fillcells.h"
#include <fstream>

#include <catch2/catch_all.hpp>

TEST_CASE("fillcells test")
{
    int n = 5;
    
    Cells all_alive(n);
    fill(all_alive.begin(), all_alive.end(), "alive");
    
    REQUIRE( initial_cells(n, 1.0) == all_alive );
}
