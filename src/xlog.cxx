#include <chrono>
#include <thread>

#include <xlog/xlog.h>

using namespace xlog;

std::shared_ptr<log_wrapper> logger::wrapper_ = nullptr;

bool logger::log_enabled(log_level level){
    return true;
}


int main(){
    using namespace  xlog;
    logger logger_ = logger("main");
    XLOG(logger_, log_level::DEBUG, "{}", "this is main func of xlog test");
    
    while(true){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
        XLOG_IF(1>0, logger_, log_level::DEBUG, "{}", "this is log in main loop of xlog test");
    }
    return 0;
}
