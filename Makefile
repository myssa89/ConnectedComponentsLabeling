# Author: Sammy El Ghazzal
# Date: Started 05/07/2013
# Purpose: Makefile to compile the serial version of the 
#		   Connected Component Labeling algorithm. 

all: spiral ccl

spiral: spiral.cpp
	g++ -o spiral -g -ansi -pedantic -Wall -Wextra spiral.cpp imghelpers.cpp

ccl: main.cpp
	g++ -o ccl -g -ansi -pedantic -Wall -Wextra main.cpp imghelpers.cpp

clean:
	rm ccl spiral
	rm *.pyc
