cmake_minimum_required(VERSION 2.8)

project(embedding) #随便起一个工程名称

#boost.python,python头文件路径

find_package( Boost REQUIRED system)

include_directories( /usr/include/python2.7
		     ${Boost_INCLUDE_DIR})

link_directories(/usr/lib/python2.7  ${Boost_LIBRARY_DIRS})  #boost.python,python动态链接库路径
set( Boost_USE_STATIC_LIBS        OFF )
set( Boost_USE_MULTITHREADED      ON )
set( Boost_USE_STATIC_RUNTIME     OFF )
set( BOOST_ALL_DYN_LINK           ON )
link_libraries( 
	-lpython2.7#
         libboost_python.so #libpython2.7.so    
        ${Boost_LIBRARIES}
	)

add_executable (embedding embedding.cc)  #源文件embedding.cc 生成可执行文件embedding


