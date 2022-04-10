#include "logyapi.h"
#include "logy.h"
#include <stdarg.h>
#include <string.h>

static const int LEN_LOG_STR = 4096;
static char g_log_str[LEN_LOG_STR] = { 0 };
static std::mutex g_oLockLogbuf;
LOGY_API void logy_log(const char* func, const char* file, const int line,
                       const char* type, const char* format, ...)
{
    #if 0
    //window平台乱码
    va_list va;
    va_start(va, format);
    Logy::GetInstance()->logy(func, file, line, type, format, va);
    va_end(va);
    #endif

    std::string strLog;
    {
        std::lock_guard<std::mutex> oGuard(g_oLockLogbuf);
        memset(g_log_str, 0, LEN_LOG_STR);

        // 日志内容格式转换
        va_list ap;
        va_start(ap, format);
        vsnprintf(g_log_str, LEN_LOG_STR, format, ap);
        va_end(ap);
        strLog = g_log_str;
    }
    Logy::GetInstance()->logy(func, file, line, type, strLog);
}

LOGY_API void logy_set_logfile_path(const std::string& strLogfilePath)
{
    Logy::GetInstance()->SetLogfilePath(strLogfilePath);
}