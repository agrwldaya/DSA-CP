#include<iostream>
using namespace std;

// abstract shape class 
class Shape{
    public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

class circle : public Shape{
    double r;
    public:
    circle(double redius):r(redius){};

    double area() override{
        return 3.14*r*r;
    }
};

class rectangle:public Shape{
    double length,width;

    public:
    rectangle(double l,double w):length(l),width(w){};

    double area ()override{
       return length*width;
    }
};

class squre:public Shape{
    int length;
    public:
     squre(int l):length(l){};

     double area() override{
       return length*length;
     }
};
class calculateArea{
    public:
    
    double calculate(Shape* s){
        return s->area();
    } 
};

int main(){
    circle c(5);

    calculateArea res;
    rectangle rec(3,4);
    cout<<res.calculate(&c)<<endl;
    cout<<res.calculate(&rec)<<endl;

    squre s(5);
    cout<<res.calculate(&s)<<endl;
}