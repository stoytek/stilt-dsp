#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sigproc.h>

double* readIR(char* filename, int nCoeffs)
{
    FILE *ir_file = fopen(filename, "r");
    double* ir = (double*) malloc(nCoeffs*sizeof(double));
    char* line = NULL;       // Temp line
    size_t len = 0; 
    ssize_t read;
    if(ir_file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    for(int n = 0; n < nCoeffs; n++)
    {
        if((read = getline(&line, &len, ir_file)) == -1)
            ir[n] = 0.0;
        else 
            ir[n] = strtod(line, NULL);
    }

    free(line);
    fclose(ir_file);
    return ir;
}

double getdb(double* x, int N)
{
    /* This is the main sigproc function. 
     * Takes an audio signal (and length N),
     * filters it with the impulse from a .txt file
     * (not the fastest way of doing it, consider hard coding)
     * and returns a relative value */

    // First, filter the input signal
    int M = 40;     // Filter length
    double* h = readIR("impulse.txt", M);   // Filter Impulse Response
    double* y = conv(x, h, N, M);           
    // HER MÅ DET LESES!

    // Second, find and return the dB value
    double db = 0;
    for(int n = 0; n < N; n++)
    {
        db += x[n]*x[n];
    }
    db /= N;
    db = sqrt(db);
    db = 20*log10(db / 0.00002);

    free(y);
    return db;        
}



double* conv(double* x, double* h,int N, int M)
{
    // This function allocates memory! Be careful!
    // x = signal of length N (this is also the length of the output!)
    // h = filter of length M
    double* output = (double*) malloc(N*sizeof(double));
    for(int n = 0; n < N; n++)
    {
        output[n] = 0;
        for(int m = 0; m < M && m <= n; m++)
        {
           output[n] += h[m]*x[n - m];
        }
    }
    return output;
}

/*  DELETE THIS if not useful later 
double* zeroPad(double* signal, int* sig_length, int nZeros)
{
    int length = *sig_length + nZeros;
    *sig_length = length;

    signal = (double *) realloc(signal, (length)*sizeof(double));
    for(int i = length; i < length; i++)
    {
        signal[i] = 0.0;
    }
    return signal;
}
*/
