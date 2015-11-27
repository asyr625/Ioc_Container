#ifndef TEST_LOC1_H
#define TEST_LOC1_H

#include <iostream>
using namespace std;

struct Base
{
    virtual void func() {}
    virtual ~Base() {}
};


struct DerivedB : Base
{
    void func() override
    {
        cout << "call func in DerivedB" <<endl;
    }
};

struct DerivedC : Base
{
    void func() override
    {
        cout << "call func in DerivedC" <<endl;
    }
};

struct DerivedD : Base
{
    void func() override
    {
        cout << "call func in DerivedD" <<endl;
    }
};

struct DerivedE : Base
{
    DerivedE(int a, double b)
        : m_a(a),
          m_b(b)
    {
    }

    void func() override
    {
        cout << "DerivedE func(): " << m_a + m_b << endl;
    }

private:
    int m_a;
    double m_b;
};


class A
{
public:
    A(Base* interfaceB)
        : m_interfaceB(interfaceB)
    {
    }

    void func()
    {
        m_interfaceB->func();
    }
    ~A()
    {
        if( m_interfaceB != nullptr )
        {
            delete m_interfaceB;
            m_interfaceB = nullptr;
        }
    }

private:
    Base* m_interfaceB;
};


#endif // TEST_LOC1_H
