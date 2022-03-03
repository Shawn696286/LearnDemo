#include "prototype.h"

CSheep::CSheep(int nId, string strName)
{
    m_nId = nId;
    m_strName = strName;
}

IClone* CSheep::Clone()
{
    return new CSheep(*this);
}

void CSheep::Show()
{
    cout << "id:" << m_nId << endl;
    cout << "name:" << m_strName.data() << endl;
}

