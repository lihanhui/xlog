#include <string>
#include <string_view>

#include <xlog/xlog.h>

using namespace aquaman::xlog;

bool logger::log_enabled(log_level level){
	return true;
}

/*template<class... Args> logger & logger::log(log_level level, std::string && file, int line, std::string_view fmt, const Args&... args){
	return *this;
}//*/