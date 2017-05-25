import ctypes  
lib = ctypes.cdll.LoadLibrary("./libpycall.so")    
lib.foo(1, 3)  
print '***finish***' 
