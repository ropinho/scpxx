#ifndef ORLIB_FILEREADER_H
#define ORLIB_FILEREADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace ORLib {

    class FileReader {
    public:

        // Constructor
        FileReader() : buffer("") {}


        // Destructor
        ~FileReader() {}


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
         * Lê o arquivo de dados e retorna um vector com todos os números ints */
        std::vector<int> operator()(std::ifstream& _file) {
            using std::string;
            using std::vector;

            string auxRow;
            vector<int> vecInts;

            if (!_file.is_open())
                throw std::runtime_error("Error in open the file");

            // Begin the reading
            while (getline(_file, auxRow)) {
                buffer << auxRow;
            }

            // Vetor com todos os valores
            vecInts = split(buffer.str(), ' ');
            buffer.clear();
            return vecInts;
        }

    protected:
        std::stringstream buffer;
    
    };

}

#endif