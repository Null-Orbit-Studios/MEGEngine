#ifndef MEGENGINEPROJECT_LOG_H
#define MEGENGINEPROJECT_LOG_H

#include <string>

#include "MEGEngine/common.h"

#ifndef __FUNCTION_NAME__
    #ifdef _WIN32
        #define __FUNC_NAME__ __FUNCTION__
    #else
        #define __FUNC_NAME__ __func__
    #endif
#endif

enum class ENGINE_API LogLevel {
    DBG,
    INF,
    WRN,
    ERR
};

/** 
 * DEPRECATED - use LOG_DBG, LOG_INF, LOG_WRN, LOG_ERR macros instead
 * i.e. LOG_DBG("Message %i", 1);
 */
void ENGINE_API Log(LogLevel level, const std::string& format, ...);

class ENGINE_API Logger {
public:
    Logger() {}
    ~Logger() {}

    static void log(LogLevel level, const char* filepath, int line, const std::string& function, const std::string& format, ...);

private:
    static const char* get_file_basename(const std::string& filename);
    static const std::string get_log_level_str(LogLevel level);
};

#define LOG_DBG(format, ...) Logger::log(LogLevel::DBG, __FILE__, __LINE__, __FUNC_NAME__, format __VA_OPT__(, __VA_ARGS__))
#define LOG_INF(format, ...) Logger::log(LogLevel::INF, __FILE__, __LINE__, __FUNC_NAME__, format __VA_OPT__(, __VA_ARGS__))
#define LOG_WRN(format, ...) Logger::log(LogLevel::WRN, __FILE__, __LINE__, __FUNC_NAME__, format __VA_OPT__(, __VA_ARGS__))
#define LOG_ERR(format, ...) Logger::log(LogLevel::ERR, __FILE__, __LINE__, __FUNC_NAME__, format __VA_OPT__(, __VA_ARGS__))


#endif //MEGENGINEPROJECT_LOG_H