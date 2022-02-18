#pragma once
#include <iostream>
#include <functional>
#include <map>
using namespace std;

/*初始化test*/
void test_init();

enum Mode_Type
{
    Mode_Type_nom = 0,
    Mode_Type_simple_factory,/*简单工厂模式*/
    Mode_Type_factory,/*工厂方法模式*/
    Mode_Type_abstract_factory,/*抽象工厂模式*/
    Mode_Type_strategy_mode,/*传统策略模式*/
    Mode_Type_strategy_by_funcction,/*使用函数指针实现策略模式*/
    Mode_Type_adapter_comb,/*组合适配器模式*/
    Mode_Type_adapter_derive,/*继承适配器模式*/
    Mode_Type_singleton_lazy_notsafe,/*懒汉单例模式(线程不安全)*/
    Mode_Type_singleton_lazy_safe,/*懒汉单例模式(线程安全)*/
    Mode_Type_singleton_lazy_reference_nosafe,/*懒汉单例模式(返回引用，线程不安全，不用delete)*/
    Mode_Type_singleton_hungry_safe,/*饿汉单例模式(线程安全)*/
    Mode_Type_prototype,/*原型模式*/
    Mode_Type_template,/*模板模式*/
    Mode_Type_builder,/*建造者模式*/
    Mode_Type_facade,/*外观模式*/
    Mode_Type_composite,/*组合模式*/
    Mode_Type_agency,/*代理模式*/
    Mode_Type_flyweight,/*享元模式*/
    Mode_Type_bridge,/*桥接模式*/
    Mode_Type_decorative,/*装饰模式*/
    Mode_Type_memo,/*备忘录模式*/
    Mode_Type_mediator,/*中介者模式*/
    Mode_Type_chain_of_responsibility_mode,/*责任链模式*/
    Mode_Type_observer,/*观察者模式*/
    Mode_Type_max,
};
/*
    在工厂模式中，我们在创建对象时不会对客户端暴露创建逻辑，并且是通过使用一个共同的接口来指向新创建的对象。工厂模式作为一种创建模式，一般在创建复杂对象时，考虑使用；
    在创建简单对象时，建议直接new完成一个实例对象的创建。
*/
/*测试简单工厂模式*/
void test_simple_factory_mode();

/*测试工厂方法模式*/
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

/*
    适配器模式可以将一个类的接口转换成客户端希望的另一个接口，使得原来由于接口不兼容而不能在一起工作的那些类可以在一起工作。通俗的讲就是当我们已经有了一些类，而这些类不能满足新的需求，
    此时就可以考虑是否能将现有的类适配成可以满足新需求的类。适配器类需要继承或依赖已有的类，实现想要的目标接口。

    缺点：过多地使用适配器，会让系统非常零乱，不易整体进行把握。比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现，一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，
    可以不使用适配器，而是直接对系统进行重构。
*/
/*测试组合适配器模式*/
void test_adapter_comb_mode();

/*测试继承适配器模式*/
void test_adapter_derive_mode();

/*
    单例模式顾名思义，保证一个类仅可以有一个实例化对象，并且提供一个可以访问它的全局接口。实现单例模式必须注意一下几点：

    单例类只能由一个实例化对象。

    单例类必须自己提供一个实例化对象。

    单例类必须提供一个可以访问唯一实例化对象的接口。

    单例模式分为懒汉和饿汉两种实现方式。
*/
/*测试懒汉单例模式(线程不安全)*/
void test_singleton_lazy_notsafe_mode();

/*测试懒汉单例模式(线程安全)*/
void test_singleton_lazy_safe_mode();

/*测试懒汉单例模式(返回引用，线程不安全，不用delete)*/
void test_singleton_lazy_reference_nosafe_mode();

/*测试饿汉单例模式(线程安全)*/
void test_singleton_hungry_safe_mode();

/*
    原型模式：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。通俗的讲就是当需要创建一个新的实例化对象时，我们刚好有一个实例化对象，但是已经存在的实例化对象又不能直接使用。
    这种情况下拷贝一个现有的实例化对象来用，可能会更方便。

    以下情形可以考虑使用原型模式：

    当new一个对象，非常繁琐复杂时，可以使用原型模式来进行复制一个对象。比如创建对象时，构造函数的参数很多，而自己又不完全的知道每个参数的意义，就可以使用原型模式来创建一个新的对象，不必去理会创建的过程。

    当需要new一个新的对象，这个对象和现有的对象区别不大，我们就可以直接复制一个已有的对象，然后稍加修改。

    当需要一个对象副本时，比如需要提供对象的数据，同时又需要避免外部对数据对象进行修改，那就拷贝一个对象副本供外部使用。
*/
/*测试原型模式*/
void test_prototype_mode();

/*
    模板模式：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

    当多个类有相同的方法，并且逻辑相同，只是细节上有差异时，可以考虑使用模板模式。具体的实现上可以将相同的核心算法设计为模板方法，具体的实现细节有子类实现。

    缺点:每一个不同的实现都需要一个子类来实现，导致类的个数增加，使得系统更加庞大。

    以生产电脑为例，电脑生产的过程都是一样的，只是一些装配的器件可能不同而已。
*/
/*测试模板模式*/
void test_template_mode();

/*
    建造者模式：将复杂对象的构建和其表示分离，使得相同的构建过程可以产生不同的表示。

    以下情形可以考虑使用建造者模式：

    对象的创建复杂，但是其各个部分的子对象创建算法一定。

    需求变化大，构造复杂对象的子对象经常变化，但将其组合在一起的算法相对稳定。

    建造者模式的优点：

    将对象的创建和表示分离，客户端不需要了解具体的构建细节。

    增加新的产品对象时，只需要增加其具体的建造类即可，不需要修改原来的代码，扩展方便。

    产品之间差异性大，内部变化较大、较复杂时不建议使用建造者模式。
*/
/*测试建造者模式*/
void test_builder_mode();

/*
    外观模式：为子系统中的一组接口定义一个一致的界面；外观模式提供一个高层的接口，这个接口使得这一子系统更加容易被使用；对于复杂的系统，系统为客户端提供一个简单的接口，把负责的实现过程封装起来，
    客户端不需要连接系统内部的细节。

    以下情形建议考虑外观模式：

    设计初期阶段，应有意识的将不同层分离，层与层之间建立外观模式。

    开发阶段，子系统越来越复杂，使用外观模式提供一个简单的调用接口。

    一个系统可能已经非常难易维护和扩展，但又包含了非常重要的功能，可以为其开发一个外观类，使得新系统可以方便的与其交互。

    优点：

    实现了子系统与客户端之间的松耦合关系。

    客户端屏蔽了子系统组件，减少了客户端所需要处理的对象数据，使得子系统使用起来更方便容易。

    更好的划分了设计层次，对于后期维护更加的容易。
*/
/*测试外观模式*/
void test_facade_mode();

/*
    组合模式：将对象组合成树形结构以表示“部分-整体”的层次结构，组合模式使得客户端对单个对象和组合对象的使用具有一直性。

    既然讲到以树形结构表示“部分-整体”，那可以将组合模式想象成一根大树，将大树分成树枝和树叶两部分，树枝上可以再长树枝，也可以长树叶，树叶上则不能再长出别的东西。

    以下情况可以考虑使用组合模式：

    希望表示对象的部分-整体层次结构。

    希望客户端忽略组合对象与单个对象的不同，客户端将统一的使用组合结构中的所有对象。
*/
/*测试组合模式*/
void test_composite_mode();

/*
    代理模式：为其它对象提供一种代理以控制这个对象的访问。在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介作用。

    优点：

    职责清晰。真实的角色只负责实现实际的业务逻辑，不用关心其它非本职责的事务，通过后期的代理完成具体的任务。这样代码会简洁清晰。

    代理对象可以在客户端和目标对象之间起到中介的作用，这样就保护了目标对象。

    扩展性好。
*/
/*测试代理模式*/
void test_agency_mode();

/*
    享元模式：运用共享技术有效地支持大量细粒度的对象。在有大量对象时，把其中共同的部分抽象出来，如果有相同的业务请求，直接返回内存中已有的对象，避免重新创建。

    以下情况可以考虑使用享元模式：

    系统中有大量的对象，这些对象消耗大量的内存，且这些对象的状态可以被外部化。

    对于享元模式，需要将对象的信息分为两个部分：内部状态和外部状态。内部状态是指被共享出来的信息，储存在享元对象内部且不随环境变化而改变；外部状态是不可以共享的，它随环境改变而改变，是由客户端控制的。
*/
/*测试享元模式*/
void test_flyweight_mode();

/*
    桥接模式：将抽象部分与实现部分分离，使它们都可以独立变换。

    以下情形考虑使用桥接模式：

    当一个对象有多个变化因素的时候，考虑依赖于抽象的实现，而不是具体的实现。

    当多个变化因素在多个对象间共享时，考虑将这部分变化的部分抽象出来再聚合/合成进来。

    当一个对象的多个变化因素可以动态变化的时候。

    优点：

    将实现抽离出来，再实现抽象，使得对象的具体实现依赖于抽象，满足了依赖倒转原则。

    更好的可扩展性。

    可动态的切换实现。桥接模式实现了抽象和实现的分离，在实现桥接模式时，就可以实现动态的选择具体的实现。
*/
/*测试桥接模式*/
void test_bridge_mode();

/*
    装饰模式：动态地给一个对象添加一些额外的功能，它是通过创建一个包装对象，也就是装饰来包裹真实的对象。新增加功能来说，装饰器模式比生产子类更加灵活。

    以下情形考虑使用装饰模式：

    需要扩展一个类的功能，或给一个类添加附加职责。

    需要动态的给一个对象添加功能，这些功能可以再动态的撤销。

    需要增加由一些基本功能的排列组合而产生的非常大量的功能，从而使继承关系变的不现实。

    当不能采用生成子类的方法进行扩充时。一种情况是，可能有大量独立的扩展，为支持每一种组合将产生大量的子类，使得子类数目呈爆炸性增长。另一种情况可能是因为类定义被隐藏，或类定义不能用于生成子类。
*/
/*测试装饰模式*/
void test_decorative_mode();

/*
    备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原来保存的状态。

    备忘录模式中需要定义的角色类：

    1.Originator(发起人)：负责创建一个备忘录Memento，用以记录当前时刻自身的内部状态，并可使用备忘录恢复内部状态。Originator可以根据需要决定Memento存储自己的哪些内部状态。

    2.Memento(备忘录)：负责存储Originator对象的内部状态，并可以防止Originator以外的其他对象访问备忘录。备忘录有两个接口：Caretaker只能看到备忘录的窄接口，他只能将备忘录传递给其他对象。
    Originator却可看到备忘录的宽接口，允许它访问返回到先前状态所需要的所有数据。

    3.Caretaker(管理者):负责备忘录Memento，不能对Memento的内容进行访问或者操作。
*/
/*测试备忘录模式*/
void test_memo_mode();

/*
    中介者模式：用一个中介对象来封装一系列的对象交互，中介者使各对象不需要显示地相互引用，从而使其耦合松散，而且可以独立地改变它们之前的交互。

    如果对象与对象之前存在大量的关联关系，若一个对象改变，常常需要跟踪与之关联的对象，并做出相应的处理，这样势必会造成系统变得复杂，遇到这种情形可以考虑使用中介者模式。当多个对象存在关联关系时，
    为它们设计一个中介对象，当一个对象改变时，只需要通知它的中介对象，再由它的中介对象通知每个与它相关的对象。
*/
/*测试中介者模式*/
void test_mediator_mode();

/*
    职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之前的耦合关系，将这些对象连成一条链，并沿着这条链传递请求，直到有一个对象处理它为止。

    职责链上的处理者负责处理请求，客户只需要将请求发送到职责链上即可，无需关心请求的处理细节和请求的传递，所有职责链将请求的发送者和请求的处理者解耦了。
*/
/*测试责任链模式*/
void test_chain_of_responsibility_mode();

/*
    观察者模式：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都要得到通知并自动更新。

    观察者模式从根本上讲必须包含两个角色：观察者和被观察对象。

    被观察对象自身应该包含一个容器来存放观察者对象，当被观察者自身发生改变时通知容器内所有的观察者对象自动更新。

    观察者对象可以注册到被观察者的中，完成注册后可以检测被观察者的变化，接收被观察者的通知。当然观察者也可以被注销掉，停止对被观察者的监控。
*/
/*测试观察者模式*/
void test_observer_mode();


typedef void(*FuncTest)();
extern map<Mode_Type, FuncTest> g_mapFuncTest;