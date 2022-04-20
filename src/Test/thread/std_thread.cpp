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
    �������������以����mutex����
    �������е�wait������ʱ������ڴ�������Ȼ���Զ�unlock����ô�����߳����õ����Ժ�ͻ��������У������е�notify_one()������ʱ�򣬾ͻỽ��wait������Ȼ���Զ�lock�����������С�
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
    ��1��std:��thread������ɣ��̹߳���������������
    ��2��thread::join() �����������̣߳�ֱ���߳̽���
    ��3��thread::detach() �����������߳�תΪ��̨����
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