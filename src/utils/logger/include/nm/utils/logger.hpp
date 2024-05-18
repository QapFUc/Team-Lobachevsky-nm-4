#pragma once

#include <iostream>

#define C_RESET  "\033[0m"
#define C_YELLOW "\033[33m"
#define C_RED    "\033[31m"
#define C_GREEN  "\033[32m"

inline void printMsg() {}
inline void printMsg(std::ostream& os) {
    os << '\n';
}

template <class First, class... Other>
void printMsg(std::ostream& os, First& first, const Other&... other) {
    os << ':' << first;
    printMsg(os, other...);
}

template <class... Other>
void printMsg(Other&... other) {
    printMsg(std::cout, other...);
}

template <class... Info>
void logger(std::ostream& os, const std::string& logLevel, const Info&... info) {
    std::string color;
    if (logLevel == std::string("INFO")) {
        color = C_GREEN;
    } else if (logLevel == std::string("WARNING")) {
        color = C_YELLOW;
    } else if (logLevel == std::string("ERROR")) {
        color = C_RED;
    } else if (logLevel == std::string("DEBUG")) {
        color = C_GREEN;
    } else {
        color = C_RESET;
    }

    os << '[' << color << logLevel << C_RESET << ']';
    printMsg(os, info...);
}

// Log to console
#define LOG_INFO_CLI(info...)    logger(std::cout, std::string("INFO"), std::string(__FUNCTION__), info)
#define LOG_DEBUG_CLI(info...)   logger(std::cout, std::string("DEBUG"), std::string(__FILE__), std::string(__FUNCTION__), std::to_string(__LINE__), info)
#define LOG_WARNING_CLI(info...) logger(std::cout, std::string("WARNING"), info)
#define LOG_ERROR_CLI(info...)   logger(std::cout, std::string("ERROR"), std::string(__FILE__), std::to_string(__LINE__), info)

// TODO: Log to file using ostream

// errors...
#define NM_ASSERT(_condition_, error_msg)       \
    if (!_condition_) {                         \
        LOG_ERROR_CLI(error_msg, #_condition_); \
        std::runtime_error(error_msg);          \
    }