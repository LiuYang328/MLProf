#ifndef MLIRPROFILER_LOGGER_H
#define MLIRPROFILER_LOGGER_H

#include <string>


namespace myutils {
// 日志级别枚举
enum class LogLevel { INFO, WARNING, ERROR };

// 日志输出函数
void log(LogLevel level, const std::string &message);

} // namespace utils


#endif