#include "Log.hpp"

#include <iostream>

std::string sqc_red = "\033[1;31m";
std::string sqc_orange = "\033[38;5;208m";
std::string sqc_reset = "\033[0m";

void Logger::log(const std::string& msg, LogType T)
{
    auto t = std::time(nullptr);
    auto current_t = std::localtime(&t);

    switch (T)
    {
        case LogType::DEBUG:
            std::cout << "| " + localTimeToString(current_t) + " | " + msg << std::endl;
            break;
        case LogType::WARNING:
            std::cerr << "| " + localTimeToString(current_t) + " | " + sqc_orange + "WARNING: " + msg + sqc_reset << std::endl;
            break;
        case LogType::ERROR:
            std::cerr << "| " + localTimeToString(current_t) + " | " + sqc_red + "#ERROR# " + msg + sqc_reset << std::endl;
    }
}

std::string Logger::localTimeToString(const std::tm *t)
{
    std::ostringstream oss;
    oss << std::put_time(t, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
