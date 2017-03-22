import numpy as np
import matplotlib.pyplot as plt
import math
import wave     # for audio files
import re

# Bruker map og en lambda-funksjon for å kunne skrive en one-liner (som i MatLab!)
# audio = wave.open('blaze.wav', 'r')

#x = map(lambda x: math.sin(6.24*2*x/44100), list(range(2*44100)))
#rms = math.sqrt(

# Read and plot impulse response:
def plotfft(impulse_filename):
    irtxt = ""
    with open(impulse_filename, 'r') as irfile:
        irtxt = irfile.readlines()

    ir = [0]*len(irtxt)
    for n in range(len(irtxt)):
        ir[n] = float(re.sub('\n$', '', irtxt[n]))

    plt.plot(ir)

if __name__ == '__main__':
    plotfft('mob_fft.txt')
    plotfft('mic_fft.txt')
    plt.show()
