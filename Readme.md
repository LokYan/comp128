# COMP128 Exercise

COMP128 is a well known cryptographic algorithm that implemented the A3 (Authentication) and A8 (Key Agreement) functions of the GSM standard. Like other contemporary algorithms, COMP128 was proprietary and buggy. We studied the "narrow pipe" issue by Wagner, Goldberg, and Briceno (http://www.isaac.cs.berkeley.edu/isaac/gsm-faq.html) in our mobile security course and this is an opportunity to test out the bug. 

The researchers also released a recovered (some internal documentation was leaked to the public) and reverse engineered a version of the A3A8 algorithm written in C. This repository is that source, but in a form that is suitable as an assignment/lab/exercise. 

## Source Layout

The original source code is found in comp128\_orig.c and the same source (plus a couple of helper functions) was separated into a shared-library (libcomp128.c) as well as a main function (main.c) that can be used to perform a brute-force search to find collisions. We also created a sample bash script (run.sh) that can be used to run a brute force attempt. Finally, a python version of comp128 is also provided (comp128.py) for students who would rather play with Python (although it is much slower).

## Idea Behind the Assignment

For the assignment, students are provided with a libcomp128.a (see Makefile) that was precompiled with a secret key. Students are then asked to make changes to the source to 1. find collisions at each of the 8 byte position pairs and 2. use the colliding inputs (challenges) to find the corresponding key bytes. 

## Sample Run of repository

	lok@lok:~/Desktop/comp128$ ls 
	comp128.h  comp128.py  libcomp128.c  main.c  Makefile  Readme.md  run.sh
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ make lib
	gcc -I. -L. -c libcomp128.c -o libcomp128.o
	ar rcs libcomp128.a libcomp128.o
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ make
	gcc -I. -L. -c main.c -o main.o
	gcc -I. -L. main.o -lcomp128 -o main 
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ python3 comp128.py 
	Output from original program
	A3A8(1D000000000000009900000000000000,048BC1EA93B0F82733D67C19267C91D6) = 80B3A76AD121F66903D0F800
	
	A3A8(3E00000000000000C100000000000000,048BC1EA93B0F82733D67C19267C91D6) = 80B3A76AD121F66903D0F800
	
	Output from this script
	A3A8(1D000000000000009900000000000000,048BC1EA93B0F82733D67C19267C91D6) = 80B3A76AD121F66903D0F800
	A3A8(3E00000000000000C100000000000000,048BC1EA93B0F82733D67C19267C91D6) = 80B3A76AD121F66903D0F800
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ ./main 0x3E00000000000000C100000000000000 0 0x1D
	3E00000000000000C100000000000000
	80B3A76AD121F66903D0F800
	1D000000000000009900000000000000
	80B3A76AD121F66903D0F800
	
## Other Modes of Operation

This COMP128 program has three modes of operation in total: the brute force mode as shown above, the base mode where you can pass in both the random challenge and the key to use, and then there is the rand-only mode where you pass in the random challenge and the built-in key (the one that is being brute-forced is used). The brute force mode is useful for finding collisions, the base mode is good for finding the key and the rand-only mode is good for verifying that you have the right key.

### Sample Run of other modes

	lok@lok:~/Desktop/comp128$ ./main 0x12341234123412341234123412341234
	9CD2E0434EE92690CE71D800
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ ./main 0x12341234123412341234123412341234 0x048bc1ea93b0f82733d67c19267c91d6
	9CD2E0434EE92690CE71D800
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ ./main 0x00001234123412341234123412340000
	136A205ED174EE8175944400
	lok@lok:~/Desktop/comp128$
	lok@lok:~/Desktop/comp128$ ./main 0x00001234123412341234123412340000 0x048bc1ea93b0f82733d67c19267c91d6
	136A205ED174EE8175944400

# LICENSE

Copyright 2021 Lok Yan

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
