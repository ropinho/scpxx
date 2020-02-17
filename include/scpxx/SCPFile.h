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

#ifndef SCPXX_SCPFILE_H
#define SCPXX_SCPFILE_H

#include "InstanceFile.h"
#include "Matrix.h"
#include "Exception.h"

namespace scpxx {

    class SCPFile : public InstanceFile<int> {
    public:
        /*
         * Default constructor
         */
        explicit SCPFile(std::string filename) : InstanceFile(filename) {
            if (!this->is_open()) {
                throw FileNotOpenException(filename);
            }
        }

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

#endif //SCPXX_SCPFILE_H
