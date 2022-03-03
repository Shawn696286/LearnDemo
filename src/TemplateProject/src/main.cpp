// C++.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include "test.h"
#include "test2.h"
#include "subdir/test3.h"

using namespace std;

int main()
{
    cout << "Hello CMake." << endl;
    test();
    test2();
    test3();
	system("pause");
    return 0;
}
