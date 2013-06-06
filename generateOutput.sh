# File: generateOutput.sh
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that takes input files in inputs/ and 
#          runs the serial algorithm. Outputs files in outputs/.
# Usage: ./generateOutput.sh
#!/bin/sh

for f in inputs/* 
do
  input=$f
  f=${f##*/}
  f=${f%.*}
  ext=".out"
  ./ccl $input "outputs/$f$ext" 4
done
