#pragma once
/*
    ���������˿϶�Ҫ������ʳ�������ڵ����ඨ���ʱ��ͽ���ʵ�������ڷ������Ƚϴ󣬻��߿��ܷ��ʵ��̱߳Ƚ϶�ʱ�����ö���ʵ�֣�����ʵ�ָ��õ����ܡ������Կռ任ʱ�䡣
*/
class SingletonHungry
{
public:
    static SingletonHungry* GetInstance();
private:
    SingletonHungry() {}//���캯��˽��
    SingletonHungry(const SingletonHungry&) = delete;//��ȷ�ܾ�
    SingletonHungry& operator=(const SingletonHungry&) = delete;//��ȷ�ܾ�
    static SingletonHungry* m_pSelf;
};

