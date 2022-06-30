#pragma once
#include "public.h"

class CMyUseSharedPtr;
class CMySharedThis: public std::enable_shared_from_this<CMySharedThis>
{
public:
    CMySharedThis();
    ~CMySharedThis();
    void Init();
    void Print(std::string strMsg);
    void UnInit();
};

class CMyUseSharedPtr
{
public:
    CMyUseSharedPtr();
    ~CMyUseSharedPtr();
    void SetSharedPtr(std::shared_ptr<CMySharedThis> pPtr);
private:
    std::shared_ptr<CMySharedThis> m_pPtr;
};
