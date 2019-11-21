# ORLib [![build](https://travis-ci.org/pinho/orlib.svg?branch=master)](https://travis-ci.org/pinho/orlib)

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
#include <orlib/SCPFile.h>

int main() {
    SCPFile file("scp42.txt");

    // Read all number in file and copy to a vector
    file.bufferize();

    // Get the vector with all numbers
    std::vector<int> vec = file.values();

    std::cout << "Numero de valores: " << vec.size() << std::endl;

    for (int i = 0; i < vec.size(); i++)
	    std::cout << vec[i] << " ";
    std::cout << std::endl;

    return 0;
}
```

## License

[MIT](https://opensource.org/licenses/MIT)
