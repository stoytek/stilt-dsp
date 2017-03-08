#!/bin/bash
# Temporary script to build (replace with makefile)

clear
gcc -g test_sigproc.c ../csrc/sigproc.c -o test_sigproc -I ../cinclude -lsndfile -lm -pthread

read cont
if [ "$cont" == "" ]; then
    ./test_sigproc > plot_values.txt
    python ./test_pyplot.py
fi
# include libsndfile with	-lsndfile
# include math library with	-lm
# include pthread (but why?)
