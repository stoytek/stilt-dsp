#ifndef TESTSIGPROC_H
#define TESTSIGPROC_H

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <string.h>
#include <math.h>
#include "sigproc.h"

int main(int argc, char *argv[]) 
{
	/* ----------------------- Read audio file into array -----------------------
	SF_INFO soundInfo;	// Sound file info. 
	soundInfo.format = 0;
	SNDFILE* file;		// New SNDFILE object
	
	if((file = sf_open(argv[1], SFM_READ, &soundInfo)) == NULL)
	{
		printf("Error : Not able to open input file '%s'\n", argv[1]);
		sf_close(file);
		exit(1);
	}

	unsigned int length = (unsigned int) soundInfo.frames;
	double *audio = (double *) malloc(length*sizeof(double));		// Array that stores entire sound.
	
	sf_readf_double(file, audio, length);							// Read audio file into audio array.
	sf_close(file);											// Close audio file.
	
	// -----------------------------------------------------------------------------------------
    */
    int length = 44100;
    double * audio = (double *) malloc(length*sizeof(double));
    for(int n = 0; n < length; n++)
    {
        audio[n] = sin(2*3.14*3*n/length);
    }

    // Zero padding because FFT is much faster for powers of two. 
    // If using an FFT length of 2^16, then we need 2^16 - 44100 zeros:
    int zero_padding = 21436;
    zeroPad(audio, length, zero_padding);
    length += zero_padding;
	
    for(int i = 0; i < length; i++)
    {
    //    printf("audio[%d] = %f \n", i, audio[i]);
    }

	free(audio);
	return 0;
}

#endif
