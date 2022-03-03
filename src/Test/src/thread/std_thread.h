#include "public.h"
class CMyThread
{
public:
    //< ��ʼ��
    void Init();

    //< ����ִ��
    void Execute();

    //< ����std::thread.join
    void TestJoin();

private:
    //< ��������
    void OnWorker();

    //< ����std::thread.join����������
    void my_printf(std::string msg);

private:
    //< ���廷������
    std::condition_variable      m_oCondVar;

    //< ���幤���߳�
    std::unique_ptr<std::thread> m_pWorker;

    //< ���廥����
    std::mutex                   m_oLock;

    //< ����std::thread.join���ź���
    bool                        m_bRuning;
};
