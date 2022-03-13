// C++.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include "test.h"
#include "test2.h"
#include "subdir/test3.h"

#ifdef _WIN32
#else
    #include <unistd.h>
#endif // WIN32


using namespace std;

int main()
{
    cout << "Hello CMake." << endl;
    test();
    test2();
    test3();
    #ifdef _WIN32
    system("pause");
    #else
    pause();
    #endif // WIN32

    return 0;
}
