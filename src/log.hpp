#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <string>
#include <cstdio>
#include <sstream>
#include <csignal>
#include <execinfo.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/fmt/ostr.h"

// 日志使用方式：include头文件log.hpp
// 在想记录日志的地方输入： (例如输入安全级别为info的一条日志)
// OA_LOG_INFO("messag：{0},{1}",str1,str2);
// {0} {1} ... 是占位符记号，替换str1，str2字符串(或者数字)内容
// 还有如下其他安全级别的宏供使用
/* #define OA_LOG_INFO(args...)       \
{   \
    std::lock_guard<std::mutex> lk(log_oa::global()->mut);\
    log_oa::global()->get_log()->info(args);\
} */
#define OA_LOG_INFO       log_oa::global()->get_log()->info
#define OA_LOG_TRACE      log_oa::global()->get_log()->trace
#define OA_LOG_DEBUG      log_oa::global()->get_log()->debug
#define OA_LOG_WARNING    log_oa::global()->get_log()->warn
#define OA_LOG_ERROR      log_oa::global()->get_log()->error
#define OA_LOG_CRITICAL   log_oa::global()->get_log()->critical

// 数字转字符串的功能，如有需要也可以使用
#define NUM2STR(x)        log_oa::global()->num2str(x)

class log_oa {

private:
    std::shared_ptr<spdlog::logger> my_logger;
public:
    //std::mutex mut;
    ~log_oa(){
        //spdlog::shutdown();
        spdlog::drop_all();
    };
    void init();

    std::string getProcessName();

    std::string getHostName();

    void handle_segv(int signum);

    std::shared_ptr<spdlog::logger> get_log()
    {
        return my_logger;
    }

    void multi_sink_init();

    //弱化了输入方式，暂时不用。
    void log_record(std::string msg,std::string level);
    std::string getCurrentDateTime();

    template<typename T>
    std::string num2str(T num) {
        std::stringstream ss;
        ss << num;
        std::string str1 = ss.str();
        return str1;
    }
    static log_oa *global() {
        static log_oa _log;
        return &_log;
    }
};


#endif
