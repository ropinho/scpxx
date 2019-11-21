//
// Created by pinho on 21/11/2019.
//

#ifndef ORLIB_INSTANCEFILE_H
#define ORLIB_INSTANCEFILE_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class InstanceFile : protected std::ifstream {
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
    std::vector<int> split(std::string _str, char _sep) {
        using std::vector;
        using std::string;

        vector<string> strs;
        vector<int> ints;

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

        vecOfInts = split(buffer.str(), ' ');
        buffer.clear();
    }

    /*
     * Returns a reference to the vector of integers with all values
     */
    std::vector<int>& values() {
        return vecOfInts;
    }

protected:
    std::vector<int> vecOfInts;
};


#endif //ORLIB_INSTANCEFILE_H
