#include <iostream>

using namespace std;

class A
{
    public:
    A()
    {
        cout << " A()" << endl;
    }
    A(A&)
    {
        cout << " A(&A)" << endl;
    }

    virtual ~A() {
        cout << " ~A()" << endl;
    }

    A& operator=(A&)
    {
        cout << "op=(A&)" << endl;
        return *this;
    }

};

class B : public A
{
    public:
    B()
    {
        cout << " B()" << endl;
    }
    B(B&)
    {
        cout << " B(&B)" << endl;
    }

    virtual ~B() {
        cout << " ~B()" << endl;
    }

    B& operator=(B&)
    {
        cout << "op=(B&)" << endl;
        return *this;
    }

};

void f(A b){
    cout << "f(A)" << endl;
}

int main()
{
    cout << "------------" << endl;
    B d;
    cout << "------------" << endl;
    B copy = d;
    cout << "------------" << endl;
    A b = d;
    cout << "------------" << endl;
    A& ref = d;
    cout << "------------" << endl;
    B arr[2];
    cout << "------------" << endl;
    f(d);
    cout << "------------" << endl;
    A* p = new B(d);
    cout << "------------" << endl;
    delete p;
    cout << "------------" << endl;
    d = d;
    cout << "------------" << endl;
    ref = d;
    cout << "------------" << endl;
    return 0;
}