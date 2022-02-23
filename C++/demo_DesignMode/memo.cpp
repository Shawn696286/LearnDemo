#include "memo.h"
CMemento::CMemento(SGameValue oValue)
{
    m_oGameValue = oValue;
}

SGameValue CMemento::GetValue()
{
    return m_oGameValue;
}

CGame::CGame(SGameValue oValue)
{
    m_oGameValue = oValue;
}

void CGame::AddGrade()
{
    ++m_oGameValue.nGrade;
}

void CGame::ReplaceArm(string strArm)
{
    m_oGameValue.strArm = strArm;
}

void CGame::ReplaceCorps(string strCorps)
{
    m_oGameValue.strCorps = strCorps;
}

CMemento CGame::SaveValue()
{
    CMemento oMemento(m_oGameValue);
    return oMemento;
}

void CGame::Load(CMemento oMemento)
{
    m_oGameValue = oMemento.GetValue();
}

void CGame::ShowValue()
{
    cout << "Grade:" << m_oGameValue.nGrade << endl;
    cout << "Arm:" << m_oGameValue.strArm << endl;
    cout << "Corps:" << m_oGameValue.strCorps << endl;
}

void CCaretake::Save(CMemento oMemento)
{
    m_oMenento = oMemento;
}

CMemento CCaretake::Load()
{
    return m_oMenento;
}





