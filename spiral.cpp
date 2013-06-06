/* 
 * File: spiral.cpp
 * Author: Sammy EL GHAZZAL
 * Date: Started 06/03/2013
 * Purpose: 
 *		- Generates an input file for ccl containing a spiral.
 * Usage: ./spiral [size = 10] [outputFile = spiral.in]
 */

#include <vector>
#include <iostream>
#include <fstream> 
#include <iterator>
#include <sstream>
#include <string>
#include <cmath>
#include "imghelpers.h"

typedef unsigned int uint;

std::vector<uint> CreateSpiral1D(uint n) {
	if (n % 2 == 0) { 
		std::cout << "Warning: the size you provided was even, we rounded it up to the next odd integer (" << n + 1 << ")" <<  std::endl;
		++n;
	}
	uint k = n / 2;
	int numIter = (int)k + 1; 
	uint flip = 1;
	std::vector<uint> v(n * n);
	for (int it = 0; it < numIter; ++it) { 
		int len = (int)n - 2 * it;
		for (int i = it; i < it + len; ++i) {
			v[i * n + it] = flip;
			v[i * n + n - 1 - it] = flip;
			v[it* n + i] = flip;
			v[(n - 1 - it) * n + i] = flip;
		}
		v[(it + 1) * n + it] = 1 - flip;
		flip = 1 - flip;
	}
	return v;
}


int main(int argc, char** argv){
	int size = 10;
	std::string outfile = "spiral.in";
	if (argc > 1) { 
		size = atoi(argv[1]);
	}
	if (argc > 2) { 
		outfile = argv[2];
	}
	std::vector<uint> spiral = CreateSpiral1D(size);
	uint finalSize = (uint)sqrt(spiral.size());
	WriteImgToFile(outfile, spiral, finalSize, finalSize);
	return 0;
}
