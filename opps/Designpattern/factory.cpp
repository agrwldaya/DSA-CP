#include <bits/stdc++.h>
using namespace std;

// Base class
class burger {
public:
    virtual void prepare() = 0;
    virtual ~burger() {}
};

// Derived burger types
class basicBurger : public burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger\n";
    }
};

class standardBurger : public burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger\n";
    }
};

class premiumBurger : public burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger\n";
    }
};

// Factory
class burgerFactory {
public:
    static unique_ptr<burger> createBurgerObject(const string& type) {
        if (type == "Basic") {
            return make_unique<basicBurger>();
        } 
        else if (type == "Standard") {
            return make_unique<standardBurger>();
        } 
        else if (type == "Premium") {
            return make_unique<premiumBurger>();
        } 
        else {
            cout << "Invalid burger type\n";
            return nullptr;
        }
    }
};

// Main function
int main() {
    string type = "Basic";

    auto myBurger = burgerFactory::createBurgerObject(type);

    if (myBurger) {
        myBurger->prepare();
    }

    return 0;
}
