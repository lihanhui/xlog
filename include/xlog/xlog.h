#ifndef AQUAMAN_XLOG_XLOG
#define AQUAMAN_XLOG_XLOG

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <string_view>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include "xlog/log_level.h"
#include "xlog/wrapper/wrapper.h"

namespace xlog {


class logger {
private:
    std::string class_name; // or fileName
    static std::shared_ptr<log_wrapper> wrapper_;
public:
    static void set_log_wrapper(std::shared_ptr<log_wrapper> wrapper_){
        logger::wrapper_ = wrapper_;
    }
public:
    logger(){
        this->class_name = "root";
    }
    logger(std::string class_name){
        this->class_name = class_name;
    }
    std::string get_class_name(){
        return this->class_name;
    }
    bool log_enabled(log_level level);//{
    //  return true;
    //}
    template<class... Args> logger & log(log_level level, std::string && file, std::string && func, int line, std::string && format_, const Args&... args){
        if(file.length() > 32){
            file = file.substr(file.length() - 32);
        }
        std::string cnt = fmt::format(format_, args...);
        if(!this->log_backend_enabled()){
            std::cout<<current()<<" "<<file<<":"<<get_class_name()<<":"<<func<<":"<<line<<"\t"<<cnt<<std::endl;
        }else{
            logger::wrapper_->log(level, file, func, line, cnt);
        }
        return *this;
    }
private:
    bool log_backend_enabled(){
        return logger::wrapper_ != nullptr;
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
#ifdef _MSC_VER
#   define XLOG_GET_FUNC()      __FUNCTION__
#elif defined(__BORLANDC__)
#   define XLOG_GET_FUNC()      __FUNC__
#else
#   define XLOG_GET_FUNC()      __PRETTY_FUNCTION__
#endif
    
#define XLOG_IF(cond, logger_, level_, fmt, args...) do {                                   \
    if(!(cond)){                                                                            \
        break;                                                                              \
    }                                                                                       \
    if(logger_.log_enabled(level_)){                                                        \
        logger_.log(level_, XLOG_GET_FILE(), XLOG_GET_FUNC(), XLOG_GET_LINE(), fmt, ##args);\
    }                                                                                       \
}while(0)

#define XLOG(logger_, level_, fmt, args...) do {                                            \
    if(logger_.log_enabled(level_)){                                                        \
        logger_.log(level_, XLOG_GET_FILE(), XLOG_GET_FUNC(), XLOG_GET_LINE(), fmt, ##args);\
    }                                                                                       \
}while(0)

};

#endif
