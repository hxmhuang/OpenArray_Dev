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

#define OA_LOG_INFO       log_oa::global()->get_log()->info
#define OA_LOG_TRACE      log_oa::global()->get_log()->trace
#define OA_LOG_DEBUG      log_oa::global()->get_log()->debug
#define OA_LOG_WARNING    log_oa::global()->get_log()->warn
#define OA_LOG_ERROR      log_oa::global()->get_log()->error
#define OA_LOG_CRITICAL   log_oa::global()->get_log()->critical
#define NUM2STR(x)        log_oa::global()->num2str(x)

class log_oa {

private:
    std::shared_ptr<spdlog::logger> my_logger;
public:

    ~log_oa(){
        spdlog::shutdown();
    };
    void init();

    std::string getProcessName();

    std::string getHostName();

    void handle_segv(int signum);

    std::shared_ptr<spdlog::logger> get_log()
    {
        return my_logger;
    }

    void trace();

    void multi_sink_init();

    void syslog();


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
