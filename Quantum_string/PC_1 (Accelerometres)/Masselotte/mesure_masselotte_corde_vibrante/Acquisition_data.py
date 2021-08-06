# Module de lecture/ecriture du port série
from serial import *
import keyboard
import os
import json
import datetime 
from datetime import tzinfo, timedelta, datetime


# Ports séries 
# COM11 : Masse sup
# COM
# Vitesse de baud : 9600
# Timeout en lecture : 1 sec 

 
origin = datetime.now()
date = origin.strftime("%m_%d_%Y--%H_%M_%S")

prev = datetime.now() 

filename = "/Users/AL-nikon/Desktop/Masselotte/mesure_masselotte_corde_vibrante/data_{}.txt".format(date)

ports = dict(
    masse_supérieure="COM14",
    haut_parleur_droit="COM11"
    # haut_parleur_gauche="COM22"
)

data = dict()
serials = dict()

for key, port in ports.items():
    serials[key] = Serial(port=port, baudrate=9600, timeout=None)
    data[key] = list()
    #["t", "x", "y", "z"]


    print("Traitement en cours - Appuyer sur Echap pour quitter")
while not keyboard.is_pressed("escape"):
    for key, serialport in serials.items():
        if serialport.isOpen():
            ligne = serialport.readline()
            ligne = ligne.decode("utf-8")
            ligne = ligne.replace("\n", "").replace("\r", "")
            ligne = ligne.split(",")
            data[key].append(ligne)

fichier = open(filename, "w")
dumped = json.dumps(data, indent=2)
fichier.write(dumped)
fichier.close()
 






