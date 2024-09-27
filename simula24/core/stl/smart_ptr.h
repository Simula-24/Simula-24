#ifndef CORE_simula24_SMART_PTR_H_
#define CORE_simula24_SMART_PTR_H_

#include <stdint.h>
#include <cassert>
#include <type_traits>
#include <simula24/core/stl/utility.h>
#include <simula24/core/memory/memory.h>

#include <new>
namespace stl
{

/// @brief
///    A simple container for holding a pointer and  
///    the number of shared_ptrs referencing it
/// 
///     void* is for type erasure such that this structure 
///     can be shared between shared_ptrs with convertable types or
///     base-derived types
/// 
struct RefCountContainer
{
    void* _ptr;
    uint32_t _refcount;
};

///
/// @brief
///    Generic Shared Pointer class
///    
///    create via @ref simula24::make_shared <YourType>(YourArgs...);
///    
///    This is a reference counted Smart Pointer.
///    It will use a structure called @ref RefCountContainer to hold
///    the pointer and it's reference count
/// 
///    Copying this class will simply increase the reference count
///    Moving this class will NOT
/// 
///    During destruction, this class will try to release itself
///        1. if the reference count is 1, we are the owner: destroy the data
///        2. otherwise, decrement the refcount
/// 
template <class T >
class shared_ptr
{
public:

    shared_ptr() : _int_store(nullptr) {}

    template <class U>
    shared_ptr(U* _new)
    {
        _int_store = new RefCountContainer{ ._ptr = _new, ._refcount = 1 };
    }

    ~shared_ptr()
    {
        release();
    }

    shared_ptr(const shared_ptr& other)
        : _int_store(other._int_store)
    {
        _int_store->_refcount++;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        _int_store = other._int_store;
        other._int_store->_refcount++;
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other)
    {

        _int_store = stl::move(other._int_store);
        other._int_store->_refcount++;
        return *this;

    }

    /// get the pointer
    T* operator->()
    {
        if (_int_store)
            return static_cast<T*>(_int_store->_ptr);
        else
            return nullptr;
    }

    /// dereference the pointer
    T& operator*()
    {
        assert(_int_store);
        return *static_cast<T*>(_int_store->_ptr);
    }

    /// 
    /// @brief
    ///     Convert between a convertable type
    /// 
    template<class U>
    shared_ptr(const shared_ptr<U>& other, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0)
        : _int_store(((shared_ptr<T>&)other)._int_store)
    {
        _int_store->_refcount++;
    }

    /// 
    /// @brief
    ///     Convert between parent and child types
    /// 
    template<class U>
    shared_ptr<U> static_pointer_cast()
    {
        auto x = shared_ptr<U>();
        _int_store->_refcount++;
        x._int_store = _int_store;

        return x;
    }

    bool isSame(const shared_ptr& other)
    {
        return other._int_store == _int_store;
    }

    bool isValid() { return _int_store != nullptr; }

    ///
    /// @brief
    ///     Release the pointer because we are done with it
    ///     This is automatically called from our destructor
    /// 
    ///     This will decrease the reference count or if it is 0,
    ///     it will destroy/free the resource
    /// 
    void release()
    {
        if (_int_store == nullptr || _int_store->_ptr == nullptr)
            return;
        if (_int_store->_refcount <= 1)
        {
            if constexpr (!std::is_trivially_destructible_v<T>)
            {
                T* t = (T*)_int_store->_ptr;
                t->~T();
            }
            simula24::free_static(_int_store->_ptr);
            delete _int_store;
            _int_store = nullptr;
        }
        else
            _int_store->_refcount--;
    }

    uint32_t reference_count() const
    {
        return _int_store->_refcount;
    }

private:


    RefCountContainer* _int_store;

    template <class U>
    friend class shared_ptr;

};

/// Create a new shared pointer
template <class T, class... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    T* nt = (T*)simula24::alloc_static(sizeof(T));

    return shared_ptr<T>(
        new (nt) T(stl::forward<Args>(args)...)
    );
}

///
/// @brief
///    Generic Unique Smart Pointer class
/// 
///    This object cannot be shared or copied, it can only
///    be moved
/// 
///    Create with @ref simula24::make_unique<T>
///    
///    Access the data via the overloaded member access operators
/// 
template <class T>
class unique_ptr
{
public:

    unique_ptr() : m_ptr(nullptr) {}

    explicit unique_ptr(T* _new) : m_ptr(_new) { assert(_new); }

    ~unique_ptr()
    {
        if (m_ptr)
            simula24::free_static(m_ptr);
    }

    unique_ptr(unique_ptr&& other)
        : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    template<class U, std::enable_if_t<std::is_convertible_v<U*, T*>, int> = 0>
    unique_ptr(unique_ptr<U>&& other)
    {
        if (m_ptr == other.m_ptr)
            return;

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }
    template<class U>
    unique_ptr& operator=(unique_ptr<U>&& other)
    {
        if (m_ptr == other.m_ptr)
            return *this;

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    }


    unique_ptr& operator=(unique_ptr&& other)
    {
        m_ptr = stl::move(other.m_ptr);
        other.m_ptr = nullptr;

        return *this;
    }

    T& operator*()
    {
        assert(m_ptr);
        return *m_ptr;
    }

    T* operator->()
    {
        return m_ptr;
    }

private:

    T* m_ptr;

    template<class U>
    friend class unique_ptr;
};


/// Create a new unique pointer
template <class T, class... Args>
unique_ptr<T> make_unique(Args... args)
{
    T* nt = (T*)simula24::alloc_static(sizeof(T));

    return unique_ptr<T>(
        new (nt) T(stl::forward<Args>(args)...)
    );
}



} // stl

#endif // CORE_simula24_SMART_PTR_H_