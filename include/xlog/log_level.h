#ifndef AQUAMAN_XLOG_LOG_LEVEL_H
#define AQUAMAN_XLOG_LOG_LEVEL_H

namespace xlog {

enum class log_level {
    VERBOSE     = 0,
    DEBUG       = 1,
    INFO        = 2,
    WARN        = 3,
    ERROR       = 4,
    FATAL       = 5
};

};

#endif