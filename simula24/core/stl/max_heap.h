#ifndef CORE_STL_MAX_HEAP_H_
#define CORE_STL_MAX_HEAP_H_

#include <core/stl/copy_on_write.h>
#include <core/types.h>
#include <utility>
#include <cassert>

namespace simula24
{

class max_heap
{
public:

    max_heap() : m_current_size(0), m_idx(0) {}
    
    max_heap(size_t size) 
        : m_current_size(size), m_idx(0)
    {
        m_data.resize(size);
        U32 zero = 0;
        m_data.copydata(&zero, m_current_size);
    }

    constexpr U32 get_left_child(U32 pos)
    {
        return (2 * pos + 1);
    }

    constexpr U32 get_right_child(U32 pos)
    {
        return (2 * pos + 2);
    }
    
    constexpr U32 get_parent(U32 pos)
    {
        return (pos - 1) / 2;
    }
    constexpr bool is_leaf(U32 pos)
    {
        return (m_idx / 2 <= pos) && (pos < m_idx);
    }
    void sift_up(U32 n)
    {
        while (n > 0)
        {
            U32 parent = get_parent(n);
            if (m_data.at(parent) >= m_data.at(n))
                return;
            std::swap(m_data.at_m(n), m_data.at_m(parent));
            n = parent;
        }
    }

    void sift_down(U32 index)
    {
        while (!is_leaf(index))
        {
            int left = get_left_child(index);
            if ((left + 1 < m_idx) && m_data.at(left + 1) > m_data.at(left))
                left++;
            if (m_data.at(left) > m_data.at(index))
                return;
            std::swap(m_data.at_m(m_idx), m_data.at_m(left));
            index = left;
        }
    }

    void insert(U32 n)
    {
        resize_if(m_idx >= m_current_size);
        
        m_data.at_m(m_idx) = n;
        sift_up(m_idx);
        m_idx++;
    }

    U32 pop()
    {
        if (m_idx == 0)
            return (U32)-1;
    
        m_idx--;
        std::swap(m_data.at_m(0), m_data.at_m(m_idx));
        sift_down(m_idx);


    }

    void dump()
    {
        for (int i = 0; i < m_idx; i++) printf("%d " , m_data.at(i));
        putchar('\n');
    }
private:

    constexpr void resize_if(bool expr)
    {
        if (expr)
            m_data.resize(m_current_size + 2);
    }

    stl::copy_on_write<uint32_t> m_data;
    size_t m_current_size;
    size_t m_idx;
};

} // simula24

#endif // CORE_STL_MAX_HEAP_H_