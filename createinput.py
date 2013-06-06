# File: createinput.py
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that converts an image to an image file (formatted for imghelpers.cpp)

import sys
import Image
import helpers
import getopt

# This file produces a file (from an image) that can be 
# given to ReadImgFromFile (see imghelpers.cpp).
# Usage: python createinput.py -i image -o destination [-t threshold -g]
# The g flag converts the image to a binary image.  

dest = '';
imgName = '';
threshold = 128;
gray = False;
myopts, args = getopt.getopt(sys.argv[1:],"i:o:t:g");

for o, a in myopts:
    if o == '-g':
        gray = True;
    elif o == '-i':
        imgName = a;
    elif o == '-o':
        dest = a;
    elif o == '-t':
        threshold = int(a);
    else:
        print "Usage: python createinput.py -i image -o destination [-t threshold -g]";
        sys.exit(1);
if dest == '' or imgName == '':
    print "Usage: python createinput.py -i image -o destination [-t threshold -g]";
    sys.exit(1);

im = Image.open(imgName);
mat = im.convert("L").load();
a,b = im.size;

print "The image is {} x {} pixels".format(a,b);
if gray:
    helpers.WriteBinaryMatToFile(mat, a, b, dest, threshold);
else:
    helpers.WriteMatToFile(mat,a,b,dest);

print "Image successfuly converted and written to {}".format(dest);
