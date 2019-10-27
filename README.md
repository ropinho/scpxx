# ORLib

![build](https://travis-ci.org/pinho/orlib.svg?branch=master)

A simple C++ library for reading computer science problem instances made
available in [OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html).


## Installing

The installation uses CMake to build the library.

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

The files are placed in `/usr/local/include/orlib`.


## List of problems

Follwoing problems existing in
[OR-Library](http://people.brunel.ac.uk/~mastjjb/jeb/info.html)
that can be readed here are:

- [X] Set covering problem (SCP)
- [ ] Multidimensional Knapsack problem
- [ ] Knapsacking Problem
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

[LICENSE](https://opensource.org/licenses/MIT)