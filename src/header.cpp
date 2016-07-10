//用于生产预编译，不要添加代码
#include "header.hpp"
#ifdef BOOST_ALL_NO_LIB

////////////////////////System   ///////////////////////////////////////
#include <libs/system/src/error_code.cpp>

////////////////////////File System///////////////////////////////////////
#include <libs/filesystem/src/codecvt_error_category.cpp>
//#include <libs/filesystem/src/operations.cpp>
#include <libs/filesystem/src/path.cpp>
#include <libs/filesystem/src/path_traits.cpp>
#include <libs/filesystem/src/portability.cpp>
#include <libs/filesystem/src/unique_path.cpp>
#include <libs/filesystem/src/utf8_codecvt_facet.cpp>
#include <libs/filesystem/src/windows_file_codecvt.cpp>

/////////////////////Thread  ////////////////////////////////////////////
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



////////////////////////LOG Part//////////////////////////////////////////
#include <libs/log/src/attribute_name.cpp>
#include <libs/log/src/attribute_set.cpp>
#include <libs/log/src/attribute_value_set.cpp>
#include <libs/log/src/core.cpp>
#include <libs/log/src/record_ostream.cpp>
#include <libs/log/src/severity_level.cpp>
#include <libs/log/src/thread_id.cpp>
#include <libs/log/src/default_attribute_names.cpp>
#include <libs/log/src/default_sink.cpp>
#include <libs/log/src/thread_specific.cpp>
#include <libs/log/src/once_block.cpp>
#include <libs/log/src/exceptions.cpp>
#include <libs/log/src/unhandled_exception_count.cpp>
#include <libs/log/src/light_rw_mutex.cpp>
#include <libs/log/src/dump.cpp>
#include <libs/log/src/trivial.cpp>
#include <libs/log/src/global_logger_storage.cpp>
//#include <libs/log/src/code_conversion.cpp>
//#include <libs/log/src/named_scope.cpp>
//#include <libs/log/src/syslog_backend.cpp>
//#include <libs/log/src/timestamp.cpp>
//#include <libs/log/src/process_name.cpp>
//#include <libs/log/src/process_id.cpp>
//#include <libs/log/src/text_ostream_backend.cpp>
//#include <libs/log/src/text_file_backend.cpp>
//#include <libs/log/src/text_multifile_backend.cpp>
//#include <libs/log/src/threadsafe_queue.cpp>
//#include <libs/log/src/timer.cpp>


#endif 


