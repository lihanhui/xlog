#include <chrono>
#include <thread>

#include <xlog/xlog.h>
int main(){
    using namespace  aquaman::xlog;
    logger logger_ = logger("main");
    LOG(logger_, log_level::DEBUG, "{}", "this is main func of xlog test");
    
    while(true){
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(500ms);
        LOG_IF(1>1, logger_, log_level::DEBUG, "{}", "this is log in main loop of xlog test");
    }
    return 0;
}
