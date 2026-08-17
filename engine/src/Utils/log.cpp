#include <cstdarg>
#include <iostream>
#include <sstream>
#include <chrono>

#include "MEGEngine/Utils/log.h"

#ifdef __linux // _vscprintf is a windows function, not available on linux so defined here
int _vscprintf (const char * format, va_list pargs) {
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}
#endif


void Log(LogLevel level, const std::string& format, ...) {
    va_list args;
    int len;
    char* buffer;

    va_start(args, format);
    len = _vscprintf(format.c_str(), args) + 1;
    buffer = (char*) malloc(len * sizeof(char));
    vsprintf(buffer, format.c_str(), args);
    std::string msg = buffer;

    free(buffer);

    std::string levelStr;
    switch (level) {
        case LogLevel::DBG:
            levelStr = "DBG";
#ifndef DEBUG // only log this in debug builds
            return;
#endif
            break;
        case LogLevel::INF:
            levelStr = "INF";
            break;
        case LogLevel::WRN:
            levelStr = "WRN";
            break;
        case LogLevel::ERR:
            levelStr = "\033[31mERR\033[0m"; // colour codes for when displayed in terminal
            break;
    }
    #ifdef DEBUG
    //TODO: display logs to the game screen
    #endif
    auto time = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now());
    auto formattedTime = std::format("{:%T}", time);
    std::cout << formattedTime << " [" << levelStr << "]: " << msg << std::endl;
}

const char* Logger::get_file_basename(const std::string& filename) {
    size_t pos = filename.find_last_of("/\\");

    if (pos != std::string::npos && pos + 1 < filename.size()) {
        return filename.c_str() + pos + 1;
    }

    return filename.c_str();
}

const std::string Logger::get_log_level_str(LogLevel level) {
    std::string levelStr;
    switch (level) {
        case LogLevel::DBG:
            levelStr = "DBG";
            break;
        case LogLevel::INF:
            levelStr = "INF";
            break;
        case LogLevel::WRN:
            levelStr = "WRN";
            break;
        case LogLevel::ERR:
            levelStr = "\033[31mERR\033[0m"; // colour codes for when displayed in terminal
            break;
    }

    return levelStr;
}

void Logger::log(LogLevel level, const char* filepath, int line, const std::string& function, const std::string& format, ...) {
    va_list args;
    int len;
    char* buffer;

    #ifndef DEBUG
    if (level == LogLevel::DBG) return; // dont log debug when not in debug mode
    #endif

    va_start(args, format);
    len = _vscprintf(format.c_str(), args) + 1;
    buffer = (char*) malloc(len * sizeof(char));
    vsprintf(buffer, format.c_str(), args);
    std::string msg = buffer;

    free(buffer);

    std::string levelStr = get_log_level_str(level);

    auto time = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now());
    auto formattedTime = std::format("{:%T}", time);

    std::string file = get_file_basename(filepath);

    std::stringstream formattedMsg;
    formattedMsg << formattedTime << " [" << levelStr << "] [" << file + ":" << line << "] [" << function << "]: " << msg;

    std::cout << formattedMsg.str() << std::endl;

    //TODO: display logs to the game screen
}

