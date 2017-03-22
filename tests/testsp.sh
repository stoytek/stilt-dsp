#!/bin/bash
# Temporary script to build (replace with makefile)

clear
gcc -g testsp.c ../sigproc.c ../impulse.c -o testsp -I ../ -lsndfile -lm -pthread
