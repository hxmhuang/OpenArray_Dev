//
// Created by GP on 2019/11/14.
//

#include "log.hpp"

#include <time.h>
#include <unistd.h>
#include <iostream>

std::string log_oa::getCurrentDateTime() {
    time_t cur_time_t = time(NULL);
    char ch[64] = {0};
    strftime(ch, sizeof(ch) - 1, "%Y%m%d%H%M%S", localtime(&cur_time_t));
    std::string exe_time_str = ch;
    return exe_time_str;
}
void log_oa::handle_segv(int signum)
{
    void *array[100];
    size_t size;
    char **strings;
    size_t i;
    signal(signum, SIG_DFL); /* 还原默认的信号处理handler */
    size = backtrace (array, 100);
    strings = (char **)backtrace_symbols (array, size);
//    fprintf(stderr,"Launcher received SIG: %d Stack trace:\n", signum);
    OA_LOG_ERROR("Launcher received SIG: {0} Stack trace:", signum);
    for (i = 0; i < size; i++)
    {
//        fprintf(stderr,"%ld %s \n",i,strings[i]);
        OA_LOG_ERROR("{0}",strings[i]);
    }
    free (strings);
}

std::string log_oa::getHostName() {
    char computer[256];
    char processname[2048] = {0};
    gethostname(computer, 256);
    std::string str_computer = computer;
    return str_computer;
}

std::string log_oa::getProcessName(){
    char processdir[2048] = { 0 };
    char processname[2048] = { 0 };
    do
    {
        char* path_end;
        if (readlink("/proc/self/exe", processdir, 2048) <= 0)
            break;
        path_end = strrchr(processdir, '/');
        if (path_end == NULL)
            break;
        ++path_end;
        strcpy(processname, path_end);
        *path_end = '\0';
    } while (0);
    std::string str_processname = processname;
    return str_processname;
}


void log_oa::init(){
    std::string datetime = getCurrentDateTime();
    std::string filename = "logs/openarray_" + datetime + ".log";
//    spdlog::init_thread_pool(4096, 1);
//    my_logger = spdlog::basic_logger_mt<spdlog::async_factory>("file_logger", filename);
    my_logger = spdlog::basic_logger_mt("file_logger", filename);
    //设置最低级的要求，可以每次记录日志后便写入
    my_logger->set_level(spdlog::level::trace);
    my_logger->flush_on(spdlog::level::info);
    my_logger->set_pattern("[%Y-%m-%d %H:%M:%S "+getHostName()+" "+getProcessName()+" PID:"+num2str(getpid())+"]:[%^%L%$] %v");
//    my_logger->set_pattern("[%Y-%m-%d %H:%M:%S TID:%t] [%^%L%$] %v");
//    spdlog::enable_backtrace(10); // create ring buffer with capacity of 10  messages
//    for (int i = 0; i < 100; i++)
//    {
//        spdlog::debug("Backtrace message {}", i); // not logged..
//    }
//    // e.g. if some error happened:
//    spdlog::dump_backtrace(); // log them now!
    spdlog::flush_every(std::chrono::seconds(3));
//    my_logger->flush();
    my_logger->set_error_handler([](const std::string &msg) {
        printf("*** Custom log error handler: %s ***\n", msg.c_str());
    });
    //my_logger->info("init complete!");
}

void log_oa::multi_sink_init(){
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    std::string datetime = getCurrentDateTime();
    std::string filename = "logs/mulopenarray_" + datetime + ".log";
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
    logger.flush_on(spdlog::level::info);
    spdlog::flush_every(std::chrono::seconds(3));
    logger.set_error_handler([](const std::string &msg){
        printf("*** Custom log error handler: %s ***\n", msg.c_str());
    });
    logger.set_pattern("[%Y-%m-%d %H:%M:%S "+getHostName()+" PID:"+num2str(getpid())+"]:[%^%L%$] %v");
    logger.info("Multi sink init complete!");
    my_logger = logger.clone("multi_sink");

//    logger.warn("this should appear in both console and file");
//    logger.info("this message should not appear in the console, only in the file");
}

void log_oa::log_record(std::string msg,std::string level){
    if (level.find("info")!=std::string::npos){
        my_logger->info(msg);
    } else if(level.find("warn")!=std::string::npos){
        my_logger->warn(msg);
    }else if(level.find("trace")!=std::string::npos){
        my_logger->trace(msg);
    }else if(level.find("debug")!=std::string::npos){
        my_logger->debug(msg);
    }else if(level.find("error")!=std::string::npos){
        my_logger->error(msg);
    }else if(level.find("critical")!=std::string::npos){
        my_logger->critical(msg);
    }else
        my_logger->info(msg);
}
