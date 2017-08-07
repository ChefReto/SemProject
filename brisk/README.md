# README #


### What is this repository for? ###

The folder brisk contains all relevant fucntions to compute Brisk/Surf/Sift deescriptors,  the computation of mean descriptors and vizualizations. I have everything coded in functions, once it is necessary it could be structured in a better way.


### Dependencies ###

OpenCV 2.4 or newer. OpenCV 3 is compatible, however not extensively tested
and the demo application is somewhat limited in functionality.

### How do I get set up? ###


1) Download brisk from Bitbucket
2) Extract in a directory of choice
3) Navigate to .../brisk

Build instructions:
```terminal
cd /path/to/brisk
mkdir build
cd build
cmake -CMAKE_BUILD_TYPE=Release ..
make -j8




4) Create a folder in …/brisk/build named Data
4.1) Create a folder in …/brisk/build named Data1
5) Create a folder in …/brisk/build named Vector
6) Create a folder in …/brisk/build named Viz
7) Create a folder in …/brisk/build named images
7.1) Create a folder in …/brisk/build named FilterImages/images/AMOS_Data/FD
7.2) Create a folder Grayimages
8) Copy Paste the folder AMOS_Day to images. In case you use another name, you need to change in main and in computinddescriptor.h
9) Create folders in …/brisk/build named Keypoints, Keypooints1
10) make
11) ./bin/demo

 
The main is either in ../brisk/src/demo-free.cc or in  ../brisk/src/demo.cc 
All my header files are in ../brisk/include/reto
The library header is in /brisk/include/brisk/library.h which includes all libraries that are needed



### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact
