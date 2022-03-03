#pragma once
/*
    ����������˼�壬�����򲻵��ѾͲ���ȥʵ�����࣬Ҳ����˵�ڵ�һ���õ���ʵ����ʱ��Ż�ȥʵ����һ�������ڷ�������С���������ܲ���ȥ���ʵ�����£���������ʵ�֣�������ʱ�任�ռ䡣
*/
/*
    �ؼ����룺���캯����˽�еģ�����ͨ����ֵ���㣬��������ȷ�ʽʵ��������
*/

//����ʽһ��ʵ�֣����̰߳�ȫ��getInstance���ص�ʵ��ָ����Ҫdelete
class Singleton
{
public:
    static Singleton* GetInstance();
    ~Singleton() {}
private:
    Singleton() {}//����˽��
    Singleton(const Singleton& obj) = delete;//��ȷ�ܾ�
    Singleton& operator=(const Singleton& obj) = delete;//��ȷ�ܾ�

    static Singleton* m_pSelf;
};
