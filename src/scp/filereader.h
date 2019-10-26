#ifndef SCP_FILE_READER_HPP
#define SCP_FILE_READER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "matrix.hpp"

namespace ORLib {

    namespace scp {

        /**
        * Operator for read data files and build a matrix */
        class FileReader {
        public:

            // Constructor
            FileReader () {};
            ~FileReader() {};

            /** Gets a string and separe through a separator __sep and returns into a
             * std::vector<std::string> */
            std::vector<int> split(std::string _str, char _sep) {
                std::vector<std::string> strs;
                std::vector<int> ints;
            
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
                        ints.push_back( std::stoi(strs[i]) );
                    }
                }

                return ints;
            };


            /**
             * Lê o arquivo de dados e retorna um vector com todos os números ints
             * exceto a linha 1 que é armazenada nas variáveis nRows e nColumns */
            std::vector<int> read_file (std::ifstream& _file) {
                using std::string;
                using std::vector;

                if (!_file.is_open())
                    throw std::runtime_error("File not open");
            
                // Ler primeira linha
                string line;
                getline(_file, line);
                vector<int> vecInts = split(line, ' ');
                numRows = vecInts[0];
                numColumns = vecInts[1];

                // Ler custos das colunas
                while (getline(_file, line)) {
                    buffer << line;
                }

                // Vetor com todos os valores
                vecInts = split( buffer.str(), ' ');
                buffer.clear();
                return vecInts;
            }


            Matrix operator()(std::ifstream& _file) {
                using std::vector;
            
                if (!_file.is_open())
                    throw std::runtime_error("File not open");

                vector<int> vecInts = read_file(_file);
            
                // Adiciona os valores dos custos das colunas
                for (int i=0; i < numColumns; i++)
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
                return matrix;
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