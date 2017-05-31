#pragma once

/**
 * Placeholder for STL's utility, used for move semantics
 */

// from type_traits
namespace ir {
    template<typename T> struct remove_reference      {using type = T;};
    template<typename T> struct remove_reference<T&>  {using type = T;};
    template<typename T> struct remove_reference<T&&> {using type = T;};
}

namespace ir {
    template<typename T>
    constexpr typename std::remove_reference<T>::type&& move(T&& t) {
        return static_cast<typename std::remove_reference<T>::type&&>(t);
    }

    template<typename T>
    constexpr T&& forward(typename std::remove_reference<T>::type& t) {
        return static_cast<T&&>(t);
    }
    template<typename T>
    constexpr T&& forward(typename std::remove_reference<T>::type&& t) {
        return static_cast<T&&>(t);
    }

    template<typename T>
    void swap(T& a, T& b) {
        T t = move(a);
        a = move(b);
        b = move(t);
    }
}
