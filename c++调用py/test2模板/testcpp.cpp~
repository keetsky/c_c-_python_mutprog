
/* 
//g++ -o bb bb.cpp -I/usr/include/python2.7 -L/usr/lib64/python2.7/config -lpython2.7
//g++ bb.cpp -o bb -lpython2.7

 * test.cpp 

 *  Created on: 2010-12-12 

 *      Author: Handy_Zhou 
在python 中不能有中文注释

 */  

#include <python2.7/Python.h>  

#include <iostream>  
#include <stdio.h>
#include <string>  
using namespace std;

void printDict(PyObject* obj) {  

    if (!PyDict_Check(obj))  

        return;  

    PyObject *k=NULL, *keys=NULL;  

    keys = PyDict_Keys(obj);  

    for (int i = 0; i < PyList_GET_SIZE(keys); i++) {  

        k = PyList_GET_ITEM(keys, i);  

        char* c_name = PyString_AsString(k);  

        printf("%s\n", c_name);  

    }  

}  

int main() {  

    Py_Initialize();  

    if (!Py_IsInitialized())  

        return -1;  

    PyRun_SimpleString("import sys");  

    PyRun_SimpleString("sys.path.append('./')");  //编译目录，寻找test.py路径

    //导入模块

    PyObject*  pModule =NULL; 
    pModule = PyImport_ImportModule("testpy");  

    if (!pModule) {  

        printf("[ERROR] Python get module failed!\n");  //一般是python程序错误

        return -1;  

    }  

    //模块的字典列表  

    PyObject* pDict =NULL;
    pDict = PyModule_GetDict(pModule);  

    if (!pDict) {  

        printf("Cant find dictionary.\n");  

        return -1;  

    }  

    //打印出来看一下  

    printDict(pDict);  
//####################数据读取
  //整数读取int_data=5
  PyObject* pInt_data= PyDict_GetItemString(pDict, "int_data");
  int int_data;
  PyArg_Parse(pInt_data, "i", &int_data);
  cout<<"int_data:"<<int_data<<endl;
 

//###################函数调用  
    //HelloWorld()
    PyObject* pFunHelloWorld= PyDict_GetItemString(pDict, "HelloWorld"); 
    if (!pFunHelloWorld) {  
        printf("Cant find function HelloWorld().\n");  
        return -1;  
    } 
    PyEval_CallObject(pFunHelloWorld, NULL);
    Py_DECREF(pFunHelloWorld);

    //sayhi(name) return name
    PyObject* pFunHi = PyDict_GetItemString(pDict, "sayhi"); 
    if (!pFunHi) {  
        printf("Cant find function sayhi().\n");  
        return -1;  
    } 
    string name="keetsky";  
    PyObject * pArgs = NULL;
    pArgs = PyTuple_New(1); 
    PyObject * Arg1 = NULL;
    Arg1 = Py_BuildValue("s", name.data());//arg1 = Py_BuildValue("s", name);如果使用char *name="dddd";
    PyTuple_SetItem(pArgs, 0, Arg1);
    PyObject* pSayhi=NULL;
    pSayhi=PyObject_CallObject(pFunHi, pArgs);//PyObject_CallFunction(pFunHi,"s","name1");  传参数name.data()将报错
    char* sayhi;
    PyArg_Parse(pSayhi, "s", &sayhi);//
    cout << "sayhi:" << sayhi << endl;
    Py_DECREF(pFunHi);//释放 
    Py_DECREF(pArgs);
    Py_DECREF(Arg1);

    //add(a,b)  return a+b
    PyObject* pFunAdd = PyDict_GetItemString(pDict, "add"); 
    if (!pFunAdd) {  
        printf("Cant find function add().\n");  
        return -1;  
    } 
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 5));//
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 7));//
    PyObject *pReturn = NULL;
    pReturn = PyEval_CallObject(pFunAdd, pArgs);//
    int result;
    PyArg_Parse(pReturn, "i", &result);//
    cout << "5+7 = " << result << endl;
    Py_DECREF(pFunAdd);//释放 
    Py_DECREF(pArgs);
    Py_DECREF(pReturn);
   //addMult(a,b)  return a+b,a*b
   PyObject* pFunAddMult = PyDict_GetItemString(pDict, "AddMult"); 
    if (!pFunAddMult) {  
        printf("Cant find function AddMult().\n");  
        return -1;  
    } 
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 8));//
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 9));////args = Py_BuildValue("(ifs)", 100, 3.14, "hello");//或只使用这段代替；对于无参数函数args = Py_BuildValue("()");  或使用：PyTuple_SetItem(args, 0, Py_BuildValue("i",100));  。参数符号查看https://docs.python.org/release/1.5.2p2/ext/parseTuple.html http://www.cnblogs.com/apexchu/p/5015961.html
    pReturn = PyEval_CallObject(pFunAddMult,pArgs);
    int result1 = 0;
    int result2 = 0;
    PyArg_ParseTuple(pReturn,"i|i", &result1,&result2);
    printf("Function[AddMult] call successful a + b = %d, a * b = %d\n", result1, result2);
    Py_DECREF(pFunAddMult);           //释放
    Py_DECREF(pArgs);
    Py_DECREF(pReturn);  
    
//##################################dict 字典
    //TestDict(dict)  return dict
    PyObject* pFunDict = PyDict_GetItemString(pDict, "TestDict"); 
    if (!pFunAdd) {  
        printf("Cant find function TestDict().\n");  
        return -1;  
    }
    pArgs = PyTuple_New(1); 
    PyObject *pDict_Test=NULL;
    pDict_Test = PyDict_New(); //创建字典对象
    PyDict_SetItemString(pDict_Test, "Name", Py_BuildValue("s", "keetsky")); //
    PyDict_SetItemString(pDict_Test, "Age", Py_BuildValue("i", 25)); //
    PyTuple_SetItem(pArgs, 0, pDict_Test);//
    pReturn = PyEval_CallObject(pFunDict, pArgs);//
    int size = PyDict_Size(pReturn);
    cout << "size: " << size << endl;
    PyObject *pNewAge = PyDict_GetItemString(pReturn, "Age");//返回age键对应的值
    const char* Name="";
    PyObject *pName = PyDict_GetItemString(pReturn, "Name");
    PyArg_Parse(pName, "s", &Name);
    cout << "name: " << Name<< endl;
    int newAge;
    PyArg_Parse(pNewAge, "i", &newAge);
    cout << "True Age: " << newAge << endl;
    Py_DECREF(pFunDict);//释放 
    Py_DECREF(pArgs);
    Py_DECREF(pDict_Test);
    Py_DECREF(pNewAge);
    Py_DECREF(pName);
    Py_DECREF(pReturn);

  
//#################################类的调用
    //演示构造一个Python对象，并调用Class的方法  

    //获取Second类  

    PyObject* pClassSecond = PyDict_GetItemString(pDict, "Second");  

    if (!pClassSecond) {  

        printf("Cant find second class.\n");  

        return -1;  

    }  

    //获取Person类  

    PyObject* pClassPerson = PyDict_GetItemString(pDict, "Person");  

    if (!pClassPerson) {  

        printf("Cant find person class.\n");  

        return -1;  

    }  

    //构造Second的实例  

    PyObject* pInstanceSecond = PyInstance_New(pClassSecond, NULL, NULL);  

    if (!pInstanceSecond) {  

        printf("Cant create second instance.\n");  

        return -1;  

    }  

    //构造Person的实例  

    PyObject* pInstancePerson = PyInstance_New(pClassPerson, NULL, NULL);  

    if (!pInstancePerson) {  

        printf("Cant find person instance.\n");  

        return -1;  
    } 
    char *FuncGreet="greet";
    char *FunArgs="Hello Kitty!";
    char  *dataf="s";
    pReturn=PyObject_CallMethod(pInstancePerson,FuncGreet, dataf, FunArgs);
    PyObject_CallMethod(pInstancePerson,"sayHi", NULL, NULL);
    //类函数如何读取返回值
    //char* baby="dd";
    //PyArg_Parse(pReturn, "s", &baby);
    //cout<<"newperson:"<<baby<<endl;
    //把person实例传入second的invoke方法  
    PyObject_CallMethod(pInstanceSecond, "invoke", "O", pInstancePerson );  
    //释放  
    Py_DECREF(pInstanceSecond);  
    Py_DECREF(pInstancePerson);  
    Py_DECREF(pClassSecond);  
    Py_DECREF(pClassPerson);  
    Py_DECREF(pModule);  

  
    Py_Finalize();
    return 0;  

} 


