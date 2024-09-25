#ifndef SIMULA24_CORE_STL_FUNCTION_H_
#define SIMULA24_CORE_STL_FUNCTION_H_

#include <simula24/core/stl/smart_ptr.h>
#include <simula24/core/stl/utility.h>
#include <type_traits>

namespace simula24
{

///
/// @brief
///     Base Callable class
///     Used for type erasure
/// 
template <class RetType, class... Args>
class Callable
{
public:
    virtual ~Callable() = default;
    virtual RetType invoke(Args&&... args) = 0;
};

///
/// @brief
///     Wrapper around callable
/// 
template <class Fn, class RetType, class... Args >
class CallableWrapper : public Callable<RetType, Args...>
{
public:
    explicit CallableWrapper(Fn fn) : m_fn(simula24::move(fn)) {}

    RetType invoke(Args&&... args) override
    {
        if constexpr (std::is_same_v<RetType, void>)
            m_fn(simula24::forward<Args>(args)...);
        else
            return m_fn(simula24::forward<Args>(args)...);
    }
private:
    Fn m_fn;
};

template <class Signature>
class function;

template <class Ret, class... Args>
class function <Ret(Args...)>
{

public:


    template <class Fn>
    function(Fn fn)
    {
        m_functor = simula24::make_unique<CallableWrapper<Fn, Ret, Args...>>(simula24::move(fn));
    }

    function() {}

    template<class Fn>
    function& operator=(const function& other)
    {
        m_functor = other.m_functor;
        return *this;
    }

    Ret operator()(Args&&...args)
    {
        if constexpr (std::is_same_v<Ret, void>)
            m_functor->invoke(simula24::forward<Args>(args)...);
        else
            return  m_functor->invoke(simula24::forward<Args>(args)...);
    }

private:
    simula24::unique_ptr<Callable<Ret, Args...>> m_functor;
};



} // simula24

#endif // SIMULA24_CORE_STL_FUNCTION_H_