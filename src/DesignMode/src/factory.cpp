#include "factory.h"


TankFactory::~TankFactory()
{

}

Tank56Factory::~Tank56Factory()
{

}

Tank* Tank56Factory::CreateTank()
{
    return new Tank56();
}

Tank96Factory::~Tank96Factory()
{

}

Tank* Tank96Factory::CreateTank()
{
    return new Tank96();
}

