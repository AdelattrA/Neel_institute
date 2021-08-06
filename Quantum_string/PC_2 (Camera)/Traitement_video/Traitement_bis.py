import cv2
import numpy as np
import matplotlib.cm as cm
from matplotlib import pyplot as plt
import matplotlib.animation as animation
import cv2
import glob


trash = []

#Affichage pontuel de l'image process

def show_wait_destroy(winname, img):
    cv2.imshow(winname, img)
    cv2.moveWindow(winname, 500, 0)
    cv2.waitKey(0)
    cv2.destroyWindow(winname)




def Traitement(path):
    #Création du background
    background = cv2.imread("C:/Users/Alexandre/Documents/Pro/UGA/M1/Neel/Stage/Etalon/background.tif")
    show_wait_destroy("res", background)



    if len(background.shape) != 2:
        b_g = cv2.cvtColor(background, cv2.COLOR_BGR2GRAY)
    else:
        b_g = background
    b_g = cv2.bitwise_not(b_g)

    ret,b_bw = cv2.threshold(b_g, 210, 255, cv2.THRESH_BINARY)

    b_bw = 255-b_bw    

    kernel = np.ones((5,5),np.uint8)
    b_bw = cv2.dilate(b_bw,kernel,iterations = 1)

    #Creation du résultat image par image
    images_bw = []
    images = [cv2.imread(file) for file in glob.glob("*.tif".format(path))]

    for image in images :
        if len(image.shape) != 2:
            gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        else:
            gray = image
        gray = cv2.bitwise_not(gray)
        ret,bw = cv2.threshold(gray, 210, 255, cv2.THRESH_BINARY)
        images_bw.append(bw-b_bw)    


    #Recherche des objets de l'image
    for res in images_bw :

        kernel = np.ones((2,2),np.uint8)
        res_b = cv2.erode (res, kernel, iterations = 1, borderType = cv2.BORDER_CONSTANT)
        #edges =  cv2.Canny(res, 50,200) 

        listY = []

        for e in res_b.T:           

            e=list(e)

            try:
                index = e.index(255)
            except :
                index= 999 #En l'absence de point expérimental, on renvoit une valeur hors champ (ATTENTION EN CAS DE CALCULS STAT')

            listY.append(index)

            listX = np.arange(0,len(listY))  

        print(type(listY))

        listY_mieux = listY.remove(999)

        print(listY_mieux)



Traitement("C:/Users/Alexandre/Documents/Pro/UGA/M1/Neel/Stage/Traitement_video/")





    




