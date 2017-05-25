#!/usr/bin/python  
# Filename: test.py  
print("start c++_py:")
int_data=5;
def HelloWorld():  
    print ("Hello World!")   

def sayhi(name):  
    print ('hi',name); 
    return name
def add(a, b):  
    return a+b  

def AddMult(a,b):
    print("addmuilt in python")
    return (a+b,a*b)

def TestDict(dict):  
    print (dict)  
    dict["Age"] = 17  
    return dict 
class Person:  
    def sayHi(self,):  
        print ('hi')  
    def greet(self, greetStr):  
        print (greetStr)
    	return greetstr+"babby"  
#the chinese words cannot be present ,otherwise error occur
class Second:  
    def invoke(self,obj):  
        obj.sayHi()  
