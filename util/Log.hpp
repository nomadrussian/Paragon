#ifdef PARAGON_DEBUG
    #define log_debug(msg) Logger::log(msg, LogType::DEBUG)
#else
    #define log_debug(msg)
#endif

#ifndef LOG_HPP
#define LOG_HPP

#define log_warning(msg) Logger::log(msg, LogType::WARNING)
#define log_error(msg) Logger::log(msg, LogType::ERROR)

#include <iomanip>
#include <string>

enum class LogType {
    DEBUG, WARNING, ERROR
};

namespace Logger
{
    void log(std::string msg, LogType T);
    std::string localTimeToString(const std::tm* t);
}

#endif // LOG_HPP
