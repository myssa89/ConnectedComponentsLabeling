/* 
 * File: imghelpers.cpp
 * Author: Sammy EL GHAZZAL
 * Date: Started 05/07/2013
 * Purpose: 
 *      - Load / Save functions between vectors and formatted files.
 *      - Relabeling of outputs.
 * 		- Comparison between output files.
 */

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sstream>
#include <map>
#include <fstream>
#include "imghelpers.h"

static std::vector<uint> StringToVector(const std::string& line) {
	std::stringstream buffer(line);
	std::vector<uint> res;
	uint temp;
	while (buffer >> temp) { 
		res.push_back(temp);
	}
	return res;
}

static uint StringToUint(const std::string& line) {
    std::stringstream buffer;
    uint res;
    buffer << line;
    buffer >> res;
    return res;
}

// Write v to the file filename. The user needs to provide the width and height of the image
// because v is assumed to be one dimensional.
void WriteImgToFile(const std::string& filename, std::vector<uint>& v, uint xLen, uint yLen) { 
	std::ofstream outfile(filename.c_str());
	if (!outfile.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		exit(1);
	}
	outfile << xLen << std::endl;
	outfile << yLen << std::endl;
	for (int i = 0; i < (int)yLen; ++i) { 
		for (int j = 0; j < (int)xLen - 1; ++j) { 
			outfile << v[i * xLen + j] << " ";
		}
		outfile << v[(i + 1) * xLen - 1] << std::endl;
	}
	outfile.close();
}

// Reads an image from the file named filename. Updates xLen (height) and yLen (width) by
// reference.
std::vector<uint> ReadImgFromFile(const std::string& filename, uint& xLen, uint& yLen) { 
	std::ifstream infile(filename.c_str());
	if (!infile) {
		std::cerr << "Failed to load the file." << std::endl;
		exit(1);
	}
	std::string line;
	std::vector<uint> temp;
	getline(infile, line);
	if (infile.fail()) {
		std::cout << "This is not a valid file" << std::endl;
		exit(1);
	}
	xLen = StringToUint(line);
 	getline(infile, line);
	if (infile.fail()) {
		std::cout << "This is not a valid file" << std::endl;
		exit(1);
	}
	yLen = StringToUint(line);
	std::vector<uint> res;
	while (true) {
		getline(infile, line);
		if (infile.fail()) break;
		temp = StringToVector(line);
		res.insert(res.end(), temp.begin(), temp.end());
	}
	return res;	
}

// Relabels v using a predefinite order (the one then used 
// for comparison). Will modify v by reference to avoid allowing 
// too much memory. 
void RelabelImg(std::vector<uint>& v, uint xLen, uint yLen) { 
	uint curr = 0;
	std::map<uint, uint> corresp;
	uint elem, newColor;
	for (int i = 0; i < (int)yLen; ++i) {
		for (int j = 0; j < (int)xLen; ++j) { 
			elem = v[i * xLen + j];
			if (corresp.find(elem) == corresp.end()) { 
				corresp[elem] = curr;
				newColor = curr;
				++curr;
			}
			else { 
				newColor = corresp[elem];
			}
			v[i * xLen + j] = newColor;
		}
	}
}

// Compares v1 and v2 element by element. Raises an assertion 
// if something is different. 
void CompareVectors(const std::vector<uint>& v1, const std::vector<uint>& v2) { 
	uint l1, l2;
	l1 = v1.size();
	l2 = v2.size();
	assert(l1 == l2);
	for (int i = 0; i < (int)l1; ++i) { 
		assert(v1[i] == v2[i]);
	}
}

// Compares the solution files in file1 and file2. Will operate the 
// relabeling before comparing the solutions. 
void CompareSolutions(const std::string& file1, const std::string& file2) { 
	uint xLen1, xLen2, yLen1, yLen2;
	std::vector<uint> v1, v2;
	v1 = ReadImgFromFile(file1, xLen1, yLen1);
	v2 = ReadImgFromFile(file2, xLen2, yLen2);
	assert(xLen1 == xLen2);
	assert(yLen1 == yLen2);
	RelabelImg(v1, xLen1, yLen1);
	RelabelImg(v2, xLen2, yLen2);
	WriteImgToFile("mod1", v1, xLen1, yLen1);
	WriteImgToFile("mod2", v2, xLen2, yLen2);
    CompareVectors(v1, v2);
	std::cout << "The two solutions match!" << std::endl;
}


