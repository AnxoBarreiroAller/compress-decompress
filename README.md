# Compress-Decompress

This program compresses a input binary file and is also able to reconstruct the orioginal file bit a bit

## Getting Started

Just copy the current folder to a location of you choice. By the moment this program only runs on Linux

### Prerequisites

Please have updated GCC and CMAKE on your local machine


### Installing

Different options can be selected 

1) .bash file, there are two bash files on the root directory both Release and Debug just give permisions to them,
    (chmod +x *.bash on your terminal)  and execute them

2) also it can be compiled with cmke:
    mkdir build
    cd build
    cmake ..
    make

3) GCC
   copy paste the following
   gcc main.c decompress.c common.c compress.c -o compress-decompress

## Running

./compress-decompress -h will promtp the help info

HELP for Compress-Decompress program 
 
Program must be called as ./compress-decompress -OPTION -i PATH_TO_INPUT_FILE -o PATH_TO_INPUT_FILE 

	 -h / - help 		 Displays help/usage 
	 -compress 		 Calls compression algorithm 
	 -decompress 	 Calls decompression algorithm 
	 -accescompress  Calls Access compresed file algorithm 
	 -i 	 		 Path and name of the input file 
	 -testing 		 Number of tests to be performed at testing folder 


Please modify the path to the testing folderon the source code(not able to make it)


## Authors

* **Anxo Barreiro** - *anxo.barreiro@gmail.com* - 
