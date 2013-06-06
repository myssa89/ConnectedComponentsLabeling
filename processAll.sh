# File: processAll.sh
# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Script that processes all images in img/ and outputs
#          the labeled images in results/.
# Usage: ./processAll.sh 

#!/bin/sh

for f in img/* 
do
  input=$f
  f=${f##*/}
  f=${f%.*}
  ./process.sh $input "results/$f"
done
