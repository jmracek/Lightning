#ifndef TYPELIST_HPP
#define TYPELIST_HPP

template<typename Args...>
class TypeList;

template<typename H, typename... Rest>
class TypeList<H, Rest...> {
    using Head = H;
    using Tail = TypeList<Rest...>;
};

template<typename T>
class TypeList<T> {
    using Head = H;
    using Tail = NullType;
};

template<>
class TypeList<> {
    using Head = NullType;
    using Tail = NullType;
};

template<typename H, typename... Args>
struct Length<TypeList<T, Args...>> {
    static constexpr value = Length<TypeList<Args...>> + 1;
};

template<>
struct Length<TypeList<>> {
    static constexpr value = 0;
};

#endif
