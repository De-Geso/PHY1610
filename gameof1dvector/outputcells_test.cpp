// outputcells_test.cpp
#include "outputcells.h"
#include <string>
#include <iostream>
#include <sstream>

#include<catch2/catch_all.hpp>

TEST_CASE("outputcells test")
{
    // Redirect std::cout to buffer
    std::stringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    
    // Do the code to be tested
    // Test all alive case
    Cells all_alive(5, true);
    output_cells(std::cout, 0, all_alive);
    
    // Use string value of buffer to compare
    std::string text = buffer.str();
    REQUIRE( text == "0\tIIIII 1\n" );

    // Reset buffer
    buffer.str(std::string());

    // All dead case
    Cells all_dead(2, false);
    output_cells(std::cout, 10, all_dead);
    text = buffer.str();
    REQUIRE( text == "10\t-- 0\n" );
    buffer.str(std::string());

    Cells cells1(1,true);
    output_cells(std::cout, 100, cells1);
    text = buffer.str();
    REQUIRE( text == "100\tI 1\n" );
    buffer.str(std::string());

    Cells cells2 = {false, false, true, true, true};
    output_cells(std::cout, 9, cells2);
    text = buffer.str();
    REQUIRE( text == "9\t--III 0.6\n" );
    buffer.str(std::string());

    Cells cells3 = {false, false, true};
    output_cells(std::cout, -1, cells3);
    text = buffer.str();
    // Careful here. I have the correct precision, but if the cout precision changes, this test will fail.
    REQUIRE( text == "-1\t--I 0.333333\n" );
    buffer.str(std::string());
}
