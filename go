#!/bin/sh
g++ -std=c++0x -g -Wall $1.cpp && ./a.out < $1.in$2
