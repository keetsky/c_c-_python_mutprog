import ctypes  
lib = ctypes.cdll.LoadLibrary("./libpycallcpp.so")    
lib.foo(1, 3)  
lib.display()
lib.display_int(2)
print '***finish***' 




