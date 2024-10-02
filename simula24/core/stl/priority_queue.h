#ifndef CORE_STL_PRIORITY_QUEUE_H_
#define CORE_STL_PRIORITY_QUEUE_H_

#include <core/types.h>
#include <core/stl/copy_on_write.h>

#include <stdio.h>
namespace simula24
{

template <class T, class IntType = I32>
class priority_queue
{
public:
    constexpr static I32 EMPTY_CHILD = -1;
    
    struct pq_pair 
    {
        T object;
        IntType priority{ (I32)(EMPTY_CHILD) };

        pq_pair& operator=(const pq_pair& o)
        {
            object = o.object;
            priority = o.priority;
            return *this;
        }

    };

    priority_queue() : m_current_size(0), m_idx(0) {}
    priority_queue(size_t size) 
        : m_current_size(size), m_idx(0) 
    {
        m_heap.resize(size);
        for (int i = 0; i < size; i++)
            m_heap.at_m(i).priority = EMPTY_CHILD;
    }

    void push(T object, IntType priority)
    {
        resize();
        auto& obj = m_heap.at_m(m_idx);
        obj.object = object;
        obj.priority = priority;
        sift_up(m_idx);
        m_idx++;
    }

    pq_pair pop()
    {
        if (m_idx == 0)
            return {};
        m_idx--;
        if (m_idx == 0)
        {
            return m_heap.at(m_idx);
        }

        std::swap(m_heap.at_m(0), m_heap.at_m(m_idx));
        sift_down(0);
        pq_pair p = m_heap.at(m_idx);
        return p;
    }
    void dump()
    {
        for (int i = 0; i < m_idx; i++) printf("%ld ", m_heap.at(i).priority);
        putchar('\n');
    }
private:
    
    void resize()
    {
        if (m_idx >= m_current_size || m_current_size > m_heap.get_size())
        {
            m_heap.resize(m_current_size + 4); // 4 new children
            for (; m_current_size < m_current_size + 4; m_current_size++)
            {
                m_heap.at_m(m_current_size).priority = EMPTY_CHILD;
            }
        }
    }
    

    constexpr I32 get_left_child(I32 pos)
    {
        return (2 * pos + 1);
    }

    constexpr I32 get_right_child(I32 pos)
    {
        return (2 * pos + 2);
    }

    constexpr I32 get_parent(I32 pos)
    {
        return (pos - 1) / 2;
    }
    constexpr bool is_leaf(I32 pos)
    {
        return (m_idx / 2 <= pos) && (pos < m_idx);
    }

    constexpr IntType priority_at(I32 idx)
    {
        return m_heap.at(idx).priority;
    }

    void sift_up(I32 idx)
    {
        while (idx > 0)
        {
            I32 parent = get_parent(idx);
            if (priority_at(parent) >= priority_at(idx))
                return;
            std::swap(m_heap.at_m(idx), m_heap.at_m(parent));
            idx = parent;
        }
    }

    void sift_down(I32 idx)
    {
        while (!is_leaf(idx))
        {
            I32 left = get_left_child(idx);
            if ((left + 1 < m_idx) && priority_at(left + 1) > priority_at(left))
                left++;
            if (priority_at(left) < priority_at(idx))
                return;
            std::swap(m_heap.at_m(idx), m_heap.at_m(left));
            idx = left;
        }
    }

    size_t m_current_size;
    I32 m_idx;
    stl::copy_on_write<pq_pair> m_heap;
};

} // simalu24

#endif // CORE_STL_PRIORITY_QUEUE_H_