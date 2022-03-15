// C++.cpp: 定义应用程序的入口点。
//
#include "test.h"
#include <sstream>
#include <iomanip>
#include "logyapi.h"
using namespace std;

int main()
{
    LOGY_DEBUG("test logy\n");
    CTest t;
    t.Worker();
    return 0;
}
