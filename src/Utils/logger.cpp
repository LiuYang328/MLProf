#include "Utils/logger.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

// ANSI 转义序列定义不同颜色
const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_INFO_COLOR = "\033[32m"; // 绿色
const std::string ANSI_WARNING_COLOR = "\033[33m"; // 黄色
const std::string ANSI_ERROR_COLOR = "\033[31m"; // 红色

void myutils::log(LogLevel level, const std::string &message) {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

    const char *level_str;
    std::string color_code;
    switch (level) {
    case LogLevel::INFO:
        level_str = "INFO";
        color_code = ANSI_INFO_COLOR;
        break;
    case LogLevel::WARNING:
        level_str = "WARNING";
        color_code = ANSI_WARNING_COLOR;
        break;
    case LogLevel::ERROR:
        level_str = "ERROR";
        color_code = ANSI_ERROR_COLOR;
        break;
    }

    std::cout << color_code << "[" << ss.str() << "][" << level_str << "] " << message << ANSI_RESET << std::endl;
}    