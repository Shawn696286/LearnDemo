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
private:
    Logy();
    ~Logy();
    Logy(const Logy&) = delete;//��ȷ�ܾ�
    Logy& operator=(const Logy&) = delete;//��ȷ�ܾ�

    int WriteFile(std::string strLog);

    std::string GetLocalTime();

private:
    static Logy* m_pSelf;
    std::queue<std::string> m_queLog;
    std::mutex m_oLock;
};