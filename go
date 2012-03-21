#!/bin/sh
g++ -O2 -Wno-unused-result -Wall $1.cpp -o $1 && ./$1 < $1.in
