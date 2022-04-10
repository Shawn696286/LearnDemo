#pragma once
#include <string>
#include <queue>
#include <mutex>

class Logy
{
public:
    static Logy* GetInstance();

    void logy(const char* func, const char* file, const int line,
              const char* type, const char* format, ...);
    void logy(const char* func, const char* file, const int line,
              const char* type, const std::string& strLog);

    void SetLogfilePath(const std::string& strLogfilePath);

private:
    Logy();
    ~Logy();
    Logy(const Logy&) = delete;//明确拒绝
    Logy& operator=(const Logy&) = delete;//明确拒绝

    std::string GetLocalTime();

private:
    static Logy* m_pSelf;
    std::queue<std::string> m_queLog;
    std::mutex m_oLock;
};