#include "Visitor.hpp"
#include<iostream>

class A: public Visitable<A> {
};

class B: public Visitable<B> {
};

class C: public Visitable<C> {
};

class ConcreteVisitor: 
    public Visitor<A, B, C> {
public:
    void dispatch(A& a) override { std::cout << "Type A!" << std::endl; }
    void dispatch(B& b) override { std::cout << "Type B!" << std::endl; }
    void dispatch(C& c) override { std::cout << "Type C!" << std::endl; }
};

int main(void) {
    A a;
    B b;
    C c;
    ConcreteVisitor v;

    a.accept(v);
    b.accept(v);
    c.accept(v);
    return 0;
}
