#ifndef SIMULA24_CORE_STL_UTILITY_H_
#define SIMULA24_CORE_STL_UTILITY_H_

#include <type_traits>

namespace stl
{

/// disable qualifier warning
/// irrelavent in this case
#pragma warning(push)
#pragma warning(disable: 4180)

///
/// @brief
///    This was mostly copied from the STL because 
///    it has very little performance over head ( if any)
///    and is really the best way to implement perfect forwarding
///    and movement
/// 
///    @ref remove_reference<T>::type will simply give you the type without 
///    the reference
/// 
///    e.g. remove_reference<const int&>::type = int
/// 
///    This first class exists so the following two can use template specialization
/// 
template <class T>
struct remove_reference
{
    using type = T;
    using const_type = const T;
};

/// deduce type from reference
template <class T>
struct remove_reference<T&>
{
    using type = T;
    using const_type = const T&;
};

/// deduce type from rvalue reference
template <class T>
struct remove_reference<T&&>
{
    using type = T;
    using const_type = const T&&;
};

/// used as a function argument
template <class T>
using remove_reference_t = typename remove_reference<T>::type;

/// end warning disable
#pragma warning(pop)

/// 
/// @brief
///    T& -> T&&
///    Used for perfect forwarding
/// 
template <class T>
constexpr T&& forward(remove_reference_t<T>& arg)
{
    return static_cast<T&&>(arg);
}

template <class T>
constexpr T&& forward(remove_reference_t<T>&& arg)
{
    return static_cast<T&&>(arg);
}


///
/// @brief
///    Used in move semantics
///    Will move stuff
/// 
template <class T>
constexpr typename remove_reference<T>::type&& move(T&& arg)
{
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

template <class T>
constexpr void swap(T& l, T& r)
{
    T temp = l;
    l = r;
    r = temp;
}


} // simula24

#endif // SIMULA24_CORE_STL_UTILITY_H_