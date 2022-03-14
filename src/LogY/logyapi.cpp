#include "logyapi.h"
#include "logy.h"
#include <stdarg.h>

LOGY_API void logy_log(const char* func, const char* file, const int line,
                       const char* type, const char* format, ...)
{
    va_list va;
    va_start(va, format);
    Logy::GetInstance()->logy(func, file, line, type, format, va);
    va_end(va);
}