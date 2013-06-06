# File: createinput.py
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Source files containing the helpers functions used by createinput.py
#          and createimg.py. In particular 

import Image
import sys
import math
import colors

def RGBRange(number):
    return int(math.floor(255 * number));

def WriteMatToFile(mat, a, b, filename):
    file = open(filename, "w");
    file.write(str(a));
    file.write('\n');
    file.write(str(b));
    file.write('\n');
    for i in range(b):
        for j in range(a - 1):
            file.write(str(mat[j, i]));
            file.write(' ');
        file.write(str(mat[a - 1, i]));
        file.write('\n');

def ConvertToBinary(mat, a, b, threshold = 128):
    for i in range(b):
        for j in range(a):
            if mat[j, i] < threshold:
                mat[j, i] = 0;
            else:
                mat[j, i] = 1;
    return mat;
 
def WriteBinaryMatToFile(mat, a, b, filename, threshold = 128):
    ConvertToBinary(mat, a, b, threshold);
    WriteMatToFile(mat, a, b, filename);

def MatFromFile(filename):
    file = open(filename, "r");
    a = int(file.readline());
    b = int(file.readline());
    res = [];
    for i in range(b):
        line = file.readline();
        temp = [int(x) for x in line.split()];
        res.extend(temp);
    return res, a, b;

def TransformMatClassesToColors(mat):
    colorsSet = set();
    for i in range(len(mat)):
        colorsSet.add(mat[i]);
    numColors = len(colorsSet);
    sample = colors.GetColors(numColors); 
    corresp = {};
    curr = 0;
    for c in colorsSet:
        corresp[c] = sample[curr];
        curr += 1;
    newmat = [0] * len(mat);
    for i in range(len(mat)):
        newmat[i] = corresp[mat[i]];
    return newmat;

def ImgFromFile(filename, dest):
    mat, a, b = MatFromFile(filename);
    mat = TransformMatClassesToColors(mat);
    im = Image.new("RGB", (a, b));
    im.putdata(mat);
    im.save(dest);










