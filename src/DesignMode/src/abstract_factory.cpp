#include "abstract_factory.h"
Coat::~Coat()
{

}

BlackCoat::BlackCoat(): Coat()
{
    m_strColor = "Black Coat";
}

BlackCoat::~BlackCoat()
{

}

const string& BlackCoat::Color()
{
    return m_strColor;
}

WhiteCoat::WhiteCoat() : Coat()
{
    m_strColor = "White Coat";
}

WhiteCoat::~WhiteCoat()
{

}

const string& WhiteCoat::Color()
{
    return m_strColor;
}

Pants::~Pants()
{

}

BlackPants::BlackPants()
{
    m_strColor = "Black Pants";
}

BlackPants::~BlackPants()
{

}

const string& BlackPants::Color()
{
    return m_strColor;
}

WhitePants::WhitePants()
{
    m_strColor = "White Pants";
}

WhitePants::~WhitePants()
{

}

const string& WhitePants::Color()
{
    return m_strColor;
}

Coat* WhiteFactory::CreateCoat()
{
    return new WhiteCoat;
}

Pants* WhiteFactory::CreatePants()
{
    return new WhitePants;
}

Coat* BlackFactory::CreateCoat()
{
    return new BlackCoat;
}

Pants* BlackFactory::CreatePants()
{
    return new BlackPants;
}



