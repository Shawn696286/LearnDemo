#pragma once
#include <string>
#define LOGY_API

#define LOGY_DEBUG( format, ...) logy_log(__func__, __FILE__, __LINE__, "DEBUG", format, ##__VA_ARGS__)
#define LOGY_INFO( format, ...) logy_log(__func__, __FILE__, __LINE__, "INFO", format, ##__VA_ARGS__)
#define LOGY_WARN( format, ...) logy_log(__func__, __FILE__, __LINE__, "WARN", format, ##__VA_ARGS__)
#define LOGY_ERROR( format, ...) logy_log(__func__, __FILE__, __LINE__, "ERROR", format, ##__VA_ARGS__)


LOGY_API void logy_log(const char* func, const char* file, const int line,
                       const char* type, const char* format, ...);

LOGY_API void logy_set_logfile_path(const std::string& strLogfilePath);