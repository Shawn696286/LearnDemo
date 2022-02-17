#pragma once
#include "public.h"
/*
    ���󹤳�ģʽ

    ���󹤳�ģʽ�ṩ����һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ

    �����ڶ����Ʒϵ�У����ͻ���ֻʹ��һ��ϵ�еĲ�Ʒʱ�����Կ���ʹ�ó��󹤳�ģʽ��

    ȱ�㣺������һ����ϵ�еĲ�Ʒʱ��������Ҫ��ʵ����Ĳ�Ʒ�࣬����Ҫ����һ���µĴ����ӿڣ���չ������ѡ�
*/

/*
    �ؼ����룺��һ��������ۺ϶��ͬ���Ʒ��
    ���´����԰�ɫ�·��ͺ�ɫ�·�Ϊ������ɫ�·�Ϊһ����Ʒϵ�У���ɫ�·�Ϊһ����Ʒϵ�С���ɫ���´����ɫ���ӣ�   ��ɫ���´����ɫ���֡�ÿ��ϵ�е��·���һ����Ӧ�Ĺ���������
    ����һ�������������·��ܱ�֤�·�Ϊͬһ��ϵ�С�
*/

//����������
class Coat
{
public:
    virtual ~Coat();
    virtual  const string& Color() = 0;
};

//��ɫ������
class BlackCoat: public  Coat
{
public:
    BlackCoat();
    ~BlackCoat();
    const string& Color() override;
private:
    string m_strColor;
};

//��ɫ������
class WhiteCoat : public  Coat
{
public:
    WhiteCoat();
    ~WhiteCoat();
    const string& Color() override;
private:
    string m_strColor;
};

//���������
class Pants
{
public:
    virtual ~Pants();
    virtual const string& Color() = 0;
};

//��ɫ������
class BlackPants: public  Pants
{
public:
    BlackPants();
    ~BlackPants();
    const string& Color() override;
private:
    string m_strColor;
};

//��ɫ������
class WhitePants : public  Pants
{
public:
    WhitePants();
    ~WhitePants();
    const string& Color() override;
private:
    string m_strColor;
};

//���󹤳��࣬�ṩ�·������ӿ�
class AbstractFactory
{
public:
    //���´����ӿڣ����س���������
    virtual Coat* CreateCoat() = 0;
    //���Ӵ����ӿڣ����س��������
    virtual Pants* CreatePants() = 0;
};

//������ɫ�·��Ĺ����࣬����ʵ�ִ�����ɫ���ºͰ�ɫ���ӽӿ�
class WhiteFactory: public AbstractFactory
{
public:
    Coat* CreateCoat() override;
    Pants* CreatePants() override;
};

//������ɫ�·��Ĺ����࣬����ʵ�ִ�����ɫ���ºͺ�ɫ���ӽӿ�
class BlackFactory : public AbstractFactory
{
public:
    Coat* CreateCoat() override;
    Pants* CreatePants() override;
};
