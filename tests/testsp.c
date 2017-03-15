#ifndef TESTSIGPROC_H
#define TESTSIGPROC_H

#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>
#include <string.h>
#include <math.h>
#include "sigproc.h"

void writeaudio(char *filename, double *signal, sf_count_t length, int Fs)
{
    SNDFILE *outfile; // *file;
    SF_INFO info = { length, Fs, 1, SF_FORMAT_WAV | SF_FORMAT_PCM_16, 0, 0 };
    /* The format field in the above SF_INFO structure is made up of the bit-wise OR of a major format type (values between 0x10000 and 0x08000000), a minor format type
    *  (with values less than 0x10000) and an optional endian-ness value */
    if ((outfile = sf_open(filename, SFM_WRITE, &info)) == NULL)
    {
        printf("Error : Not able to open input file '%s'\n", filename);
        sf_close(outfile);
        exit(1);
    };
    sf_write_double(outfile, signal, length);
    sf_close(outfile);
}

double *readaudio(char *filename, SF_INFO *soundInfo)
{
    SNDFILE* file;  // New SNDFILE type
    if ((file = sf_open(filename, SFM_READ, soundInfo)) == NULL)
    {
        printf("Error : Not able to open input file '%s'\n", filename);
        sf_close(file);
        exit(1);
    }
    unsigned int length = (unsigned int) soundInfo->frames;
    double *signal = (double *) malloc(length*sizeof(double));    // We want to read all frames of the signal.
    sf_readf_double(file, signal, length);
    sf_close(file);
    return signal;
}

void normalize(double* x, int N)
{
    double max = 0.0;
    for(int n = 0; n < N; n++)
    {
        double abs_x = (x[n] < 0.0 ? -x[n] : x[n]); // Calculates absolute value
        printf("abs_x[%d] = %f", n, abs_x);
        if(abs_x > max)
            max = abs_x;
    }
    for(int n = 0; n < N; n++)
    {
        x[n] /= max;
    }
    printf("Max: %f\n", max);
}


int main(int argc, char *argv[]) 
{

    // Load a soundfile with sndfile:
    SF_INFO soundInfo;
    double* audio = readaudio(argv[1], &soundInfo); 
    int length = soundInfo.frames;
    int flength = 666;
    
    // Test the convolution:
    double* filter = readIR("impulse.txt", flength);
//    for(int n = 0; n < flength; n++)
//    {
//        printf("ir[%d] = %f\n", n, filter[n]);
//    }
    double* output = conv(audio, filter, length, flength);
//     Printing stuff:
//     for(int n = 0; n < length; n++)
//     {
//         printf("n[%d] = %f \n", n, output[n]);
//     }
    //normalize(output, length);
    writeaudio(argv[2], output, length, soundInfo.samplerate);

    //printf("dB SPL = %f\n", getdb(audio, length));
    //printf("dBA SPL = %f\n", getdb(output, length));
    
    // free(filter);
    free(audio);
    //free(output);
	return 0;
}

#endif
