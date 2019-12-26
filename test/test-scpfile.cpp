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
        SUBCASE("Open file") {
            SCPFile file("files/scp41.txt");
            CHECK_EQ(file.is_open(), true);
        }

        SUBCASE("Not Open file") {
            DOCTEST_CHECK_THROWS_WITH(SCPFile("scp41.txt"), "SCPFile not opened.");
        }
    }

    TEST_CASE("Buffer values") {
        SCPFile file("files/scp41.txt");
        file.bufferize();

        vector<int> vec = file.values();

        SUBCASE("Vector values") {
            CHECK_EQ(vec[0], 200);
            CHECK_EQ(vec[1], 1000);
            CHECK_EQ(vec.size(), 5211);
        }
    }
}