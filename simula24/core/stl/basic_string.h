#ifndef SIMULA24_CORE_STL_BASIC_STRING_H_
#define SIMULA24_CORE_STL_BASIC_STRING_H_

#include <limits.h>
#include <type_traits>
#include <simula24/core/stl/utility.h>
#include <simula24/core/stl/copy_on_write.h>

namespace stl
{


template<class T>
class basic_string
{
public:

    static constexpr size_t npos = UINT64_MAX;

    basic_string() : m_length(0) { }
    ~basic_string()
    {

    }
    basic_string(const basic_string& other)
        : m_chars(other.m_chars), m_length(other.m_length)
    {
    }

    basic_string(const basic_string&& other)
        : m_chars(stl::move(other.m_chars)), m_length(stl::move(other.m_length))
    {

    }
    basic_string(const T* source)
    {
        *this = source;
    }

    basic_string& operator=(const basic_string& other)
    {

        m_chars = other.m_chars;
        m_length = other.length();
        return *this;

    }

    basic_string& operator=(const basic_string&& other)
    {


        m_length = stl::move(other.length());
        m_chars = stl::move(other.m_chars);

        return *this;
    }


    template <size_t N>
    basic_string& operator=(const T(&other)[N])
    {

        resize(N);
        m_length = N;
        assign(other);
        return *this;
    }

    basic_string& operator=(const T* other)
    {


        // todo: this  is temporary code
        size_t size = strlen(other);
        size += 1;
        m_length = size;
        resize(size);
        assign(other);

        return *this;
    }

    basic_string& operator+=(T other)
    {
        if (should_resize()) resize(m_length + 1);
        m_chars.at_m(m_length) = other;
        m_length++;

        return *this;
    }

    basic_string& operator+=(const T* other)
    {


        size_t olen = strlen(other) + 1;
        size_t newsize = length() + (olen)-1;
        size_t oldlen = length();

        m_length = newsize;
        if (should_resize())
            resize(newsize + 1);

        // -2 to copy over old data's null
        m_chars.copydata(other, olen, oldlen == 0 ? 0 : oldlen - 1);

        return *this;
    }

    basic_string& operator+=(const basic_string& other)
    {


        size_t newsize = length() + (other.length() - 1);
        size_t oldlen = length();
        if (should_resize())
            resize(newsize + 1);
        m_length = newsize;

        m_chars.copydata(other.c_str(), other.length() + 1, oldlen - 1);
        return *this;

    }

    /// return a substring
    basic_string<T> substr(size_t pos = 0, size_t count = npos) const;
    
    basic_string<T> substr_from_to(size_t from = 0, size_t to = npos) const;

    void setPos(size_t pos)
    {
        if (m_chars.get_size() < pos) pos = m_chars.get_size();
        m_length = pos;
    }
    inline void resize(size_t n)
    {
        m_chars.resize(n);
    }

    /// copy these characters
    inline void assign(const T* chars)
    {


        m_chars.copydata(chars, strlen(chars) + 1);
    }

    /// returns raw data from string
    constexpr T* data()
    {
        return &m_chars.copy();
    }

    /// returns a const c array
    constexpr const T* c_str() const
    {
        return &m_chars.reference();
    }

    /// get the length
    constexpr size_t length() const
    {
        return m_length;
    }

    /// 
    /// @brief
    ///     Find first occurense of 'ch'
    ///     
    /// @returns index of ch or npos if not found
    /// 
    size_t find(T ch) const;

    /// 
    /// @brief
    ///     Find first occurense of 'ch' starting at offset
    ///     
    /// @returns index of ch or npos if not found
    /// 
    size_t find(size_t offset, T ch) const;

    /// get reference character at pos
    constexpr T& operator[](size_t pos) { return m_chars.at_m(pos); }

    /// get const reference character at pos
    constexpr const T& operator[](size_t pos) const { return m_chars.at(pos); }

    /// Get the length of a string
    static size_t strlen(const T* other)
    {
        return ::strlen(other);
    }

    /// get a const reference to the first character
    constexpr const T& front() const { return *m_chars.at(0); }
    /// get a reference to the first character
    constexpr T& front() { return m_chars.at_m(0); }

    /// get a const reference to the last character
    constexpr const T& back() const { return m_chars.at(length() - 2); }
    /// get a reference to the last character
    constexpr T& back() { return m_chars.at_m(length() - 2); }


private:
    
    copy_on_write<T> m_chars;
    /// Our buffer. COW happens implicitly
    size_t m_length;

    constexpr bool should_resize()
    {

        return m_length >= m_chars.get_size();
    }
};



template<class T>
basic_string<T> basic_string<T>::substr(size_t pos, size_t count) const
{
    if (count > length())
        count = length() - pos;

    basic_string<T> newString;
    newString.resize(count + 1);

    size_t idx = 0;
    for (size_t i = 0; i < count; i++)
    {
        newString[idx++] = m_chars.at(pos + i);
    }
    newString[idx] = 0;
    newString.m_length = idx + 1;
    return newString;
}

template<class T>
basic_string<T> basic_string<T>::substr_from_to(size_t from, size_t to) const
{

    if (to > length())
        to = length();

    basic_string<T> newString;
    newString.resize(to - from + 1);

    size_t idx = 0;
    for (size_t i = from; i < to; i++)
    {
        newString[idx++] = m_chars.at(i);
    }
    newString[idx] = 0;
    newString.m_length = idx + 1;
    return newString;
}

template <class T>
size_t basic_string<T>::find(T ch) const
{
    for (size_t i = 0; i < m_length; i++)
    {
        if (m_chars.at(i) == ch)
            return i;
    }
    
    return npos;
}

template <class T>
size_t basic_string<T>::find(size_t offset, T ch) const
{
    for (size_t i = offset; i < m_length; i++)
    {
        if (m_chars.at(i) == ch)
            return i;
    }

    return npos;
}

} // simula24


#endif // SIMULA24_CORE_STL_BASIC_STRING_H_