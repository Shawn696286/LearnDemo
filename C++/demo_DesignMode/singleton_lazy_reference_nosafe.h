#pragma once
/*
    ���ֵ���ģʽʵ�ַ�ʽ���߳̿��ܴ��ڲ�ȷ���ԣ��κ�һ��non-const static���󣬲�������local��non-local,�ڶ��̻߳����¡��ȴ�ĳ�·������������鷳��
    ����ķ������ڳ���ĵ��߳������׶��ֹ���������reference-returning����������ʵ�ַ�ʽ�ĺô��ǲ���Ҫȥdelete����
*/
class SingletonEx2
{
public:
    static SingletonEx2& GetInstance();
private:
    SingletonEx2() {}
    SingletonEx2(const SingletonEx2&) = delete;  //��ȷ�ܾ�
    SingletonEx2& operator=(const SingletonEx2&) = delete; //��ȷ�ܾ�
};


