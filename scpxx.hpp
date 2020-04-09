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

#ifndef _SCPXX_SINGLE_HEADER_HPP_
#define _SCPXX_SINGLE_HEADER_HPP_

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

namespace scpxx {

/**
 * Exception for throw when not is possible open a file
 */
class FileNotOpenException : public std::runtime_error {
public:
    FileNotOpenException(const std::string filename)
    : std::runtime_error("Impossible open the file " + filename),
      name(filename) {}
protected:
    std::string name;
};


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


/**
 * Class that represents a instance file. Inherit from ifstream.
 * Gets a filename string and can read all values
 */
template <typename T>
class InstanceFile : public std::ifstream {
public:
    /*
     * Default Constructor
     * inherit from "input file stream"
     */
    explicit InstanceFile(std::string _filename) : std::ifstream(_filename) {}
    /*
     * Destructor
     */
    ~InstanceFile() {}
    /*
     * Gets a string with numbers and split through a separator _sep and
     * returns into a vector<int>
     */
    std::vector<T> split(std::string _str, char _sep) {
        using std::vector;
        using std::string;
        vector<string> strs;
        vector<T> values;
        int begin = 0;
        for (int i=0 ; i < _str.size() ; i++) {
            if (_str[i] == _sep) {
                strs.push_back( _str.substr(begin, i-begin) );
                begin = i+1;
            }
        }
        strs.push_back(_str.substr(begin, _str.size()));
        for (int i=0; i < strs.size(); i++) {
            if ((strs[i] != "") and (strs[i] != " ")) {
                values.push_back( std::stoi(strs[i]) );
            }
        }
        return values;
    };

    /*
     * Copy all integer numbers from instance file to a vector
     */
    void bufferize() {
        if (!this->is_open())
            throw std::runtime_error("File not open");
        std::stringstream buffer;
        std::string line;
        while (std::getline(*this, line)) {
            buffer << line;
        }
        vecOfvalues = split(buffer.str(), ' ');
        buffer.clear();
    }
    /*
     * Returns a reference to the vector of integers with all values
     */
    std::vector<T>& values() {
        return vecOfvalues;
    }
protected:
    std::vector<T> vecOfvalues;
}; // end of InstanceFile class


/**
 * Class for Set Covering Problem instance files from OR-Libary format
 * Gets a string filename of a file scp**.txt
 */
class SCPFile : public InstanceFile<int> {
public:
    /*
     * Default constructor
     */
    explicit SCPFile(std::string filename) : InstanceFile<int>(filename) {}
    /* Destructor */
    ~SCPFile() {}
    Matrix generate_matrix() {
        int nRows = this->vecOfvalues[0];
        int nColumns = this->vecOfvalues[1];
        std::vector<int> costs_vector;
        std::vector<int> columnsCover;
        int index = 2;
        for (; index < nColumns+2; index++)
            costs_vector.push_back(this->vecOfvalues[index]);
        index = nColumns+2;
        Matrix m(nRows, nColumns);
        int rowIndex = 0;
        while (rowIndex < nRows) {
            int endList = index + vecOfvalues[index];
            for (int i = index+1; i <= endList; i++) {
                columnsCover.push_back( vecOfvalues[i] );
                index = i;
            }
            //std::cout << rowIndex << std::endl;
            m.set_row(rowIndex, columnsCover);
            columnsCover.clear();
            rowIndex++;
            index++;
        }
        m.costs(costs_vector);
        costs_vector.clear();
        return m;
    }
};


} // end of namespace scpxx


#endif // _SCPXX_SINGLE_HEADER_HPP_