#include <iostream>
class B {
public:
    int x_;
    B(void) {}
    B(int x): x_(x) {}
    B(const B& b) {x_ = b.x_;}
};

class C {
public:
    int y_;
    C(void) {}
    C(int y): y_(y) {}
    C(const C& c) {y_ = c.y_;}
};

class A: public B, public C {
public:
    A(B b, C c) {
        B* test = static_cast<B*>(this);
        *test = b;
        C* test2 = static_cast<C*>(this);
        *test2 = c;
    }
};

int main(void) {
    C c(10);
    B b(-5);
    A a(b, c);
    std::cout << a.x_ << " " << a.y_ << std::endl;
}
