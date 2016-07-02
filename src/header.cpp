//用于生产预编译，不要添加代码
#include "header.hpp"
#ifdef BOOST_ALL_NO_LIB
#include <libs/system/src/error_code.cpp>
///////////////////////Thread  ////////////////////////////////////////////
#ifdef _MSC_VER
#include <boost/config.hpp>
#include <libs/thread/src/win32/thread.cpp>
#include <libs/thread/src/win32/tss_dll.cpp>
#include <libs/thread/src/win32/tss_pe.cpp>
#include <libs/thread/src/future.cpp>
void boost::tss_cleanup_implemented(void){}
#else
#include <libs/thread/src/pthread/thread.cpp>
#include <libs/thread/src/pthread/once.cpp>
#endif




#endif 


