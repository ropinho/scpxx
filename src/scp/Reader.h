#ifndef ORLIB_SCP_READER_H
#define ORLIB_SCP_READER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "matrix.h"
#include "../FileReader.h"

namespace ORLib {

    namespace scp {

        /**
        * Operator for read data files and build a matrix */
        class SCPReader : public FileReader {
        public:
            using FileReader::split;

            // Constructor
            SCPReader () : FileReader(), buffer("") {};

            // Destructor
            ~SCPReader() {};


            virtual void operator()(std::ifstream& _file, Matrix& _mat) {
                using std::vector;
            
                if (!_file.is_open())
                    throw std::runtime_error("File not open");

                vector<int> vecInts = read_file(_file);
                int numRows = vecInts[0], numColumns = vecInts[1];
            
                // Adiciona os valores dos custos das colunas
                for (int i=2; i < numColumns+2; i++)
                    vecOfCosts.push_back( vecInts[i] );

                Matrix matrix(numRows, numColumns);

                // Ler os valores: Número de colunas e as colunas que cobre cada
                // linha
                vector<int> columnsCover;
                int idx = numColumns;
                int row_i = 0;

                while (idx < vecInts.size()) {
                    int endList = idx+vecInts[idx]; // último índice da lista de col
                    for (int i = idx+1; i <= endList; i++) {
                        columnsCover.push_back( vecInts[i] );
                        idx = i;
                    }
                    // Adiciona linha definida pelo vector na matriz
                    matrix.set_row(row_i, columnsCover);
                    columnsCover.clear();
                    row_i++;
                    idx++;
                }

                matrix.costs(vecOfCosts);
                vecOfCosts.clear();
                _mat = matrix;
            }

        private:
            std::stringstream buffer;
            std::vector<int> vecOfCosts;
            int numRows;
            int numColumns;
        };

    }

}

#endif
