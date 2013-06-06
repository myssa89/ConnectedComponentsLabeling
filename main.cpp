/* 
 * File: main.cpp
 * Author: Sammy EL GHAZZAL
 * Date: Started 05/07/2013
 * Purpose: 
 *      - Implements the Union-Find labeling algorithm in serial.
 *      - Contains a Union-Find datastructure to resolve equivalences between
 *      labels.
 * Usage: ./ccl inputImgFile outputImgFile [connectivity = 8]
 */

#include <algorithm>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "imghelpers.h"
#include <utility>
#include <map>
#include "directions.h"

const static uint OUT_COLOR = UINT_MAX - 1;

// helps model a tree like structure where the parent node is the 
// representative of an equivalence class 
struct node { 
    node *parent;
    uint label;
    node(uint label) { 
        this -> label = label;
        this -> parent = this;
    }   
};

// get the root node (the representative) associated to a node 
node *FindRep(node *n) { 
    while (n -> parent != n) { 
        n = n -> parent;
    }   
    return n;
}

void Union(node *x, node *y) { 
    node *xRep = FindRep(x);
    node *yRep = FindRep(y);
    yRep -> parent = xRep;
}

// create a link between two labels 
void Union(uint lab1, uint lab2, std::map<uint, node *>& labToNode) { 
    node *x = labToNode[lab1];
    node *y = labToNode[lab2];
    Union(x, y); 
}

// create new label (and add it to the map)
void AddLabel(uint& label, std::map<uint, node *>& labToNode) { 
    node *toAdd = new node(label);
    labToNode[label] = toAdd;
    ++label;
}

// Second pass of the Union-Find labeling algorithm. Resolves 
// the equivalences of labels. 
// Modifies res by reference to avoid allocating extra memory. 
void SecondPass(std::map<uint, node *>& labToNode, std::vector<uint>& res, uint xLen, uint yLen, uint maxLabel) { 
    // decide on the final labels
    std::map<uint, uint> equivClass;
    for (int i = 0; i < (int)maxLabel; ++i) { 
        equivClass[i] = FindRep(labToNode[i]) -> label;
    }
    // second pass
    for (int i = 0; i < (int)yLen; ++i) { 
        for (int j = 0; j < (int)xLen; ++j) { 
            res[i * xLen + j] = equivClass[res[i * xLen + j]];
        }
    }
}

// First pass of the Union-Find labeling algorithm. Attributes labels
// to zones in a forward manner (i.e. by looking only at a subset of the
// neighbors). 
template<uint connectivity> void FirstPass(const std::vector<uint>& img, std::vector<uint>& res, uint xLen, uint yLen, std::map<uint, node *>& labToNode, uint &currLabel) {
    uint left, up, leftup, rightup, curr, currPos, leftC, upC, leftupC, rightupC;
    for (int i = 0; i < (int)yLen; ++i) { 
        for (int j = 0; j < (int)xLen; ++j) { 
            if (i == 0 && j == 0) continue;
            currPos = i * xLen + j;
            curr = img[currPos];
            left = GetW(currPos, xLen);
            up = GetN(currPos, xLen);
            leftC = left == ERROR_CODE ? OUT_COLOR : img[left];
            upC = up == ERROR_CODE ? OUT_COLOR : img[up];
            std::vector<uint> match;
            if (leftC == curr) match.push_back(res[left]);
            if (upC == curr) match.push_back(res[up]);
            if (connectivity == 8) {
                leftup = GetNW(currPos, xLen);
                rightup = GetNE(currPos, xLen);
                leftupC = leftup == ERROR_CODE ? OUT_COLOR : img[leftup];
                rightupC = rightup == ERROR_CODE ? OUT_COLOR : img[rightup];
                if (leftupC == curr) match.push_back(res[leftup]);
                if (rightupC == curr) match.push_back(res[rightup]);
            }
            if (match.size() == 0) {
                res[currPos] = currLabel;
                AddLabel(currLabel, labToNode);
            }
            else {
                std::sort(match.begin(), match.end());
                uint ref = match[0];
                res[currPos] = ref;
                for (int i = 1; i < (int)match.size(); ++i) { 
                    if (match[i] != ref) { 
                        Union(ref, match[i], labToNode);
                    }
                }
            }
        }
    }
}

// The Union-Find labeling algoritm. Works in two passes and uses a Union-Find
// data strucure to resolve the equivalences between labels. 
void FindConnectedComponents(const std::vector<uint>& img, std::vector<uint>& res, uint xLen, uint yLen, uint connectivity) {
    uint currLabel = 0;
    std::map<uint, node *> labToNode;
    // first pass: assign labels to different zones
    res[0] = currLabel;
    AddLabel(currLabel, labToNode);
    if (connectivity == 4) {
        FirstPass<4>(img, res, xLen, yLen, labToNode, currLabel);
    }
    else if (connectivity == 8) {
        FirstPass<8>(img, res, xLen, yLen, labToNode, currLabel);
    }
    else {
        std::cout << "This is not a valid connectivity! Exiting ..." << std::endl;
        exit(1);
    }
    // second pass: merge classes if necessary
    SecondPass(labToNode, res, xLen, yLen, currLabel);
}

int main(int argc, char **argv) {
    std::string infile = "input";
    std::string outfile = "output";
    uint connectivity = 4;
    if (argc > 1) {
        infile = argv[1];
    }
    if (argc > 2) {
        outfile = argv[2];
    }
    if (argc > 3) { 
        connectivity = atoi(argv[3]);
    }
    uint xLen, yLen;
    std::vector<uint> vec = ReadImgFromFile(infile, xLen, yLen);
    std::vector<uint> res(vec.size());
    FindConnectedComponents(vec, res, xLen, yLen, connectivity);
    RelabelImg(res, xLen, yLen);
    WriteImgToFile(outfile, res, xLen, yLen); 
    return 0;
}

