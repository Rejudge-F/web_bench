#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
enum HttpVersion {
    HTTP_10 = 10,
    HTTP_11 
};

enum HttpMethod {
    METHOD_GET = 1,
    METHOD_POST,
    METHOD_OPTIONS,
    METHOD_HEAD,
    METHOD_TRACE
};

// global variable 
int HttpVersion=10;
volatile int timerExpired=0;

struct BenchInfo {
    int speed;
    int failed;
    int bytes;
};

// InitLogger init logger with logPath
bool InitLogger(const std::string &logPath) {
    try {
        auto fileLogger = spdlog::basic_logger_mt("basic_logger", logPath.c_str());
        spdlog::set_default_logger(fileLogger);
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log Init Filed" << std::endl;
        return false;
    }
    return true;
}

#endif // COMMON_H_
