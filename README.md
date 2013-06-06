**Author:** Sammy El Ghazzal  
**Date of creation:** May 2013  
**Date of first commit:** June 2013  

Please report any bug or send feedback at myssa89 (at) gmail (dot) com.  
#### Purpose  

This repo contains the files that I created when being a Teaching Assistant for CME 213 "Introduction to parallel computing using MPI, openMP, and CUDA" at Stanford University. 

The goal of the project was to create a CUDA program that would perform the labeling on a GPU. The files of this repo were basically used to: 
* Check the correctness of the CUDA program.
* Have all scripts necessary to visualize the results and try their programs on various input images.

#### Overview

This repo is composed of the following parts: 
* A Python script createinput.py that converts an image to a file that can be read by the C++ program.
* A C++ program main.cpp that outputs a file containing the labels. Pixels in the same connected components are characterized by the fact that they share the same label. 
* A Python script createimg.py that takes as input the label file (created for instance by the C++ program) and outputs an image. Each color corresponds to a connected component.
* A C++ program spiral.cpp that can be used to generate arbitrarily large inputs. 
* Various shell scripts that can be used to create input files / run the connected components labeling program / create images from label files in batch mode.
* Some examples (see directory img/ for the inputs and results/ for the outputs).

#### Individual description of the files

Note that all files have comments at the top that explain what they contain and how they should be used. 

* img/: this folder contains sample images.
* results/: this folder contains the images produced by the algorithm.
* main.cpp: this file contains a serial implementation of the algorithm.
* directions.h: this file contains the inline functions used to find the indexes of the neighboring pixels.
* imghelpers.h and imghelpers.cpp: header and source files that contain the helper functions for image processing. This file can be used to read/write images (ReadImgFromFile and WriteImgToFile). To compare the output of another implementation (for instance a CUDA code) to the CPU solution, CompareSolution can be used; this function takes as arguments the names (include the correct path if the files are in a different directory) of the files to compare. 
* createinput.py: this Python script converts an image into a text file with the bits associated with each pixel (0 for black and 1 for white). The text file can then be easily read by the C++ code (using ReadImgFromFile). Please refer to the comments 
in the file for the usage of this script. We will give you images already converted to this text format. However you may want to use this script for other images, for testing purposes for example.
* createimg.py: this Python script transforms the text file with the labels into an image; this allows visualizing your results. It takes as input a file 
formatted in the same way as the output of WriteImgToFile. Please refer to the comments 
in the file for the usage of this script. The shell script that we are giving you, \verb|./processCuda.sh| will call this script for you.
* helpers.py: this file contains helper functions needed by the two other scripts. 
* colors.py: this file chooses appropriate colors in the RGB spectrum to be associated with each label in the output of the C++ program. This script is needed for the other scripts.
* generateInput.sh: create text files representing the images. Does this for all the images in the img/ directory. You need to have created a directory inputs/ (this will be the directory that contain all the input files that you can then feed to the C++ code). 
* generateOutput.sh: takes all the input text files in the directory inputs/ and produces the text files containing the labels in the directory outputs/ (that you need to create before running the script). 
* processAll.sh: automates the whole process, namely, create text file representing the image, runs the algorithm to produce label file, and create the result image from the label file. By default, it runs both versions of the algorithm (4 and 8-connectivity) but you can easily comment the part that you do not need. 
* processAll.sh: runs in batch mode the algorithm on all images (calls process.sh basically) contained in the img/ directory and outputs the images identifying the connected components in the results/ directory (again, you will need to create this directory before running the script). 
* spiral.cpp: this program can be used to generate a spiral image (this is a tricky case for the algorithm).

#### Remarks  
* Requires Python 2.7 or higher with the Image library set up. 
* If there are too many connected components, colors.py can go a bit crazy. 
* When using createinput.py, systematically use the -g flag
