#!/bin/bash

g++ -DEVAL -static -O2 -std=c++11 -o sorting grader.cpp sorting.cpp
