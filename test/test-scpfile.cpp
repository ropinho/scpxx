/**
MIT License

Copyright (c) 2019 Ronaldd Pinho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "doctest/doctest.h"
#include "../include/scpxx/SCPFile.h"

#include <vector>
#include <exception>

TEST_SUITE("SCP Files" * doctest::description("Testing files of Set Covering Problem instances")) {
    using std::vector;

    TEST_CASE("Instantiate SCPFile") {
        SUBCASE("Open file") {
            scpxx::SCPFile file("../instances/scp41.txt");
            CHECK_EQ(file.is_open(), true);
        }

        SUBCASE("Not Open file") {
            CHECK_THROWS_WITH(scpxx::SCPFile("scp41.txt"), "Impossible open the file scp41.txt");
        }

        SUBCASE("Catching Not Open Exception") {
            try {
                scpxx::SCPFile f("scp40.txt");
            } catch(std::exception& e) {
                std::string msg = e.what();
                CHECK(msg == "Impossible open the file scp40.txt");
            }
        }
    }

    TEST_CASE("Buffer values") {
        scpxx::SCPFile file("files/scp41.txt");
        file.bufferize();

        vector<int> vec = file.values();

        SUBCASE("Vector values") {
            CHECK_EQ(vec[0], 200);
            CHECK_EQ(vec[1], 1000);
            CHECK_EQ(vec.size(), 5211);
        }
    }
}
