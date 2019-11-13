#ifndef __LOG_CPP__
#define __LOG_CPP__

#include "log.hpp"

void oa_log::handle_segv(int signum)
{
    void *array[100];
    size_t size;
    char **strings;
    size_t i;
    signal(signum, SIG_DFL); /* 还原默认的信号处理handler */
    size = backtrace (array, 100);
    strings = (char **)backtrace_symbols (array, size);
    fprintf(stderr,"Launcher received SIG: %d Stack trace:\n", signum);
    for (i = 0; i < size; i++)
    {
        fprintf(stderr,"%ld %s \n",i,strings[i]);

    }
    free (strings);
}

std::string oa_log::getProcessName(char* processname ){
    char processdir[2048] = { 0 };
//    char processname[2048] = { 0 };
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

void oa_log::initLog(){


    logging::formatter formatter=
            expr::format("%2% %1% %3%[%4%]: [%5%] %6%")
                % expr::attr<std::string>("Tag")
                % expr::format_date_time< boost::posix_time::ptime >("TimeStamp","%Y-%m-%d %H:%M:%S")
                % expr::attr<std::string>("ProcessName")
//                % expr::attr<attrs::current_process_id::value_type>("ProcessID")
                % expr::attr<int>("ProcessId")
                % expr::attr<SeverityLevel>("Severity")
                % expr::smessage;

    logging::add_common_attributes();

//    auto console_sink=logging::add_console_log();
    auto file_sink=logging::add_file_log
            (
                    keywords::file_name="openarray_%Y%m%d%H%M%S.log",      //文件名 %Y-%m-%d_%N.log
                    keywords::rotation_size=10*1024*1024,       //单个文件限制大小
                    keywords::time_based_rotation=sinks::file::rotation_at_time_point(0,0,0)    //每天重建
//                    keywords::format =
//                            (
//                                    expr::stream
//                                            << expr::format_date_time< boost::posix_time::ptime >("TimeStamp","%Y-%m-%d %H:%M:%S")
//                                            << " " << expr::attr<std::string>("Tag")<<" "<<expr::attr<std::string>("ProcessName")
//                                            << "[" << expr::attr<int>("ProcessID")<<"]: ["<<expr::attr<SeverityLevel>("Severity")
//                                            <<"] "<<expr::smessage
//                            )
            );
//    logging::core::get()->set_filter(logging::trivial::severity>=logging::trivial::info);
    file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
            keywords::target="logs",        //文件夹名
            keywords::max_size=50*1024*1024,    //文件夹所占最大空间
            keywords::min_free_space=100*1024*1024  //磁盘最小预留空间
    ));

//    file_sink->set_filter(log_severity>=Log_Warning);   //日志级别过滤

    file_sink->locked_backend()->scan_for_files();

//    console_sink->set_formatter(formatter);
    file_sink->set_formatter(formatter);
    file_sink->locked_backend()->auto_flush(true);

    char computer[256];
    char processname[2048] = {0};
    gethostname(computer, 256);
    std::string str_computer = computer;
    std::string str_processname = oa_log::global()->getProcessName(processname);

    logging::core::get()->add_global_attribute("Tag",attrs::constant< std::string >(str_computer));
    logging::core::get()->add_global_attribute("ProcessId",attrs::constant< int >(getpid()));
    logging::core::get()->add_global_attribute("ProcessName",attrs::constant< std::string >(str_processname));
//    logging::core::get()->add_global_attribute("Scope",attrs::named_scope());
//    logging::core::get()->add_global_attribute("ProcessID",attrs::current_process_id());
//    logging::core::get()->add_global_attribute("ProcessName",attrs::current_process_name());
//    logging::core::get()->add_sink(console_sink);
    logging::core::get()->add_sink(file_sink);

}
#endif
