#include "std_thread.h"

using namespace std;

void CMyThread::Init()
{
    m_pWorker = std::make_unique<std::thread>(&CMyThread::OnWorker, this);
}

void CMyThread::Execute()
{
    m_oCondVar.notify_one();
    m_pWorker->join();
}

/*
    条件变量，搭配互斥量mutex来用
    程序运行到wait函数的时候会先在此阻塞，然后自动unlock，那么其他线程在拿到锁以后就会往下运行，当运行到notify_one()函数的时候，就会唤醒wait函数，然后自动lock并继续下运行。
*/
void CMyThread::OnWorker()
{
    {
        std::unique_lock<std::mutex> oGuard(m_oLock);
        std::cout << "OnWorker wait..." << std::endl;
        m_oCondVar.wait(oGuard);
    }
    std::cout << "OnWorker run..." << std::endl;
}

/*
    （1）std:：thread构造完成，线程工作函数立即运行
    （2）thread::join() 会阻塞调用线程，直至线程结束
    （3）thread::detach() 不会阻塞，线程转为后台运行
*/
void CMyThread::TestJoin()
{
    std::thread t(&CMyThread::my_printf, this, "join");
    string strInput;

    while("break" != strInput)
    {
        cout << "please input 1.join 2.break 3.stop:\n";
        cin >> strInput;

        if("join" == strInput)
        {
            if(t.joinable())
            {
                t.join();
            }
        }
        else if("stop" == strInput)
        {
            m_bRuning = false;
        }
        else if("break" == strInput)
        {
            m_bRuning = false;

            if(t.joinable())
            {
                t.join();
            }
        }
        else
        {
            cout << "input :" << strInput;
        }
    }
}

void CMyThread::my_printf(string msg)
{
    int n = 0;

    while(m_bRuning)
    {
        cout << "this is thread ,msg:" << msg << ",count:" << ++n << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << "thread exit\n";
}