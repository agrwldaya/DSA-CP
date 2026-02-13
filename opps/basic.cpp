#include<iostream>
using namespace std;

class A{
    public:
    A(){
        cout<<"Constractor of A is called"<<endl;
    }
    void MethodA(){
        cout<<"Method A called"<<endl;
    }
    ~A(){
        cout<<"Distuctor of A is called"<<endl;
    }
};


class B{
    public:
     A* a;
    B(){
        a = new A();
        cout<<"Constractor of B is called"<<endl;
    }
    void MethodB(){
        cout<<"Method B called"<<endl;
    }

    ~B(){
        cout<<"Distructor of B is called"<<endl;
    }

};

int main(){
    B b;
    b.a->MethodA()
}

