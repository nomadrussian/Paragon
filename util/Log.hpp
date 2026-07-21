#ifndef LOG_HPP
#define LOG_HPP

#include <ctime>
#include <format>
#include <source_location>
#include <string>
#include <string_view>

enum class LogType {
    DEBUG, WARNING, ERROR, FATAL
};

namespace Log
{

void log(std::string_view msg, LogType T, const std::source_location& loc);
std::string localTimeToString(std::time_t t);

#ifdef _WIN32
void initConsoleColors();
#endif

} // namespace Log

#define INTERNAL_LOG_WRITE(logType, ...) \
do { \
    const std::string INTERNAL_FORMATTED_LOG_STRING = std::format(__VA_ARGS__); \
    Log::log(INTERNAL_FORMATTED_LOG_STRING, logType, std::source_location::current()); \
} while(0)

#ifdef PARAGON_DEBUG
// DO NOT USE SIDE-EFFECTS EXPRESSIONS INSIDE, THEY'LL DROP OUT OF RELEASE BUILDS
#define log_debug(...) INTERNAL_LOG_WRITE(LogType::DEBUG, __VA_ARGS__)
#else
#define log_debug(...)
#endif

/* log_warning(...) - program can continue running but something has gone wrong
 * and some functionality might not work as expected */
#define log_warning(...) INTERNAL_LOG_WRITE(LogType::WARNING, __VA_ARGS__)

/* log_error(...) - program cannot continue running normally or it can continue but
 * it is completely broken so there is no meaningful reason to keep running */
#define log_error(...) INTERNAL_LOG_WRITE(LogType::ERROR, __VA_ARGS__)

/* log_fatal(...) - program cannot continue running due to an unrecoverable failure */
#define log_fatal(...) INTERNAL_LOG_WRITE(LogType::FATAL, __VA_ARGS__)

#endif // LOG_HPP
