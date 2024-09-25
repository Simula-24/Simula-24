#ifndef SIMULA24_CORE_STL_ITERATOR_H_
#define SIMULA24_CORE_STL_ITERATOR_H_

namespace simula24
{
///
/// @brief 
///     Generic iterator container
/// 
///     @ref meminc controls the iteration methof
///     If it is set to true, the inc/dec operators
///     will increment memory addresses
/// 
///     Otherwise, this will assume that T is a doubly linked list
///     and use the next and prev functions that MUST be provided
///     by T.
///     
template <class T, bool linked_list = false>
struct generic_iterator
{
    generic_iterator(T* elem) : element(elem) {}
    generic_iterator() {}
    generic_iterator(const generic_iterator& o) : element(o.element) {}

    /// next address/next node
    inline generic_iterator& operator++()
    {
        if constexpr (linked_list)
            element = element->next();
        else
            element++;
        return *this;
    }

    /// previous address/previous node
    inline generic_iterator& operator--()
    {
        if constexpr (linked_list)
            element = element->prev();
        else
            element--;
        return *this;
    }

    /// dereference
    inline T& operator*() const { return *element; }

    /// Access via pointer
    inline T* operator->() const { return element; }

    inline bool operator==(const generic_iterator& o)
    {
        return element == o.element;
    }

    inline bool operator!=(const generic_iterator& o)
    {
        return element != o.element;
    }

    operator generic_iterator() const
    {
        return generic_iterator(element);
    }
private:
    T* element = nullptr;
};


///
/// @brief
///     @ref iterator but const
/// 
template <class T, bool linked_list = false>
struct generic_const_iterator
{
    generic_const_iterator(T* elem) : element(elem) {}
    generic_const_iterator() {}
    generic_const_iterator(const generic_const_iterator& o) : element(o.element) {}

    /// next address/next node
    inline const generic_const_iterator& operator++()
    {
        if constexpr (linked_list)
            element = element->next();
        else
            element++;
        return *this;
    }

    /// previous address/previous node
    inline const generic_const_iterator& operator--()
    {
        if constexpr (linked_list)
            element = element->prev();
        else
            element--;
        return *this;
    }

    /// dereference
    inline T& operator*() const { return *element; }
    /// acess via pointer
    inline T* operator->() const { return element; }

    inline bool operator==(const generic_const_iterator& o)
    {
        return element == o.element;
    }

    inline bool operator!=(const generic_const_iterator& o)
    {
        return element != o.element;
    }

    operator generic_const_iterator() const
    {
        return iterator(element);
    }
private:
    T* element = nullptr;
};



} // simula24


#endif // SIMULA24_CORE_STL_ITERATOR_H_