# File: generateInput.sh
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that converts images in img/ to formatted
#          input files in inputs/
# Usage: ./generateInput.sh

#!/bin/sh

for f in img/* 
do
  input=$f
  f=${f##*/}
  f=${f%.*}
  ext=".in"
  python createinput.py -i $input -o "inputs/$f$ext" -g
done
