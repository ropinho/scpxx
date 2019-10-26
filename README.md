# orlib
A simple C++ library for reading computer science problem instances made available in OR-Library.

## List of problems

Follwoing problems existing in [OR-Library]() that can be readed here are:

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
#include <orlib/scp/filereader.h>

using namespace ORLib;

int main() {
	scp::Matrix matrix(5,5);
	
	

	return 0;
}
```
