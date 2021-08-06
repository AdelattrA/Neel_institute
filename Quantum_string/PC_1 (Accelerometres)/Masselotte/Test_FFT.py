import numpy as np
from matplotlib import pyplot as plt
from scipy.fft import fft, fftfreq, fftshift

N = 400

T = 1.0 / (2*N)

w = 2*np.pi * 100

x = np.linspace(0,N*T,N,endpoint = False)
y = np.cos(w*x)

yf = fft(y)
xf = fftfreq(N,T)
xf = fftshift(xf)
yplot = fftshift(yf)

plt.plot(xf,1/N * np.abs(yplot))
plt.show()
