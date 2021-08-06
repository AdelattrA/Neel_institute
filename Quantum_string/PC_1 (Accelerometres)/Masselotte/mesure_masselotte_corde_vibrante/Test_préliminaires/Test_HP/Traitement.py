from serial import *
import keyboard
import os
import datetime 
from datetime import tzinfo, timedelta, datetime
import json
import numpy as np
from matplotlib import pyplot as plt


# Port série COM4
# Vitesse de baud : 9600
# Timeout en lecture : 1 sec

 
origin = datetime.now()
date = origin.strftime("%m_%d_%Y--%H_%M_%S")

prev = datetime.now()

filename = [
    "sans_corde_hp_gauche_roul_1",
    "sans_corde_hp_gauche_roul_2"
]
color = [
    "red",
    "blue",
]

filepath = []
for fn in filename:
    filepath.append("/Users/AL-nikon/Desktop/alex/mesure_masselotte_corde_vibrante/Test_HP/{}.txt".format(fn))

fichier = []
for fp in filepath:
    fichier.append(open(fp, "r"))

data = []
for fc in fichier :
    data.append(json.loads(fc.read()))

for dt, lab, c in zip(data, filename, color):
    list_t = []
    list_x = []
    list_y = []
    list_z = []

    for ligne, i in zip(dt, range(0, len(dt))):
 
        try:
            t = int(float(ligne[0]))
            x = float(ligne[1])
            y = float(ligne[2])
            z = float(ligne[3])
            list_t.append(t)
            list_x.append(x)
            list_y.append(y)
            list_z.append(z)
        except:
            print("pb ligne {}".format(i))
    
    list_t = np.array(list_t)
    t_0 = list_t[0]
    list_t = (list_t - t_0)/1000
    list_x = np.array(list_x)
    list_y = np.array(list_y)
    list_z = np.array(list_z)

    print("a_x = ", np.max(list_x), " +/- ", np.std(list_x), " g")
    print("a_y = ", np.max(list_y), " +/- ", np.std(list_y), " g")
    print("a_z = ", np.max(list_z), " +/- ", np.std(list_z), " g")



    #plt.plot(list_t,list_x, 'r',label='Acceleration selon x')
    #plt.plot(list_t,list_y, 'b', label='Acceleration selon y')
    plt.plot(list_t,list_z, 'g', label=lab,color = c)
    plt.xlabel('Temps (ms)')
    plt.ylabel('Accélération (g)')
    plt.legend()
    
plt.savefig("/Users/AL-nikon/Desktop/alex/mesure_masselotte_corde_vibrante/Test_HP/Comparaison_HP_3.png",dpi = 300)
plt.show()




     
 






