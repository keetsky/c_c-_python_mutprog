//g++ -o bb bb.cpp -I/usr/include/python2.7 -L/usr/lib64/python2.7/config -lpython2.7
//g++ bb.cpp -o bb -lpython2.7
//函数介绍http://blog.csdn.net/magictong/article/details/8947892
//c++中调用python       http://blog.csdn.net/c_cyoxi/article/details/23978007

#include "python2.7/Python.h"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
int main()
{
    Py_Initialize();   // ## 初始化
// 将Python工作路径切换到待调用模块所在目录，一定要保证路径名的正确性
    // 检查初始化是否成功
    if ( !Py_IsInitialized() )
    {
        return -1;
    }


    // 添加当前路径
    //把输入的字符串作为Python代码直接运行，返回0
    //表示成功，-1表示有错。大多时候错误都是因为字符串
    //中有语法错误。
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");
    PyObject * pModule = NULL;
    PyObject * pFunc = NULL;
    PyObject * pClass = NULL;
    PyObject * pInstance = NULL;
    PyObject * pDict = NULL;
    PyObject * pArgs = NULL;
    PyObject * args = NULL;
    PyObject * pRet =NULL;


   //这里是要调用的dd.py的文件名
   // PyObject* moduleName = PyString_FromString("dd"); 
   // pModule = PyImport_Import(moduleName);
    pModule = PyImport_ImportModule("dd");
 	   if (!pModule) // 加载模块失败
  	  {
    	    cout << "[ERROR] Python get module failed." << endl;
   	     return 0;
   	   }
    cout << "[INFO] Python get module succeed." << endl;

//这里是要调用的函数名（1）
    pFunc= PyObject_GetAttrString(pModule, "hello");
 	if (!pFunc || !PyCallable_Check(pFunc))  // 验证是否加载成功
   	 {
        cout << "[ERROR] Can't find funftion (hell)" << endl;
        return 0;
   	 }
    	cout << "[INFO] Get function (hell) succeed." << endl;
    //调用函数
    PyEval_CallObject(pFunc, NULL);
    Py_DECREF(pFunc);  
    Py_DECREF(pFunc);
//函数（2）
    pFunc= PyObject_GetAttrString(pModule, "world");
    PyObject_CallFunction(pFunc,"s", "zhengji");//s表示带入的参数为字符串
    Py_DECREF(pFunc);
   
    
  
    

//带参数函数（3）
    pFunc=PyObject_GetAttrString(pModule, "test_add");
    //设置参数

    args = PyTuple_New(2);   // 2个参数，定义函数参数元祖大小
    PyObject* arg1 = PyInt_FromLong(4);    // 参数一设为4
    PyObject* arg2 = PyInt_FromLong(3);    // 参数二设为3
    PyTuple_SetItem(args, 0, arg1);//传入参数到元祖中
    PyTuple_SetItem(args, 1, arg2);
// 调用函数
    pRet = PyObject_CallObject(pFunc, args);
    if (pRet)  // 验证是否调用成功
    {
       long result = PyInt_AsLong(pRet);//PyInt_AsLong，PyFloat_AsDouble， PyString_AsString,对于单参数
       cout << "result:" << result<<endl;//输出函数返回值 
    }
//


 

//带参数函数（4）  多参数返回值 
   pFunc = PyObject_GetAttrString(pModule, "AddMult");
   pArgs = Py_BuildValue("ii", 4, 5);
   pRet = PyEval_CallObject(pFunc,pArgs);
   int a = 0;
   int b = 0;
   
   if (pRet && PyArg_ParseTuple(pRet,"i|i", &a,&b))
     {
        printf("Function[AddMult] call successful a + b = %d, a * b = %d\n", a, b);
       
     }
   if (pArgs)
      Py_DECREF(pArgs);
   if (pFunc)
      Py_DECREF(pFunc);  

//带参数函数（5） ,对于单个返回值数字，注意python 的return 写法必须为（dd，）否则无法读取
   pFunc = PyObject_GetAttrString(pModule, "test_add2");
   pArgs = Py_BuildValue("ii", 5, 5);
   pRet = PyEval_CallObject(pFunc,pArgs);
   int c = 0;
   if (pRet && PyArg_ParseTuple(pRet,"i", &c))
     {
        printf("Function[AddMult] call successful a + b= %d\n", c);
       
     }
   if (pArgs)
      Py_DECREF(pArgs);
   if (pFunc)
      Py_DECREF(pFunc);  


//字符的返回值不清楚

//带参数函数（6）
    pFunc=PyObject_GetAttrString(pModule, "tuplesp");
    //设置参数
    args = PyTuple_New(3);   // 3个参数，定义函数参数元祖大小
    arg1 = Py_BuildValue("i", 100); // 整数参数
    arg2 = Py_BuildValue("f", 3.14); // 浮点数参数
    PyObject* arg3 = Py_BuildValue("s", "hello"); // 字符串参数
    PyTuple_SetItem(args, 0, arg1);
    PyTuple_SetItem(args, 1, arg2);
    PyTuple_SetItem(args, 2, arg3);
    //args = Py_BuildValue("(ifs)", 100, 3.14, "hello");//或只使用这段代替；对于无参数函数args = Py_BuildValue("()");  或使用：PyTuple_SetItem(args, 0, Py_BuildValue("i",100));  。参数符号查看https://docs.python.org/release/1.5.2p2/ext/parseTuple.html http://www.cnblogs.com/apexchu/p/5015961.html
   // 调用函数
    pRet = PyObject_CallObject(pFunc, args);	

//测试调用python的类
    pClass = PyObject_GetAttrString(pModule, "Student");
    if (!pClass) {
        printf("Can't find Student class.\n");
        return -1;
    }
    pInstance = PyInstance_New(pClass, NULL, NULL);
    if (!pInstance) {
        printf("Can't create Student instance.\n");
        return -1;
    }
    PyObject_CallMethod(pInstance, "SetName", "s","my family");
    PyObject_CallMethod(pInstance, "PrintName",NULL,NULL);
    //调用Py_Finalize，这个根Py_Initialize相对应的。

   Py_Finalize();
    return 0;
}




/*
Py_BuildValue("")                       None

Py_BuildValue("i",123)                 123

Py_BuildValue("iii",123, 456, 789)     (123, 456, 789)

Py_BuildValue("s","hello")             'hello'

Py_BuildValue("ss","hello", "world")    ('hello', 'world')

Py_BuildValue("s#","hello", 4)         'hell'

Py_BuildValue("()")                     ()

Py_BuildValue("(i)",123)               (123,)

Py_BuildValue("(ii)",123, 456)         (123, 456)

Py_BuildValue("(i,i)",123, 456)        (123, 456)

Py_BuildValue("[i,i]",123, 456)        [123, 456]

Py_BuildValue("{s:i,s:i}",

                 "abc", 123, "def", 456)    {'abc': 123, 'def': 456}

Py_BuildValue("((ii)(ii))(ii)",

                 1, 2, 3, 4, 5, 6)         (((1, 2), (3, 4)), (5, 6))
*/





