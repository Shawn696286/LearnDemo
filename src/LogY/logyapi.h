#pragma once

#define LOGY_API

#define Y_LOG_DEBUG( format, ...) logy_log(__func__, __FILE__, __LINE__, "DEBUG", format, ##__VA_ARGS__)
#define Y_LOG_INFO( format, ...) logy_log(__func__, __FILE__, __LINE__, "INFO", format, ##__VA_ARGS__)
#define Y_LOG_WARN( format, ...) logy_log(__func__, __FILE__, __LINE__, "WARN", format, ##__VA_ARGS__)
#define Y_LOG_ERROR( format, ...) logy_log(__func__, __FILE__, __LINE__, "ERROR", format, ##__VA_ARGS__)


LOGY_API void logy_log(const char* func, const char* file, const int line,
                       const char* type, const char* format, ...);