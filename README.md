# ORLib

[![build](https://travis-ci.org/pinho/orlib.svg?branch=master)](https://travis-ci.org/pinho/orlib)

A simple C++ library for reading computer science problems instances made
available in [OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html).


## Installing

The installation require CMake to generate build files of the library.

Clone this repository, in command line, access the project directory.
Create a folder to files generating by cmake.

```
$ mkdir build && cd build
```

Uses make to install locally the headers.
In build directory, types

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
- [ ] Knapsacking Problem
- [ ] Multidimensional Knapsack problem
- [ ] Travelling Salesman Problem (TSP)
- [ ] Steiner forest

## Usage example

Example using matrix class for set covering problem:

```c++
#include <iostream>
#include <orlib/scp/matrix.h>

using namespace ORLib;

int main() {
    scp::Matrix matrix(5,5);

    for (int i = 0; i < matrix.num_rows(); i++) {
        for (int j = 0; j < matrix.num_columns(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }

    return 0;
}
```

`[Out]`
```
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
0 0 0 0 0 
```

## License

Licensed under the [MIT](https://opensource.org/licenses/MIT) license.