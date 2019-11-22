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


