//
// Created by pinho on 11/23/19.
//
// Test the SCP File class
//

#include "doctest/doctest.h"
#include "../src/SCPFile.h"

#include <vector>

TEST_SUITE("Files of Set Covering Problem") {
    using std::vector;

    TEST_CASE("Instantiation") {
        SCPFile file("files/scp41.txt");
        CHECK( file.is_open() == true );
    }

}