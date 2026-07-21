#include "Log.hpp"

#include <iostream>

inline constexpr std::string_view sqc_veryRed = "\033[1;38;5;196m";
inline constexpr std::string_view sqc_red = "\033[1;31m";
inline constexpr std::string_view sqc_orange = "\033[38;5;208m";
inline constexpr std::string_view sqc_reset = "\033[0m";

void Log::log(std::string_view msg, LogType T, const std::source_location& loc)
{
    const auto time = std::time(nullptr);

    switch (T)
    {
        case LogType::DEBUG:
        std::cout << "| " << localTimeToString(time) << " | " << msg << '\n';
            break;
        case LogType::WARNING:
            std::cerr << "| " << localTimeToString(time) << " | " << sqc_orange << "WARNING: " << msg << sqc_reset << '\n';
            break;
        case LogType::ERROR:
            std::cerr << "| " << localTimeToString(time) << " | " << sqc_red << "#ERROR# " << msg << sqc_reset << " [" << loc.file_name() << "|line:" << loc.line() << " (" << loc.function_name() << ")]" << '\n';
            break;
        case LogType::FATAL:
            std::cerr << "| " << localTimeToString(time) << " | " << sqc_veryRed << "###FATAL### " << msg << sqc_reset << " [" << loc.file_name() << "|line:" << loc.line() << " (" << loc.function_name() << ")]" << '\n';
            break;
    }
}

std::string Log::localTimeToString(std::time_t t)
{
    constexpr std::string_view invalidTime = "[INVALID TIME]";
    std::tm currentTime{};

#ifdef _WIN32
    if (localtime_s(&currentTime, &t) != 0)
    {
        return std::string(invalidTime);
    }
#else
    if (localtime_r(&t, &currentTime) == nullptr)
    {
        return std::string(invalidTime);
    }
#endif

    return std::format("{:%Y-%m-%d %H:%M:%S}", currentTime);
}

#ifdef _WIN32
#include <windows.h>

void Log::initConsoleColors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
    {
        return; // No console attached - silently skip
    }

    DWORD mode = 0;

    if (!GetConsoleMode(hOut, &mode))
    {
        return;
    }

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode); // Ignore failure - colors not showing is not fatal
}
#endif
