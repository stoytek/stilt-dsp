#ifndef TESTSIGPROC_H
#define TESTSIGPROC_H

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "sigproc.h"

void printAbsFFT(double * fftvalues, int length)
{
    /* Call this to print comma separated values of an fft. 
     * Run this test program with ./test_sigproc > plot_values.txt
     * to write the values to a file that is plotted by test_pyplot.py
     */
    for(int i = 0; i < length-1; i++)
    {
        // Print absolute value of the result from FFT:
        double curabs = (fftvalues[i] < 0.0 ? -fftvalues[i] : fftvalues[i]); 
        printf("%f,", i, curabs);
        // printf("y[%d] = %f \n", i, y[i]);
    }
    printf("%f", (fftvalues[length-1] < 0.0 ? -fftvalues[length-1] : fftvalues[length-1]));
}

int main(int argc, char *argv[]) 
{
	/* ----------------------- Read audio file into array -----------------------
	SF_INFO soundInfo;	// Sound file info. 
	soundInfo.format = 0;
	SNDFILE* file;		// New SNDFILE object
	
	if((file = sf_open(argv[1], SFM_READ, &soundInfo)) == NULL)
	{
		printf("Error : Not able to open input file '%s'\n", argv[1]); sf_close(file);
		exit(1);
	}

	unsigned int length = (unsigned int) soundInfo.frames;
	double *audio = (double *) malloc(length*sizeof(double));		// Array that stores entire sound.
	
	sf_readf_double(file, audio, length);							// Read audio file into audio array.
	sf_close(file);											// Close audio file.
	
	// -----------------------------------------------------------------------------------------
    */
    long m = 16;
    int length = 44100;
    double * audio = (double *) malloc(length*sizeof(double));
    // Random seed:
    time_t t;
    srand((unsigned) time(&t));
    for(int n = 0; n < length; n++)
    {
        audio[n] = sin(1000*2*3.14*n/length) + sin(2000*2*3.14*n/length) + sin(3000*2*3.14*n/length) + sin(4000*2*3.14*n/length) + sin(5000*2*3.14*n/length) + sin(7000*2*3.14*n/length) + sin(8000*2*3.14*n/length) + sin(9000*2*3.14*n/length) + sin(10000*2*3.14*n/length) + sin(11000*2*3.14*n/length) + sin(12000*2*3.14*n/length) + sin(13000*2*3.14*n/length);
        audio[n] = (double)(rand() % 50) / 50.0;
    }

    // Zero padding because FFT is much faster for powers of two. 
    // We are using an FFT length of 2^16, so we need 2^16 - 44100 zeros:
    int zero_padding = 21436;
    audio = zeroPad(audio, &length, zero_padding);

    // Make an imaginary part = 0.
    // Alternative: Remove the imaginary part from the FFT implementation in 
    //              sigproc.c
    int ylen = 0;
    double* y = zeroPad(NULL, &ylen, 65536);

    FFT(1, m, audio, y);

    printAbsFFT(audio, length);
    
    free(audio);
    free(y);
	return 0;
}

#endif
