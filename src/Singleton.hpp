#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template<typename T>
class Singleton {
public:
    Singleton& operator= (const Singleton&) = delete;
    Singleton& operator= (Singleton&&)      = delete;
    static T& instance(void) {
        static T object;
        return object;
    }
};

#endif
