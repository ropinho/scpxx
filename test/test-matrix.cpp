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
#include "../include/scpxx/Matrix.h"

TEST_SUITE("Matrix class") {

    TEST_CASE("Instantiate Matrix") {
        scpxx::Matrix m1, m2(9, 23), m3(0, 2), m4(12, 0);
        SUBCASE("Shape") {
            CHECK(m1.num_rows() == 0);
            CHECK(m1.num_columns() == 0);  // m1
            CHECK(m2.num_rows() == 9);
            CHECK(m2.num_columns() == 23); // m2
            CHECK(m3.num_rows() == 0);
            CHECK(m3.num_columns() == 2);  // m3
            CHECK(m4.num_rows() == 12);
            CHECK(m4.num_columns() == 0); // m4
        }
    }

}