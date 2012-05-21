#!/bin/sh
g++ -Wall -O2 $1.cpp -o $1 && ./$1 < $1.in$2
