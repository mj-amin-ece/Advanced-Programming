# -*- coding: utf-8 -*-
"""
Created on Wed Jun  3 10:43:44 2020

@author: mjami
"""
import numpy as np
import cv2
from matplotlib import pyplot as plt
from zipfile import ZipFile
import os
from scipy.spatial import distance
from collections import Counter



def loadImage(filename):   #load image from adress
    img=cv2.imread(filename,0)
    face=cv2.resize(img,(30,30))    #resize to 30*30
    return face.reshape((900,1)),face
  
def loadFaces(filename):
    list_faces=[]     #list all faces
    zf=ZipFile(filename+'.zip','r')
    zf.extractall()    #extract zip file
    for root, dirs, files in os.walk(filename):
         for file in files:
             #append the file name to the list
             X=loadImage(os.path.join(root,file)) #load each image 
             list_faces.append(X[0]/np.max(X[0]))       #normalize each image
    array_faces=np.array(list_faces).reshape((400,900))
    return array_faces.transpose()  #

def findEigenFaces(cov,num_faces): 
    w,v=np.linalg.eig(cov)   #find eigenvectors and eigenvalue
    #ignore imaginary part
    v=np.real(v)
    w=np.real(w)
    
    #sort eigenvlaue
    idx=w.argsort()[::-1]   
    w=w[idx]
    v=v[:,idx]
    
    return v[:,:num_faces],w[:num_faces]
  
def showEigenFaces(efaces, size):
    rows=size[0]  #row
    columns=size[1]  #columns
    fig, axs = plt.subplots(rows, columns)  #plot
    count=0
    efaces=efaces[:,::-1] #reverse efacese
    
    for i in range(rows):
        for j in range(columns):   #draw figure
            img=efaces[:,count].reshape((30,30))
            axs[i][j].imshow(img,cmap='gray')
            axs[i,j].set_title(f'figure {count}',fontsize=10)
            axs[i,j].set_xticks([]),axs[i,j].set_yticks([])
            count+=1
    plt.tight_layout()   
    plt.savefig('FaceRecognition.png')  #save figure
   
def convertFace(X, eigenfaces):    #project faeces
    return np.matmul(np.transpose(eigenfaces), X)

def createDataset(filename,efaces):  #create dataset
    if os.path.isdir(filename) is False:
        zf=ZipFile(filename+'.zip','r')
        zf.extractall()   #extract zip file
        
    filelist = []  #list of file
    for root, dirs, files in os.walk(filename):
         for file in files:
             #append the file name to the list
             filelist.append(os.path.join(root,file))  #adress of image
    sub_file = os.listdir(filename)   #list of sub file(name each person)
    list_data=[]  #dataset
    num=int(len(filelist)/len(sub_file))  #number of image each person
    for i in range(len(sub_file)):
        for j in range(num):
            data=loadImage(filelist[i*num+j])  #load image
            list_data.append((convertFace(data[0]/np.max(data[0]), efaces),sub_file[i]))#add new data
    return list_data


def kNN(dataset, input_face_vec, eigenfaces, k) :
    
    in_face_project=convertFace(input_face_vec, eigenfaces) #project new face
    list_find=[]
    for i in dataset:  #claculate Euclidean distances
        d=distance.euclidean(i[0],in_face_project)
        list_find.append((d,i[1]))  #save distance and name 
    list_find.sort()   #sort distance
    list_find=list_find[:k]   
    
    count=Counter(elem[1] for elem in list_find)  #count each name
    name=count.most_common(1)[0][0]   #most repeated name
    return name,list_find







