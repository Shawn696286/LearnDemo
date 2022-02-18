// demo_DesignMode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//设计模式
#include <iostream>
#include "public.h"

int main(int argc, char* argv[])
{
    test_init();
    int nInput = 0;

    while(-1 != nInput)
    {
        printf("\n====================================================\n");
        printf("||                                                ||\n");
        printf("||            please input %02d~%d for test         ||\n", Mode_Type_nom + 1, Mode_Type_max - 1);
        printf("||                                                ||\n");

        cin >> nInput;
        auto pFuncTest = g_mapFuncTest[(Mode_Type)nInput];

        if(pFuncTest)
        {
            pFuncTest();
        }
        else
        {
            cout << "input illicit\n";
        }
    }

    return 0;
}
