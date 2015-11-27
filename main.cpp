#include <iostream>

using namespace std;

#include "test_loc1.h"

#include "ioc_container.h"
#include "Ioc_Container1.h"
#include "Ioc_Container2.h"
struct ICar
{
    virtual ~ICar() {}
    virtual void test() const = 0;
};

struct Bus : ICar
{
    Bus() {}
    void test() const { std::cout << "Bus::test()" << endl;}
};

struct Car : ICar
{
    Car() {}
    void test() const { std::cout << "Car::test()" << endl;}
};

void test_ioc()
{
    Ioc_Container<ICar> car_ioc;
    car_ioc.register_type<Bus>("bus");
    car_ioc.register_type<Car>("car");

    std::shared_ptr<ICar> bus = car_ioc.resolve_shared("bus");
    bus->test();

    std::shared_ptr<ICar> car = car_ioc.resolve_shared("car");
    car->test();
    return;
}

void test_ioc1()
{
    Ioc_Container1 ioc;
    ioc.register_type<A, DerivedB>("B");
    ioc.register_type<A, DerivedC>("C");
    ioc.register_type<A, DerivedD>("D");

    auto pa = ioc.resolve_shared<A>("B");
    pa->func();

    auto pc = ioc.resolve_shared<A>("C");
    pc->func();
#if 0
    ioc.register_type<Bus>("bus");
    ioc.register_type<Car>("car");

    auto bus = ioc.resolve_shared<Bus>("bus");
    bus->test();

    auto car = ioc.resolve_shared<Car>("car");
    car->test();
#endif
}

void test_ioc2()
{
    cout << "test_ioc2() " << endl;
    Ioc_Container2 ioc;
    ioc.register_type<A,DerivedC>("c");
    auto c = ioc.resolve_shared<A>("c");

    ioc.register_type<A, DerivedE, int, double>("E");
    auto e = ioc.resolve_shared<A>("E", 1, 2.0);
    e->func();
}

void test_loc1()
{
    A* a = new A(new DerivedB());
    a->func();
    delete a;
    return;
}

int main()
{
    test_ioc2();
    cout << "Hello World!" << endl;
    return 0;
}

