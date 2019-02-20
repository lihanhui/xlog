#include <string>
#include <string_view>

#include <xlog/xlog.h>

using namespace aquaman::xlog;

bool logger::log_enabled(log_level level){
    return true;
}
bool logger::log_backend_enabled(){
    return false;
}
