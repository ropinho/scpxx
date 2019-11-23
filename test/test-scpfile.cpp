//
// Created by pinho on 11/23/19.
//
// Test the SCP File class
//

#include "doctest/doctest.h"
#include "../src/SCPFile.h"

#include <vector>
#include <exception>

TEST_SUITE("SCP Files" * doctest::description("Testing files of Set Covering Problem instances")) {
    using std::vector;

    TEST_CASE("Instantiation") {
        SCPFile file("files/scp41.txt");
        CHECK_EQ(file.is_open(), true);

        DOCTEST_CHECK_THROWS_WITH(SCPFile("scp41.txt"), "SCPFile not opened.");
    }

    TEST_CASE("Buffer values") {
        SCPFile file("files/scp41.txt");
        file.bufferize();

        vector<int> vec = file.values();
        CHECK( vec[0] == 200 );
        CHECK( vec[1] == 1000 );
        CHECK( vec.size() == 5211 );
    }

}