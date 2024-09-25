#ifndef SIMULA24_CORE_STL_VARIANT_H_
#define SIMULA24_CORE_STL_VARIANT_H_

#include <type_traits>
#include <simula24/core/stl/utility.h>
namespace simula24
{

template <typename... Types>
struct typelist {};


template <typename T, typename Type>
struct contains {};

/// @brief test if a typelist contains a type
template <typename T, typename...Types>
struct contains <T, typelist<Types...> >
{
    static constexpr bool value = (std::is_same_v<T, Types> || ...);
};

template <typename T, typename TypesList>
constexpr bool contains_v = contains<T, TypesList>::value;

///
/// @brief 
///     template parameter to determine whether a typelist contains a type or not
///     This is mainly here to improve readability 
template <class T, typename Types>
constexpr std::enable_if_t<contains_v<T, Types>, bool> typelist_contains()
{
    return true;
}


template <typename... Types>
class variant;


///
/// @brief 
///     Variant, holds @Types types in a union
///     Each of these functions is only enabled if the 
///     type passed to it is contained in the typelist.
///     see @ref typelist_contains
/// 
template <typename... Types>
class variant<typelist<Types...> >
{
public:

    variant() : m_idx(0) {}
    ///
    /// @brief 
    ///     Set the value to 'val'
    template <typename T,
        bool = typelist_contains<T, typelist<Types...> >() >
    void set(T&& val)
    {
        new (&m_varStorage.data) T(simula24::forward<T>(val));
        m_idx = find < T, 0, Types...>();
    }

    ///
    /// @brief 
    ///     Set the value to 'val'
    template <typename T,
        bool = typelist_contains<T, typelist<Types...> >() >
    void operator=(T&& val)
    {
        new (&m_varStorage.data) T(simula24::forward<T>(val));
        m_idx = find < T, 0, Types...>();
        //return *this;
    }

    ///
    /// @brief get the value of T in the typelist
    template <typename T,
        bool = typelist_contains<T, typelist<Types...> >() >
    constexpr T& as()
    {
        return *reinterpret_cast<T*>(&m_varStorage.data);
    }

    ///
    /// @brief
    ///     Type conversion operator for any type in the union
    template <typename T,
        bool = typelist_contains<T, typelist<Types...> >() >
    constexpr operator T()
    {
        return as<T>();
    }

private:

    template <typename T, size_t idx, typename first, typename...list>
    static constexpr size_t find()
    {
        if constexpr (std::is_same_v<T, first>)
            return idx;
        else
            return find<T, idx + 1, list...>();
    }


private:

    union Storage
    {
        Storage() {}
        ~Storage() {}
        typename std::aligned_union<0, Types...>::type data;
    };

    //Storate m_varStorage;
    size_t m_idx{ 0 };
    Storage m_varStorage;

};


} // simula24 


#endif // SIMULA24_CORE_STL_VARIANT_H_