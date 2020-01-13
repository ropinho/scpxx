# SCPxx

[![build](https://travis-ci.org/pinho/orlib.svg?branch=master)](https://travis-ci.org/pinho/orlib) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a39d4717f47c480482a1edfb93f39a05)](https://www.codacy.com/manual/ronaldpnh/orlib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pinho/orlib&amp;utm_campaign=Badge_Grade)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) 

A simple C++ library for reading Set Covering Problem (SCP) instances made
available in [OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html).


## Installation
The installation require CMake to generate build files of the library.

Clone this repository, in command line, access the project directory.
Create a folder to files generating by cmake.

```
$ mkdir build && cd build
```

Uses make to install locally the headers.
In build directory, type

```
$ cmake ..
$ sudo make install
```

By default, the files are placed in `/usr/local/include/orlib`.


## List of problems

Following problems existing in
[OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html)
that can be readed here are:

- [X] Set covering problem (SCP)

## Usage

Example using matrix class for set covering problem:

```cpp
#include <iostream>
#include <orlib/scp.h>

int main() {
    SCPFile file("../scp41.txt");

    // Read all numbers in file and copy to a vector
    file.bufferize();

    // Get the vector with all numbers
    std::vector<int> vec = file.values();
    std::cout << "Number of values: " << vec.size() << std::endl;
    
    // The method generate_matrix build the matrix object
    auto matrix = file.generate_matrix();

    std::cout << matrix.num_rows() << " rows\n";
    std::cout << matrix.num_columns() << " columns\n";
    return 0;
}

```

## License

Licensed under the [MIT](https://opensource.org/licenses/MIT) license.
