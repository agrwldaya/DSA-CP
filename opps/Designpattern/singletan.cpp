#include<bits/stdc++.h>
using namespace std;

class singleton{
    static singleton* instance;
    singleton(){
        cout<<"Instance created: "<<endl;
    }
    public:

    static singleton* getInstance(){
        return instance;
    }
    
};
singleton* singleton::instance=new singleton();

int main(){
    singleton* a = singleton::getInstance();
    singleton* b = singleton::getInstance();

    cout<<(a==b)<<" ";
}


///