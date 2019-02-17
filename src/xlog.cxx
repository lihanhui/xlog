#include <chrono>
#include <thread>

#include <xlog/xlog.h>
int main(){
    aquaman::xlog::logger logger = aquaman::xlog::logger("main");
    LOG(logger, aquaman::xlog::log_level::DEBUG, "{}", "this is main func of xlog test");
    
    while(true){
    	using namespace std::chrono_literals;
    	std::this_thread::sleep_for(500ms);
    	LOG(logger, aquaman::xlog::log_level::DEBUG, "{}", "this is log in main loop of xlog test");
    }
    return 0;
}
