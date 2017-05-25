#!/usr/bin/env python
# coding=utf-8
import numpy as np
import string
a1 = np.array([1, 2, 34])
b1= np.matrix(a1)
print("strat using python in c++")
print b1



#print(test_add(3,4))
class Student:
    def SetName(self,name):
        self._name = name
    def PrintName(self):
        print self._name
def hello():
    print "Hello World\n"
def world(name):
    print(name)
    return name
def tuplesp(a,b,c):
    print("int_flot_striing :%d,%f,%s\n"%(a,b,c))
def AddMult(a,b):
    print("addmuilt in python")
    return (a+b,a*b)
def test_add(a, b):
    print 'add ', a, ' and ', b
    return a+b
def test_add2(a, b):
    print 'add2 ', a, ' and2 ', b
    return (a+b,)
