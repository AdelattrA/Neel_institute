from serial import *
import keyboard
import os
import datetime 
from datetime import tzinfo, timedelta, datetime
import json
import numpy as np
from matplotlib import pyplot as plt
from scipy.fft import fft, fftfreq, fftshift

plt.style.use("seaborn-ticks")

# Vitesse de baud : 9600
# Timeout en lecture : 1 sec
 
origin = datetime.now()
date = origin.strftime("%m_%d_%Y--%H_%M_%S")

prev = datetime.now()

filename=input("Nom fichier: ")
filepath= "/Users/AL-nikon/Desktop/Masselotte/mesure_masselotte_corde_vibrante/{}.txt".format(filename)

fichier = open(filepath, "r")
data = json.loads(fichier.read())

data_final = dict()

list_t = []
list_x = []
list_y = []
list_z = []

# Extraction des données - Masse supérieuredata_07_15_2021--12_37_22
print("Traitement en cours")

for k, mat in data.items():
    data_final[k] = dict(
        x=[],
        y=[],
        z=[],
        t=[]
    )
    for line in mat:

        for s, i in zip(["t", "x", "y", "z"], range(0, 4)):
            try:
                v = float(line[i])
                if v == 999.0:
                    raise ValueError
                data_final[k][s].append(v)
            except IndexError:
                pass
            except ValueError:
                pass


list_colors = [
    "#3d1c02",
    "#889717"
]
list_marker = [
    ",",
    ","
]

list_line = [
    "dashdot",
    "dotted"
]

for k,v,c,m, l in zip(data_final.keys(), data_final.values(), list_colors, list_marker, list_line):
    t = np.array(v["t"])
    t_0 = t[0]
    t=(t-t_0)/10000 #Temps en s
    x = np.array(v["x"])
    y= np.array(v["y"])
    z= np.array(v["z"])

    ax1 = plt.subplot(3,1,1)
    plt.plot(t, x, color = c, marker = m, markersize = 5, linestyle = l, label="Acceleration x : {}".format(k))   
    plt.xlabel('Temps (ms)')
    plt.ylabel('Accélération (g)')
    plt.setp(ax1.get_xticklabels(), visible = False)
    plt.legend()

    ax2 = plt.subplot(3,1,2, sharex = ax1)
    plt.plot(t, y, color = c, marker = m,markersize = 5, linestyle = l, label="Acceleration y : {}".format(k))   
    plt.xlabel('Temps (ms)')
    plt.ylabel('Accélération (g)')
    plt.setp(ax2.get_xticklabels(), visible=False)
    plt.legend()

    ax3 = plt.subplot(3,1,3, sharex = ax2)
    plt.plot(t, z, color = c, marker = m,markersize = 5, linestyle = l, label="Acceleration z : {}".format(k))   
    plt.xlabel('Temps (ms)')
    plt.ylabel('Accélération (g)')
    plt.setp(ax3.get_xticklabels())
    plt.legend()

""" #Fourier Transform

sp = np.fft.fft(z)
freq = np.fft.fftfreq(len(t), 0.000005)
freq = freq/1000
plt.subplot(222)
plt.plot(freq,sp.real, freq, sp.imag)
plt.xlabel("Fréquence (Hz)")
plt.ylabel("Amplitude (ua)")
plt.legend()
 """

plt.show()


