
//g++ boostDemo.cpp -o libboostDemo.so -shared -fPIC -I/usr/include/python2.7 -lboost_python//

#include <boost/python.hpp>
char const* greet()
{
    return "hello world";
}
char const* foo(int x,int y)
{
	return "foo";
} 
BOOST_PYTHON_MODULE(libboostDemo)//#python 中导入模块名，必须与生成的动态链接库libboostDemo.so点号前名字相同，
{
    using namespace boost::python;
    def("greet", greet);
    def("foo",foo,args("x","y"),"dd");//模块中子函数的名字，c++函数名，参数，提示说明
}
