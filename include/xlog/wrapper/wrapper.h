#ifndef AQUAMAN_XLOG_WRAPPER_WRAPPER_H
#define AQUAMAN_XLOG_WRAPPER_WRAPPER_H

#include "xlog/log_level.h"

namespace xlog {

#ifdef _WIN32
    using nstring = std::wstring;
#else
    using nstring = std::string;
#endif 

struct log_wrapper: public std::enable_shared_from_this<log_wrapper>  {
    virtual void log(log_level, const nstring & file,  const nstring & func, int line, const nstring & data) = 0;
};

struct log_wrapper_impl: public log_wrapper{
public: 
    static std::shared_ptr<log_wrapper> get_log_wrapper_impl(); 
    log_wrapper_impl();
    void log(log_level, const nstring & file,  const nstring & func, int line, const nstring & data) override;
};
};
#endif