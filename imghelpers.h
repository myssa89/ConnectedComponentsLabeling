/* 
 * File: imghelpers.h
 * Author: Sammy EL GHAZZAL
 * Date: Started 05/07/2013
 * Purpose: Interface for the helpers dealing with formatted files. Implements 
 *          relabeling, comparison, load / save of image files.
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <sstream>
#include <fstream>

typedef unsigned int uint;

void WriteImgToFile(const std::string& filename, std::vector<uint>& v, uint xLen, uint yLen);

std::vector<uint> ReadImgFromFile(const std::string& filename, uint& xLen, uint& yLen);

void RelabelImg(std::vector<uint>& v, uint xLen, uint yLen);

void CompareSolutions(const std::string& file1, const std::string& file2);
