#ifndef XLOG_CUSTOMERIZED_LOBBACKEND

#include <string>
#include <string_view>
#include <plog/Log.h>
#include <plog/Logger.h>

#include "xlog/xlog.h"
#include "xlog/wrapper/wrapper.h"


static std::shared_ptr<xlog::log_wrapper> impl = xlog::log_wrapper_impl::get_log_wrapper_impl();

std::shared_ptr<xlog::log_wrapper> xlog::log_wrapper_impl::get_log_wrapper_impl(){
    std::shared_ptr<xlog::log_wrapper> impl = std::make_shared<xlog::log_wrapper_impl>();
    xlog::logger::set_log_wrapper(impl);
    return impl;
}

xlog::log_wrapper_impl::log_wrapper_impl(){
    plog::init(plog::verbose, "./log.txt", 8*1024*1024, 10);
}

plog::Severity to_serverity(xlog::log_level level){
    switch(level){
        case xlog::log_level::VERBOSE:
            return plog::verbose;
        case xlog::log_level::DEBUG:
            return plog::debug;
        case xlog::log_level::INFO:
            return plog::info;
        case xlog::log_level::WARN:
            return plog::warning;
        case xlog::log_level::ERROR:
            return plog::error;
        case xlog::log_level::FATAL:
            return plog::fatal;
        default:
            return plog::verbose; 
    }
}
void xlog::log_wrapper_impl::log(xlog::log_level level, const nstring & file,  const nstring & func, int line, const nstring & data) {
    (*plog::get())+=plog::Record(to_serverity(level), func.c_str(), line, file.c_str(), 0)<< data;
    //std::cout<<file<<":"<<func<<":"<<line<<"\t"<<data<<std::endl;
}
#endif
