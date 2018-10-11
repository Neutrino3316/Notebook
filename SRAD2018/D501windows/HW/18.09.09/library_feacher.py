import cv2
import numpy as np
import time

img1=cv2.imread('J:/data/history/pic1.jpg')
img2=cv2.imread('J:/data/history/pic2.jpg')
detect_list = []
detect_list.append(cv2.ORB_create())
detect_list.append(cv2.AKAZE_create())
detect_list.append(cv2.BRISK_create())

for i in range(len(detect_list)):
    time_start=time.time()
    # detect = cv2.AKAZE_create()
    detect = detect_list[i]
    kp1,des1 = detect.detectAndCompute(img1,None)
    kp2,des2 = detect.detectAndCompute(img2,None)
    bf = cv2.BFMatcher(cv2.NORM_HAMMING,crossCheck=True)
    matches = bf.match(des1,des2)
    matches = sorted(matches,key=lambda x:x.distance)
    img3 = cv2.drawMatches(img1,kp1,img2,kp2,matches[:23],img2,flags=2)
    time_end=time.time()
    print('totally cost',time_end-time_start)
    cv2.imwrite("J:/data/ruicheng"+str(i)+".jpg", img3)
