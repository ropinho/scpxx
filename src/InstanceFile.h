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

#ifndef ORLIB_INSTANCEFILE_H
#define ORLIB_INSTANCEFILE_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>


namespace scpxx {

    class InstanceFile : protected std::ifstream {
    public:
        using std::ifstream::is_open;
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

} // end of namespace scpxx


#endif //ORLIB_INSTANCEFILE_H
