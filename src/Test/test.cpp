#include "test.h"
#include "std_thread.h"
using namespace std;

CTest::CTest()
{
    m_mapStrAndFun[to_string(Test_Type_Thread_Join)] = &CTest::test_thread_join;
    m_mapStrAndFun[to_string(Test_Type_Thread_Wait)] = &CTest::test_thread_wait;
}

void CTest::Worker()
{
    string strInput;

    while("exit" != strInput)
    {
        cout << "input :[1~" << Test_Type_Max << "):";
        cin >> strInput;
        auto iter = m_mapStrAndFun.find(strInput);

        if(iter != m_mapStrAndFun.end())
        {
            auto pFun = iter->second;
            (this->*pFun)();
        }
        else
        {
            cout << "input illicit!!!!!!!!!!!!\n";
        }
    }
}

void CTest::test_thread_join()
{
    CMyThread oMyThread;
    cout << "test_thread_join" << endl;
    oMyThread.TestJoin();
}

void CTest::test_thread_wait()
{
    CMyThread oMyThread;
    cout << "test_thread_wait" << endl;
    oMyThread.Init();
    string strCmd;

    while("exit" != strCmd)
    {
        cout << "input cmd 1.go 2.exit:" << endl;
        cin >> strCmd;

        if("go" == strCmd)
        {
            oMyThread.Execute();
        }
    }

}