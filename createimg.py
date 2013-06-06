# File: createimg.py
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that converts a formatted label file to an actual image. 

import sys
import Image
import helpers
import getopt

# This file produces a jpg image from a file representing the
# image (see imghelpers.cpp). 
# Usage: python createimg.py -i source -o outputimg

dest = '';
filename = '';
gray = False;
myopts, args = getopt.getopt(sys.argv[1:],"i:o:");

for o, a in myopts:
    if o == '-i':
        filename = a;
    elif o == '-o':
        dest = a;
    else:
        print "Usage: python createimg.py -i source -o outputimg";
        sys.exit(1);
if dest == '' or filename == '':
    print "Usage: python createimg.py -i source -o outputimg";
    sys.exit(1);

if dest[-4:] != ".png": 
    dest += ".png";

helpers.ImgFromFile(filename, dest);

print "Image has been written to file {}".format(dest);
