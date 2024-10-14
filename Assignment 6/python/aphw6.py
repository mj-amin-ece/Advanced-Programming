
def code(filname,fun):
    new_byte=[]
    with open(filname,"rb") as image:
        f=image.read()         #read image
        byte = bytearray(f)     #get byte of image
    
    new_byte=map(fun,byte)    #maping
            
    with open(filname,"wb") as new_image:  #write new image
        for i in new_byte:
            new_image.write(bytes([i]))


class Factorial:
    def __init__(self):  #constructor
        self.dict={1:1}
        
    def __call__(self,number):    #operator()
        return self.calculate(number)   #claculate factorial
    
    def calculate(self,temp):  #claculate factorial
        for key,val in self.dict.items():  #if factorial has been computed
           if key==temp :
               return val
           
        # if factorial has not been computed ,compute it!
        if temp==1:
            return 1
        else: 
            result=self.calculate(temp-1)*temp
            self.dict.update({temp:result})
            return result