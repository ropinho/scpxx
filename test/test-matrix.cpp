#ifndef TEST_MATRIX
#define TEST_MATRIX

#include "doctest/doctest.h"
#include "../src/scp/matrix.h"

#include <iostream>

TEST_CASE("Testing Matrix class") {
    using std::vector;

    using namespace ORLib;

    // Matriz 10x10
    scp::Matrix mat1(10, 10);

    SUBCASE("Length") {
        CHECK( mat1.num_rows() == 10 );
        CHECK( mat1.num_columns() == 10 );
        CHECK( mat1.costs() == vector<int>(10, 0) ); // vector com zeros
    }

    SUBCASE("Modifying") {
        vector<int> c = {1,2,1,3,3,3,8,5,1,2}; // 10 valores
        mat1.costs(c);
        CHECK( mat1.costs().size() == 10 );
        CHECK( mat1.costs()[0] == 1 );
        CHECK( mat1.costs()[3] == 3 );
        CHECK( mat1.costs()[6] == 8 );
        CHECK( mat1.costs()[9] == 2 );

        // modify a row
        mat1.set_row(0, {2, 3, 6, 9});
        CHECK( mat1[0] == vector<bool>({0,1,1,0,0,1,0,0,1,0}) );
    }

    SUBCASE("Density") {
        scp::Matrix mat2(5,5);
        CHECK( mat2.density() == 0.0f );

        mat2.set_row(0, {1,3});
        mat2.set_row(1, {3,4});
        mat2.set_row(2, {1,5});
        mat2.set_row(3, {2,3});
        mat2.set_row(4, {4,5});

        CHECK( mat2.density() == 0.4f );
    }

}

#endif