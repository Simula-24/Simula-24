#ifndef SIMULA24_CORE_STL_COPY_ON_WRITE_H_
#define SIMULA24_CORE_STL_COPY_ON_WRITE_H_

#include <simula24/core/memory/memory.h>
#include <simula24/core/stl/utility.h>
#include <stdint.h>
#include <string.h>
namespace stl
{
///    
/// @brief 
///    A template class that allows clients to    
///    use copy-on-write. Use @ref copy() to create 
///    your own copy
///
///    Provide a Copy on Write buffer for clients
///     
///    When the copy constructor or copy assignment
///    operator is used, the pointer to the other COWs
///    buffer is used and it's refcounter incremented
///     
///    Reference counters are stored inside the allocated buffer
///     @code
///    0           32                 64    
///    ┌────────────┬───────────┬──────┐
///    │  Ref Count │ Data Size │ Data │    
///    └────────────┴───────────┴──────┘
///    @endcode
/// 
///    When a copy occurs:
///        1. Create a new buffer and copy the existing buffer's data into it.
///        2. Decrement the old buffer's ref count
///        3. Set the new buffer's ref count to 1
///        4. Set the current buffer to the new buffer        
///     
///    The function @ref __copy_on_write will ensure that we do own our own copy
/// 
template <class T>
class copy_on_write
{
public:
    
    copy_on_write() : m_ptr(nullptr)
    {
        create_empty();
    }

    ~copy_on_write()
    {
        unref();
    }

    copy_on_write(const copy_on_write& other)
        : m_ptr(other.m_ptr)
    {
        ref();
    }

    copy_on_write& operator=(const copy_on_write& other)
    {
        m_ptr = other.m_ptr;
        ref();
        return *this;
    }

    /// data[where] without a copy
    constexpr const T& at(size_t where) const;

    /// data[where] with a copy
    T& at_m(size_t where);

    /// TOTAL size of data section in bytes
    uint32_t get_total_size() const;

    /// Get total number of T's that can fit
    uint32_t get_size() const;

    /// obtain a reference to the data
    constexpr const T& reference() const;
    
    /// obtain a reference to the data and create a copy
    constexpr T& copy();


    /// Copy to the <i>data section offset</i>
    void copydata(const T* source, size_t n);

    /// @brief
    ///    Copy to the data section + offset
    ///    Note that this will copy relative to the offset
    ///    
    void copydata(const T* source, size_t n, size_t offset);

    ///
    /// @brief
    ///     Resize the buffer
    /// 
    ///     This will create a new copy
    /// 
    void resize(size_t n);

    ///
    /// @brief
    ///     A nicer way of obtain header data
    /// 
    struct CowHdr
    {
        uint32_t ref_count;
        uint32_t data_size;
    };

    constexpr uint32_t get_reference_count() const
    {
        return get_cow_header()->ref_count;
    }

    constexpr uint32_t get_data_size() const
    {
        return get_cow_header()->data_size;
    }

private:
    constexpr CowHdr* get_cow_header()
    {
        return static_cast<CowHdr*>((void*)m_ptr);
    }

    constexpr const CowHdr* get_cow_header() const
    {
        return static_cast<const CowHdr*>((void*)m_ptr);
    }

    // @TODO: clean this mess up

    static constexpr size_t REFCOUNT_OFFSET = 0;
    static constexpr size_t SIZE_OFFSET = REFCOUNT_OFFSET + 4;
    static constexpr size_t DATA_OFFSET = SIZE_OFFSET + 4;
    constexpr T* get_data()
    {
        return (T*)(((uint8_t*)m_ptr) + DATA_OFFSET);

    }
    constexpr const T* get_data() const
    {
        return (T*)(((uint8_t*)m_ptr) + DATA_OFFSET);
    }

    constexpr uint32_t* get_refc_ptr()
    {
        return (uint32_t*)(((uint8_t*)m_ptr) + REFCOUNT_OFFSET);
    }

    constexpr uint32_t* get_data_size_ptr()
    {
        return (uint32_t*)(((uint8_t*)m_ptr) + SIZE_OFFSET);
    }

    constexpr size_t get_alloc_size(size_t n)
    {
        //          objects             meta data
        return (n * sizeof(T)) + (sizeof(uint32_t) * 2);
    }
private:

    ///
    /// @brief
    ///     Create a copy of the buffer for our own use
    /// 
    ///     This will automatically occur when any non-const functions
    ///     are called
    /// 
    ///     If the buffer is empty or the reference count is less than 2, 
    ///     nothing will happen
    /// 
    uint32_t create_copy();

    ///
    /// @brief 
    ///     Add a reference
    ///     
    ///     This is called during any of the rule of 5
    /// 
    void ref();

    ///
    /// @brief
    ///     Remove a reference
    /// 
    ///     Happens during destruction
    /// 
    ///     If the reference count is 0 after removal, the data is free-ed
    void unref();

    void create_empty();

    T* m_ptr;

};


template<class T>
uint32_t copy_on_write<T>::create_copy()
{
    if (!m_ptr || get_total_size() == 0)
        return 0;

    if (get_reference_count() == 1)
        return 1;

    // hdr points to current header
    CowHdr* hdr = get_cow_header();

    uint32_t old_size = get_total_size();
    
    uint32_t rc = hdr->ref_count;
    hdr->ref_count--;

    T* old_data_ptr = get_data();

    T* new_buffer = static_cast<T*>(simula24::alloc_static(old_size + sizeof(CowHdr)));

    m_ptr = new_buffer;

    // hdr points to new header
    hdr = get_cow_header();
    
    // reset every thing
    hdr->ref_count = 1;
    hdr->data_size = old_size;

    // and copy the old data over
    ::memcpy(get_data(), old_data_ptr, old_size);

    return rc;
}



template<class T>
inline uint32_t copy_on_write<T>::get_total_size() const
{
    if (!m_ptr)
        return 0;
    return get_data_size() * sizeof(T);
}

template <class T>
uint32_t copy_on_write<T>::get_size() const
{
    if (!m_ptr)
        return 0;
    return get_data_size();
}

template<class T>
void copy_on_write<T>::ref()
{
    if (m_ptr)
        get_cow_header()->ref_count++;
}

template<class T>
void copy_on_write<T>::unref()
{
    if (m_ptr)
    {

        if (get_reference_count() == 1)
        {
            simula24::free_static(m_ptr);
            m_ptr = nullptr;
        }
        else
            get_cow_header()->ref_count--;

    }
}

template <class T>
void copy_on_write<T>::resize(size_t n)
{
    uint32_t rc = create_copy();

    T* new_buffer = static_cast<T*>(simula24::alloc_static((n * sizeof(T)) + sizeof(CowHdr)));

    T* old_buffer = m_ptr;
    T* old_data = get_data();
    size_t old_size = get_total_size();

    m_ptr = new_buffer;

    get_cow_header()->data_size = (uint32_t)(n);
    get_cow_header()->ref_count = 1;

    if (old_size > 0)
    {
        // if this is a larger buffer, copy all of the old data
        if (n > old_size)
            copydata(old_data, old_size);
        // otherwise, only copy the remaining data
        else
            copydata(old_data, n);

    }
    //if (rc == 1)
    //    simula24::free_static(old_buffer);
}


template<class T>
void copy_on_write<T>::create_empty()
{
    T* buffer = static_cast<T*>(simula24::alloc_static(sizeof(CowHdr)));

    m_ptr = buffer;

    get_cow_header()->ref_count = 1;
    get_cow_header()->data_size = 0;
}

template<class T>
constexpr const T& copy_on_write<T>::at(size_t where) const
{
    const T* _ptr = get_data();
    return _ptr[where];
}

template <class T>
T& copy_on_write<T>::at_m(size_t where)
{
    create_copy();
    T* _ptr = get_data();
    return _ptr[where];
}
template<class T>
constexpr const T& copy_on_write<T>::reference() const
{
    return *(m_ptr + DATA_OFFSET);
}

template<class T>
inline constexpr T& copy_on_write<T>::copy()
{
    create_copy();
    return *(m_ptr + DATA_OFFSET);
}

template<class T>
void copy_on_write<T>::copydata(const T* source, size_t n)
{
    create_copy();
    ::memcpy(get_data(), source, (n * sizeof(T)));
}

template<class T>
void copy_on_write<T>::copydata(const T* source, size_t n, size_t offset)
{
    create_copy();
    ::memcpy(get_data() + (offset * sizeof(T)), source, (n * sizeof(T)));
}


} // simula24

#endif // SIMULA24_CORE_STL_COPY_ON_WRITE_H_