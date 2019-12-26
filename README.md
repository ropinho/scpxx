[![build](https://travis-ci.org/pinho/orlib.svg?branch=master)](https://travis-ci.org/pinho/orlib) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/a39d4717f47c480482a1edfb93f39a05)](https://www.codacy.com/manual/ronaldpnh/orlib?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pinho/orlib&amp;utm_campaign=Badge_Grade) 

# ORLib 
A simple C++ library for reading computer science problems instances made
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
- [ ] Knapsacking Problem
- [ ] Multidimensional Knapsack problem
- [ ] Travelling Salesman Problem (TSP)
- [ ] Steiner forest

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

    std::cout << "Numero de valores: " << vec.size() << std::endl;

    auto matrix = file.generate_matrix();
    std::cout << matrix.num_rows() << " linhas e "
              << matrix.num_columns() << " colunas.\n";

	// Show some rows and columns from matrix
	for (int r=0; r < 8; r++) {
		for (int k=0; k < 10; k++)
			std::cout << matrix[r][k] << " ";
		std::cout << ". . ." << std::endl;
	}
	std::cout << ". . . . . . . . . . " << std::endl;

    return 0;
}

```

## License

Licensed under the [MIT](https://opensource.org/licenses/MIT) license.