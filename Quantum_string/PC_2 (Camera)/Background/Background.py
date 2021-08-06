import cv2
import numpy as np
from matplotlib import pyplot as plt

#Affichage pontuel de l'image process

def show_wait_destroy(winname, img):
    cv2.imshow(winname, img)
    cv2.moveWindow(winname, 500, 0)
    cv2.waitKey(0)
    cv2.destroyWindow(winname)

# Ouverture de l'image

src = cv2.imread('Test_B.tif', cv2.IMREAD_COLOR)

# Image en niveaux de gris

if len(src.shape) != 2:
    gray = cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)
else:
    gray = src

#show_wait_destroy("gray", gray)

# Image en binaire
gray = cv2.bitwise_not(gray)
ret,bw = cv2.threshold(gray, 210, 255, cv2.THRESH_BINARY)

#cv2.imshow("Image", bw)
#cv2.waitKey(0)

#Suppression du fond

# Create structuring elements
h_size = [i for i in range(70,100)]

res=bw

for h in h_size :
    horizontalStructure_1 = cv2.getStructuringElement(cv2.MORPH_RECT, (h, 1))
    # Morphological opening
    mask1 = cv2.morphologyEx(bw, cv2.MORPH_OPEN, horizontalStructure_1)    
    #Traitement 
    res = res-mask1

for i in range(0,110):
    res[:,i] = 0

for i in range(255, 640):
    res[:,i] = 0

# Outputs
#cv2.imshow('mask1', mask1)
cv2.imshow('Resultat', res) #Res == Image de fond
cv2.imshow("Corde", mask1)
cv2.waitKey(0)
cv2.imwrite('Background.tif', res)
