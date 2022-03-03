#include "public.h"
class CMyThread
{
public:
    //< 初始化
    void Init();

    //< 启动执行
    void Execute();

    //< 测试std::thread.join
    void TestJoin();

private:
    //< 工作函数
    void OnWorker();

    //< 测试std::thread.join，工作函数
    void my_printf(std::string msg);

private:
    //< 定义环境变量
    std::condition_variable      m_oCondVar;

    //< 定义工作线程
    std::unique_ptr<std::thread> m_pWorker;

    //< 定义互斥锁
    std::mutex                   m_oLock;

    //< 测试std::thread.join，信号量
    bool                        m_bRuning;
};
