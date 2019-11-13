#ifndef __LOG_HPP__
#define __LOG_HPP__


#include <csignal>
#include <execinfo.h>
#include <iostream>
#include <unistd.h>
#include <boost/log/trivial.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>

#include <boost/log/attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>


namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

enum SeverityLevel {
    Info,
    Notice,
    Debug,
    Warning,
    Error,
    Fatal
};
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(lg, src::severity_logger_mt<SeverityLevel>)

// 使用方法：例如打印一条安全级别为error的日志，代码书写格式：
// OA_LOG_ERROR<<"输入内容，按照流方式输入字符串，数字或者加入相关变量"
#define OA_LOG_INFO   BOOST_LOG_SEV(lg::get(),Info)
#define OA_LOG_NOTICE  BOOST_LOG_SEV(lg::get(),Notice)
#define OA_LOG_DEBUG   BOOST_LOG_SEV(lg::get(),Debug)
#define OA_LOG_WARNING BOOST_LOG_SEV(lg::get(),Warning)
#define OA_LOG_ERROR   BOOST_LOG_SEV(lg::get(),Error)
#define OA_LOG_FATAL   BOOST_LOG_SEV(lg::get(),Fatal)

template<typename CharT, typename TraitsT>
inline std::basic_ostream<CharT, TraitsT> &operator<<(
        std::basic_ostream<CharT, TraitsT> &strm, SeverityLevel lvl) {
    static const char *const str[] =
            {
                    "I",//info
                    "N",//notice
                    "D",//debug
                    "W",//warning
                    "E",//error
                    "F"//fatal
            };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}
class oa_log {
  public:

    void initLog();

    std::string getProcessName(char *processname);

    void handle_segv(int signum);

    static oa_log* global() {
        static oa_log _log;
        return &_log;
    }
};

#endif
