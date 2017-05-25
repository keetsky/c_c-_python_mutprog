/***g++ -o libpycallcpp.so -shared -fPIC pycallcpp.cpp */ 
//Python调用C++库比较简单，不经过任何封装打包成so，再使用python的ctypes调用即可。 
// 需要extern "C"来辅助，也就是说还是只能调用C函数，不能直接调用方法，但是能解析C++方法。不是用extern "C"，构建后的动态链接库没有这些函数的符号表。
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>  
using namespace std;
extern "C" int foo(int a, int b)  
{  
  printf("you input %d and %d\n", a, b);  
  return a+b;  
}  

///调用类
class TestLib{  
        public:  
                void display();  
                void display(int a);  
  
  
};  
void TestLib::display() {  
        cout<<"First display"<<endl;  
}  
  
  
void TestLib::display(int a) {  
        cout<<"Second display:"<<a<<endl;  
}  
extern "C" {  
        TestLib obj;  
        void display() {  
               obj.display();   
        }  
        void display_int(int a) {  
               obj.display(a);   
        }  
}  
