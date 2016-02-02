#!/bin/bash

NAME=askonegetonefree

/usr/bin/g++ -DEVAL -Wall -static -O2 -o $game bob.cpp $NAME.cpp
