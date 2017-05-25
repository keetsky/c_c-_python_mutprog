/***gcc -o libpycall.so -shared -fPIC pycall.c */ 
//Python调用C库比较简单，不经过任何封装打包成so，再使用python的ctypes调用即可。 
#include <stdio.h>  
#include <stdlib.h>  
int foo(int a, int b)  
{  
  printf("you input %d and %d\n", a, b);  
  return a+b;  
}  
