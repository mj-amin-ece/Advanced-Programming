# -*- coding: utf-8 -*-
"""
Created on Wed Jun 10 22:34:06 2020

@author: mjami
"""

from numpy import random
def generateArray():
    x=random.randint(100,999, size=(100))  #generate 100 random number
    x[8::9]=x[8]
    return x.reshape((10,10))
    
    

# d=generateArray()

# fig = plt.figure(dpi=80)
# ax = fig.add_subplot(1,1,1)
# temp=
# temp=d[0,:].tolist()
# table_data=[d[0,:].tolist(),d[1,:].tolist(),d[2,:].tolist(),d[3,:].tolist(),d[4,:].tolist()
#             ,d[5,:].tolist(),d[6,:].tolist(),d[7,:].tolist(),d[8,:].tolist(),d[9,:].tolist()]

# table = ax.table(cellText=table_data, loc='center')
# table.set_fontsize(14)
# table.scale(1,4)
# ax.axis('off')
# plt.show()
