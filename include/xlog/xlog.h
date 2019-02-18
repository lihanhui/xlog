#ifndef AQUAMAN_XLOG_XLOG
#define AQUAMAN_XLOG_XLOG

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <string_view>

#include <fmt/format.h>

namespace aquaman::xlog {

enum class log_level {
    VERBOSE     = 0,
    DEBUG       = 1,
    INFO        = 2,
    WARN        = 3,
    ERROR       = 4,
    FATAL       = 5
            
    
};

class logger {
private:
    std::string className; // or fileName
public:
    logger(){
        this->className = "root";
    }
    logger(std::string className){
        this->className = className;
    }
    std::string get_class_name(){
        return this->className;
    }
    bool log_enabled(log_level level);//{
    //  return true;
    //}
    template<class... Args> logger & log(log_level level, std::string && file, int line, std::string_view format_, const Args&... args){
        std::string cnt = fmt::format(format_, args...);
        if(!this->log_backend_enabled()){
            std::cout<<current()<<" "<<file<<":"<<get_class_name()<<":"<<line<<"\t"<<cnt<<std::endl;
        }
        return *this;
    }
private:
    bool log_backend_enabled(){
        return false;
    }
    inline std::string current(){
        std::chrono::time_point<std::chrono::system_clock> p2 = std::chrono::system_clock::now();
        std::time_t today_time = std::chrono::system_clock::to_time_t(p2);
        char buf[33] = {};
        strftime( buf, 32, "%F %T", std::localtime(&today_time) );
        return std::string(buf);
    }
    
} ;
    
#define XLOG_GET_FILE() __FILE__
#define XLOG_GET_LINE() __LINE__
//aquaman::xlog::logger l = std::forward<aquaman::xlog::logger>(logger_);           \
//aquaman::xlog::log_level level = std::forward<aquaman::xlog::log_level> (level_); \
    
#define LOG_IF(cond, logger_, level_, fmt, args...) do {                                \
    if(!(cond)){                                                                        \
        break;                                                                          \
    }                                                                                   \
    if(logger_.log_enabled(level_)){                                                    \
        logger_.log(level_, XLOG_GET_FILE(), XLOG_GET_LINE(), fmt, ##args);             \
    }                                                                                   \
}while(0)

#define LOG(logger_, level_, fmt, args...) do {                                         \
    if(logger_.log_enabled(level_)){                                                    \
        logger_.log(level_, XLOG_GET_FILE(), XLOG_GET_LINE(), fmt, ##args);             \
    }                                                                                   \
}while(0)



};

#endif