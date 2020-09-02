/* 
The way this works is that we build up a visitor object one task at a time.
    * The VisitorPolicy<ConcreteTask> template injects a single virtual method into a visitor
      object for each ConcreteTask we wish to be able to visit.
    * The Task template uses CRTP to inject the property of being able to accept a visitor into a given type.
To use this class, one would simply define a collection of Visitable objects like so:

    class A: public Visitable<A> {};
    class B: public Visitable<B> {};

then, we create a concrete visitor class like so:

class ConcreteVisitor: 
    public Visitor<A, B, C> {
public:
    void dispatch(A& a) override { std::cout << "Type A!" << std::endl; }
    void dispatch(B& b) override { std::cout << "Type B!" << std::endl; }
    void dispatch(C& c) override { std::cout << "Type C!" << std::endl; }
};

Easy peasy!
*/

#ifndef VISITOR_HPP
#define VISITOR_HPP

template<typename ConcreteTask>
class VisitorPolicy {
public:
    virtual void dispatch(ConcreteTask&) = 0;
};

template<typename ConcreteTask>
class Visitable {
public:
    void accept(VisitorPolicy<ConcreteTask>& visitor) {
        visitor.dispatch(static_cast<ConcreteTask&>(*this));
    }
};

// Base template
template<typename... Args>
class Visitor;

// TODO: Enforce T is of Visitable type using SFINAE
template<typename T, typename... Args>
class Visitor<T, Args...>:
    public VisitorPolicy<T>,
    public Visitor<Args...> {
};

template<>
class Visitor<> {
public:
    virtual ~Visitor<>(void) {}
};

#endif
