pp6calculator - A simple command line calculator
================================================
This is the README file for the pp6calculator project.

Authors
=======
- Aaron Knight

License
=======
pp6calculator is distributed under the terms of the Boost Software License.

Updates
-------
- Day 4 Homework Solutions Added
- Day 4 Exercises Added
- Day 3 Homework Solutions Added
- Day 3 Exercises Added
- Day 2 Homework Solutions Added
- Day 2 Exercises Added
- Day 1 Homework Solutions Added
- Day 1 Exercises Added

Installation
============
- How to install the pp6calcualtor program

Prerequisites
-------------
- Unix operating system (Windows should work, but not tested)
- C++98/11 compiler ('g++'/'clang++' tested)
- [CMake](http://www.cmake.org) build tool, version 2.8 or higher

Building the pp6calculator
--------------------------
To build the pp6calcualtor please follow the following steps using CMake and UNIX Makefiles:

1. Create a build directory parallet to the director holding this README file,
e.g.

	$ ls
	pp6calculator.git
	$ mkdir pp6calculator.build

2. Change into the build directory and run 'cmake', pointing it to the source directory (i.e., the directory holding this README:

   	$ cd ppdcalculator.build
	$ cmake ../pp6calculator.git

3. Run 'make' using the Makefiles

        $ make

4. You can simply run 'pp6calculator' direct from the build directory

        $ ./pp6calculator