#ifndef SIMULA24_CORE_STL_ARRAY_H_
#define SIMULA24_CORE_STL_ARRAY_H_

#include <simula24/core/stl/utility.h>
#include <simula24/core/stl/copy_on_write.h>
#include <simula24/core/stl/iterator.h>
#include <core/types.h>
namespace stl
{


///
/// @brief
///     array to hold T data
/// 
///     This uses a COW buffer to hold the data
/// 
///     elem_ptr points to the last element in the buffer,
///     as to reduce resizing.
/// 
template <class T>
class array
{
public:

    using const_iterator = stl::generic_const_iterator<T>;
    using iterator = stl::generic_iterator<T>;



    array() : m_index(0)
    {
    }
    ~array()
    {
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            for (size_t i = 0; i < m_index; i++)
                operator[](i).~T();
        }
    }
    FORCEINLINE void resize(size_t n)
    {
        m_data.resize(n);
    }

    /// Fill with T
    void fill(T value)
    {
        auto _end = m_data.get_size();
        for (size_t i = 0; i < _end; i++)
        {
            m_data.at_m(i) = value;
        }
    }

    void fill_remaining(T value)
    {
        auto _end = m_data.get_size();

        for (size_t i = m_index; i < _end; i++)
        {
            m_data.at_m(i) = value;
        }
    }


    void push_back(const T& value)
    {
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_m(m_index++)) = value;
    }

    void push_back(T&& value)
    {
        if (should_resize())
        {
            resize(size() + 1);
        }
        (m_data.at_m(m_index++)) = value;
    }


    FORCEINLINE void pop_back()
    {
        m_index--;
    }

    FORCEINLINE T& operator[](size_t index)
    {
        return m_data.at_m(index);
    }

    FORCEINLINE const T& operator[](size_t index) const
    {
        return m_data.at(index);
    }

    // @todo: see if this can be optimized
    bool contains(const T& value) const
    {
        for (size_t i = 0; i < m_index; i++)
        {
            if (m_data.at(i) == value)
                return true;
        }

        return false;
    }


    FORCEINLINE size_t size() const { return m_index; }
    FORCEINLINE size_t max_size() const { return m_data.get_size(); }


    FORCEINLINE const T& front() const { return m_data.at(0); }
    FORCEINLINE const T& back() const { return  m_data.at(m_index - 1); }

    FORCEINLINE T& front() { return m_data.at_m(0); }
    FORCEINLINE T& back() { return m_data.at_m(m_index - 1); }


    FORCEINLINE iterator begin() { return iterator(&operator[](0)); }
    FORCEINLINE iterator end() { return iterator(&operator[](m_index)); }

    FORCEINLINE const_iterator cbegin() const { return const_iterator(&operator[](0)); }
    FORCEINLINE const_iterator cend()   const { return const_iterator(&operator[](m_index)); }

private:
    /// Holds our data. 
    copy_on_write<T> m_data;

    /// Pointer to last element
    size_t m_index;

    FORCEINLINE bool should_resize()
    {
        return (m_index >= m_data.get_data_size());
    }
};

} // simula24


#endif // SIMULA24_CORE_STL_ARRAY_H_