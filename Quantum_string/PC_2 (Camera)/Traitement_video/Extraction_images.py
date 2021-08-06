import cv2
import os

#Extraction des images de la video
 
def extractFrames(pathIn, pathOut):
    if not os.path.exists(pathOut):
        os.mkdir(pathOut)
 
    cap = cv2.VideoCapture(pathIn)
    count = 0

    print("Traitement en cours ...")
 
    while (cap.isOpened()):
 
        ret, frame = cap.read()
 
        if ret == True:
            cv2.imwrite(os.path.join(pathOut, "frame_{:06d}.tif ".format(count)), frame)
            count += 1
        else:
            break
 
    cap.release()
    cv2.destroyAllWindows()


extractFrames('test.mp4', 'outputdir')
 
#Traitement des images
