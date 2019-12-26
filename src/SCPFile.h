//
// Created by pinho on 21/11/2019.
//

#ifndef ORLIB_SCPFILE_H
#define ORLIB_SCPFILE_H

#include "InstanceFile.h"

class SCPFile : public InstanceFile {
public:
    /*
     * Default constructor
     */
    explicit SCPFile(std::string filename) : InstanceFile(filename) {
        if (!this->is_open()) {
            throw std::runtime_error("SCPFile not opened.");
        }
    }

    /* Destructor */
    ~SCPFile() {}

    Matrix generate_matrix() {
        int nRows = this->vecOfInts[0];
        int nColumns = this->vecOfInts[1];
        std::vector<int> costs_vector;
        std::vector<int> columnsCover;

        int index = 2;
        for (; index < nColumns+2; index++)
            costs_vector.push_back(this->vecOfInts[index]);
        index = nColumns+2;

        Matrix m(nRows, nColumns);
        int rowIndex = 0;
        while (rowIndex < nRows) {
            int endList = index + vecOfInts[index];
            for (int i = index+1; i <= endList; i++) {
                columnsCover.push_back( vecOfInts[i] );
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


#endif //ORLIB_SCPFILE_H
