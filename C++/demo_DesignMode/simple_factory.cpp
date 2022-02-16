#include "simple_factory.h"

Tank::~Tank()
{

}

Tank56::Tank56() : Tank()
{
    m_strType = "Tank56";
    cout << "create Tank56" << endl;
}

Tank56::~Tank56()
{
    cout << "destroy Tank56" << endl;
}

const string& Tank56::Type()
{
    return m_strType;
}


Tank96::Tank96() : Tank()
{
    m_strType = "Tank96";
    cout << "create Tank56" << endl;
}

Tank96::~Tank96()
{
    cout << "destroy Tank56" << endl;
}

const string& Tank96::Type()
{
    return m_strType;
}

Tank* SimpleTankFactory::CreateTank(Tank_Type type)
{
    switch(type)
    {
        case Tank_Type_56:
            return new Tank56();

        case Tank_Type_96:
            return new Tank96();

        default:
            return nullptr;
    }
}


