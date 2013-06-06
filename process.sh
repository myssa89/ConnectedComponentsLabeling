# File: process.sh
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that takes an image file, labels it, and 
#          outputs a labeled image with a name given byu the second 
#          argument.
# Usage: ./process.sh inputImage [outputImgName = result]

#!/bin/sh

python createinput.py -i $1 -o intermediate -g
if [ $# -lt 2 ]; then
  output="result"
else
  output="$2"
fi
temp=4
./ccl intermediate out4 4
python createimg.py -i out4 -o "$output$temp"
temp=8
./ccl intermediate out8 8 
python createimg.py -i out8 -o "$output$temp"
rm intermediate out4 out8
