#pragma once
#include <iostream>
#include <functional>
using namespace std;
/*
    在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。工厂模式作为一种创建模式，一般在创建复杂对象时，考虑使用；
    在创建简单对象时，建议直接new完成一个实例对象的创建。
*/
/*测试简单工厂模式*/
void test_simple_factory_mode();

/*测试工厂模式*/
void test_factory_mode();

/*测试抽象工厂模式*/
void test_abstract_factory_mode();

/*
    策略模式是指定义一系列的算法，把它们单独封装起来，并且使它们可以互相替换，使得算法可以独立于使用它的客户端而变化，也是说这些算法所完成的功能类型是一样的，对外接口也是一样的，
    只是不同的策略为引起环境角色环境角色表现出不同的行为。

    相比于使用大量的if...else，使用策略模式可以降低复杂度，使得代码更容易维护。

    缺点：可能需要定义大量的策略类，并且这些策略类都要提供给客户端。

    [环境角色]  持有一个策略类的引用，最终给客户端调用。
*/
/*测试传统策略模式*/
void test_strategy_mode();

/*测试使用函数指针实现策略模式*/
void test_strategy_by_funcction_mode();