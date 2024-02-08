// updatecells_test.cpp
#include "updatecells.h"

#include <catch2/catch_all.hpp>

TEST_CASE("updatecells test")
{
    // Lame all alive and all dead cases.
    Cells all_alive(3,true);
    Cells expected_alive(3,true);
    all_alive = update_all_cells(all_alive);
    REQUIRE( all_alive == expected_alive );

    Cells all_dead(3,false);
    Cells expected_dead(3,false);
    all_dead = update_all_cells(all_dead);
    REQUIRE( all_dead == expected_dead );

    // Send a glider. Every step, each alive cell slides one to the right.
    // For periodic boundary conditions, it should come around.
    Cells glider(10,false);
    glider[0]=true; glider[2]=true; glider[3]=true; glider[4]=true;
    Cells expected_glider(10);
    expected_glider = glider;
    // Fly the glider all the way around.
    for (int i=0; i<10; i++) {
        glider = update_all_cells(glider);
    }
    REQUIRE( glider == expected_glider );
}
