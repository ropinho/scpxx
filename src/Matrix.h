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

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

class Matrix : protected std::vector< std::vector<bool> > {
public:
    using std::vector<std::vector<bool>>::operator[];
    using std::vector<std::vector<bool>>::iterator;
    using std::vector<std::vector<bool>>::begin;
    using std::vector<std::vector<bool>>::end;

    /*
     * Default Constructor
     * Gets the number of rows and number of columns
     */
    Matrix (unsigned int _nrows = 0, unsigned int _ncolumns = 0)
    : std::vector<std::vector<bool>>(_nrows, std::vector<bool>(_ncolumns,0)),
    numRows(_nrows), numColumns(_ncolumns), vecOfCosts(std::vector<int>(_ncolumns))
    {}

    /*
     * Destructor
     */
    ~Matrix() {}

    /*
     * Returns the number of rows of the Matrix */
    unsigned int num_rows() { return numRows; }

    /*
     * Returns the number of columns of the Matrix */
    unsigned int num_columns() { return numColumns; }

    /*
     * Set costs of all columns
     * Need a vector<int> with NCOL positions */
    void costs(std::vector<int> _costs) {
        if (_costs.size() != numColumns)
            throw std::logic_error("Number of costs should be equals to number of columns");
        vecOfCosts = _costs;
    }

    /*
     * Returns a reference to the vector of columns costs */
    const std::vector<int>& costs() {
        return vecOfCosts;
    }

    /*
     * Density of the set covering problem instance:
     * Number of Ones on the Matrix */
    float density() {
        iterator row = this->begin();
        int sum = 0;
        for (; row != this->end(); ++row) {
            sum = std::accumulate(row->begin(), row->end(), sum);
        }
        return (float) float(sum) / float(num_rows() * num_columns());
    }

    /*
     * Add a row in the matrix defining the columns that covers this row */
    void add_row(const std::vector<int> _columnsCovering) {
        if (_columnsCovering.size() > numColumns)
            throw std::length_error("Number of columns is very larger");

        std::vector<bool> aux_row(numColumns);
        std::vector<int>::const_iterator it = _columnsCovering.begin();

        for (; it != _columnsCovering.end(); ++it)
            aux_row[*it -1] = 1;

        push_back(aux_row);
    }

    /*
     * Defines the coverage of a existing row in the matrix passing the columns
     * that covers this row */
    void set_row(unsigned int _index, std::vector<int> _columnsCovering) {
        if (_columnsCovering.size() > numColumns)
            throw std::length_error("Number of columns is very larger");
        if (_index >= numColumns)
            throw std::length_error("Index out of bounds");

        std::vector<int>::iterator it = _columnsCovering.begin();

        for (; it != _columnsCovering.end(); ++it)
            at(_index)[*it -1] = 1;
    }

private:
    unsigned int numRows;
    unsigned int numColumns;
    std::vector<int> vecOfCosts;
};

#endif
