#include <iostream>
using namespace std;
#include <boost/python.hpp>
using namespace boost::python;

int main(int argc, char *argv[])
{
  Py_Initialize();

  object main_module = import("__main__");
  object main_namespace = main_module.attr("__dict__");
  exec("hello = file('hello.txt', 'w')\n"
       "hello.write('Hello world!')\n"
       "hello.close()",
       main_namespace);
  exec("result = 5 ** 2", main_namespace);
  int five_squared = extract<int>(main_namespace["result"]);
  cout << "The five_squeared caculated by python is " << five_squared << endl;

   // Load the sys module.
  object sys = import("sys");

  // Extract the python version.
  std::string version = extract<std::string>(sys.attr("version"));
  std::cout << version << std::endl;

 //要求simple.py与可执行文件在相同路径下! 运行ok,或设置如下
  object simple = exec_file("../simple.py",main_namespace, main_namespace);//build下可执行文件寻找文件目录
  //dict global;
  //object result = exec_file("simple.py", global, global);
  object foo = main_namespace["foo"];
  int val = extract<int>(foo(5));
  cout << "Python has caculated foo as " << val << endl;


  return 0;
}
