#ifndef SIMULA24_CORE_STL_UNORDERED_MAP_H_
#define SIMULA24_CORE_STL_UNORDERED_MAP_H_
#include <type_traits>
#include <simula24/core/stl/utility.h>
#include <simula24/core/stl/copy_on_write.h>
#include <simula24/core/stl/iterator.h>
#include <simula24/core/stl/hash.h>
#include <cassert>
#include <new>
#include <cstdlib>
#include <string.h>
namespace stl
{

template <class U, class T, class H>
class unordered_map;

template <class U>
class unordered_map_iterator;

constexpr int UMAP_EMPTY_SLOT = -1;

///
/// @brief
///     A specialized KV pair for maps/tables using PSLs
/// 
template <class K, class V, typename DisplacementType = int32_t>
struct displaced_pair
{
    template <class I, class J, class T>
    friend class unordered_map;

    template <class I>
    friend class unordered_map_iterator;

    K first;
    V second;
    displaced_pair(const K& _k, const V& _v)
        : first(_k), second(_v), displacement(UMAP_EMPTY_SLOT)
    {
    }

    displaced_pair(const K&& _k, const V&& _v)
        : first(stl::move(_k)), second(stl::move(_v))
    {}

    displaced_pair& operator=(const displaced_pair& o)
    {
        first = o.first;
        second = o.second;
        displacement = o.displacement;
        return *this;
    }
    ~displaced_pair() {
    }
private:
    DisplacementType displacement;


};

///
/// @brief
///     An unordered hash map implementation using 'Robin Hood' collision resolution
///     
///     The API is basically the same as std::unordered_map
/// 
template <class K, class V, class Hash = stl::hash<K> >
class unordered_map
{
public:
    using hashing_function = Hash;
    using kv_map_t = stl::displaced_pair<K, V>;

    using const_iterator = stl::unordered_map_iterator<const kv_map_t>;
    using iterator = stl::unordered_map_iterator<kv_map_t>;

    unordered_map() : m_data{}, m_size(0), m_element_count(0) { }
    ~unordered_map();
    /// Insert new value
    void insert(const kv_map_t& nkv);

    /// Get value at key
    V& at(const K& key);

    /// Get element at key. Will create a new on if not exists
    V& operator[](const K& key);
    V& operator[](K&& key);

    size_t count(const K& k) const;

    bool contains(const K& k) const { return index_of(k) != -1; }


    /// returns an iterator containing key's value
    /// end() if not exists
    iterator find(const K& key)
    {
        int idx = index_of(key);
        if (idx == -1) return end();

        return new_iterator(&m_data.at_m(idx));
    }

    /// returns an iterator containing key's value
    /// cend() if not exists
    const_iterator find(const K& key) const
    {
        int idx = index_of(key);
        if (idx == -1) return cend();

        return new_const_iterator(&m_data.at(idx));
    }

    ///
    /// @brief
    ///     Erase elements with Key k
    /// 
    size_t erase(const K& k);

    size_t erase(iterator i)
    {
        if (i != end())
            return erase((i->first));

        return 0;
    }

    /// get total number of elements allowed before
    /// a resize will occur
    size_t max_size() const { return m_size; }

    /// get current number of elements
    size_t size() const { return m_element_count; }

    /// is this map empty?
    bool empty() const { return m_element_count == 0; }

    /// Resize the array and rehash the data
    void resize(size_t n);

    /// Reserve 'n' entries, MUST be done before inserting data
    void reserve(size_t n);


    inline iterator begin() { return new_iterator(&m_data.at_m(0)); }

    inline iterator end() { return new_iterator(&m_data.at_m(m_size)); }

    inline const_iterator cbegin() const { return new_const_iterator(&m_data.at(0)); }

    inline const_iterator cend() const { return new_const_iterator(&m_data.at(m_element_count)); }

    constexpr unordered_map_iterator<const kv_map_t> new_const_iterator(const kv_map_t* target) const
    {
        return unordered_map_iterator<const kv_map_t>(target, &m_data.at(0), &m_data.at(m_size));
    }

    constexpr unordered_map_iterator<kv_map_t> new_iterator(kv_map_t* target)
    {
        return unordered_map_iterator<kv_map_t>(target, &m_data.at(0), &m_data.at(m_size));
    }
    /// get the index of 'key'. 
    /// @returns -1 on failure
    int index_of(const K& key) const;

private:

    copy_on_write<kv_map_t> m_data;
    size_t m_size;
    size_t m_element_count;
    void swap(uint32_t old_index, uint32_t new_index, uint32_t probelen);

};


template<class K, class V, class Hash>
unordered_map<K, V, Hash>::~unordered_map()
{
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::insert(const kv_map_t& nkv)
{
    // resize if needed
    if (m_element_count + 1 > m_size)
        resize(m_size + 1);

    uint32_t index = hashing_function::run(nkv.first) % m_size;
    unsigned int probe_len = 0;
    unsigned int n_probe_len = 0;

    signed int swapIndex = -1;
    while (probe_len < m_size)
    {

        // if the object does not exist, emplcae it here
        if (m_data.at(index).displacement == UMAP_EMPTY_SLOT)
        {
            auto* _new = &m_data.at_m(index);
            _new->first = nkv.first;
            _new->second = nkv.second;
            _new->displacement = probe_len;

            m_element_count++;

            if (swapIndex != -1)
            {
                swap(index, swapIndex, n_probe_len);
            }

            return;
        }
        // if the keys match, update the value
        else if (m_data.at(index).first == nkv.first)
        {
            m_data.at_m(index).second = nkv.second;
            return;
        }

        // linear probing
        else
        {
            if (swapIndex == -1 && m_data.at(index).displacement < (int)probe_len)
            {
                swapIndex = index;
                n_probe_len = probe_len;
            }
            index = (index + 1) % m_size;
        }

        ++probe_len;

    }
}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::at(const K& key)
{
    uint32_t hash = hashing_function::run(key);
    unsigned int index = hash % m_size;

    for (unsigned int i = 0; i < m_size; i++)
    {
        assert(m_data.at(index).displacement != UMAP_EMPTY_SLOT);
        if (m_data.at(index).displacement != UMAP_EMPTY_SLOT && m_data.at(index).first == key)
            return m_data.at_m(index).second;

        index = (index + 1) % m_size;

    }
    std::abort();
}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::operator[](const K& key)
{
    bool exists = false;
    if (m_size == 0)
        goto ____key_insertion_on_zero_length;
    exists =  index_of(key) != -1 ;

    if (exists)
        return m_data.at_m(index_of(key)).second;

____key_insertion_on_zero_length:
    insert({ key, V() });
    return m_data.at_m(index_of(key)).second;

}

template<class K, class V, class Hash>
V& unordered_map<K, V, Hash>::operator[](K&& key)
{
    K value = stl::move(key);
    return this->operator[](value);
}

template<class K, class V, class Hash>
size_t unordered_map<K, V, Hash>::erase(const K& k)
{
    int idx = index_of(k);
    // no keys to delete
    if (idx == -1)
        return 0;

    /// TODO: test code
    kv_map_t* target = &m_data.at_m((size_t)idx);
    int curpsl = target->displacement;
    int iters = 0;

    // shift every item with a displacement higher than ours 1 index lower
    while (m_data.at_m(++idx).displacement > curpsl && (iters < m_element_count))
    {
        auto* old = &m_data.at_m(idx);
        old->displacement--;
        memmove(target, old, sizeof(kv_map_t));

        target = &m_data.at_m(idx);

        idx = (idx + 1) % m_size;
        ++iters;
    }
    target->displacement = UMAP_EMPTY_SLOT;
    --m_element_count;
    return 1;
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::resize(size_t n)
{
    // get a copy of the data, this will increase the ref count
    copy_on_write<kv_map_t> copy = m_data;
    // resize, our old data is in m_data
    m_data.resize(n);

    ::memset(&m_data.at_m(0), 0, n * sizeof(kv_map_t));

    auto old_size = m_size;
    if (n < old_size)
        old_size = n;
    m_size = n;
    // this will be reset to what it was in the 
    // resinsertion loop below
    m_element_count = 0;

    // mark all slots as overwrite-able
    for (size_t i = 0; i < n; i++)
        m_data.at_m(i).displacement = UMAP_EMPTY_SLOT;

    for (size_t i = 0; i < old_size; i++)
        insert(copy.at(i));


    // when copy goes out of scope, it will either delete itself
    // or decrease the ref count  
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::reserve(size_t n)
{
    assert(m_element_count == 0);
    m_data.resize(n);
    //memset(m_data.get_data(), 0, m_data.get_size());
    m_size = n;
    // mark all slots as overwriteable
    for (size_t i = 0; i < n; i++)
        m_data.at_m(i).displacement = UMAP_EMPTY_SLOT;

}

template<class K, class V, class Hash>
int unordered_map<K, V, Hash>::index_of(const K& key) const
{
    uint32_t index = hashing_function::run(key) % m_size;
    for (int i = 0; i < m_element_count; i++)
    {
        if (m_data.at(index).displacement != UMAP_EMPTY_SLOT && m_data.at(index).first == key)
            return index;
        index = (index + 1) % m_size;

    }

    return -1;
}

template<class K, class V, class Hash>
void unordered_map<K, V, Hash>::swap(uint32_t old_index, uint32_t new_index, uint32_t probelen)
{
    assert(probelen != -1 && probelen != 0xffffffff);
    kv_map_t temp = m_data.at(old_index);

    kv_map_t* old = &m_data.at_m(old_index);
    kv_map_t* _new = &m_data.at_m(new_index);

    old->first = _new->first;
    old->second = _new->second;
    old->displacement = _new->displacement == UMAP_EMPTY_SLOT ? UMAP_EMPTY_SLOT : _new->displacement;

    _new->first = temp.first;
    _new->second = temp.second;
    _new->displacement = probelen;
}

///
/// @brief
///     Custom Iterator for stl::unordered_map
/// 
///     This iterator will skip over any EMPTY_SLOTs
///     
template <class T>
class unordered_map_iterator
{
public:
    using BaseType = std::remove_pointer<T>;
    constexpr unordered_map_iterator(T* elem, const T* start, const T* end) 
        : m_element(elem), m_start(start), m_end(end) 
    { 
        find_start(); 
    }
    
    constexpr unordered_map_iterator() 
        : m_element(nullptr), m_start(nullptr), m_end(nullptr) {}
    
    constexpr unordered_map_iterator(const unordered_map_iterator& o)
        : m_element(o.m_element), m_start(o.m_start), m_end(o.m_end) {}
    
    unordered_map_iterator& operator++()
    {
        while (++m_element < m_end)
        {
            if (m_element->displacement != UMAP_EMPTY_SLOT)
                break;
        }

        return *this;
    }

    unordered_map_iterator& operator--()
    {
        while (--m_element > m_start)
        {
            if (m_element->displacement != UMAP_EMPTY_SLOT)
                break;
        }

        return *this;
    }

    constexpr T& operator*() { return *m_element; }
    constexpr T* operator->() { return m_element; }

    inline bool operator==(const unordered_map_iterator& o) const
    {
        return m_element == o.m_element;
    }

    inline bool operator!=(const unordered_map_iterator& o) const
    {
        return m_element != o.m_element;
    }

    //operator unordered_map_iterator() const
    //{
    //    return unordered_map_iterator(m_element);
    //}
private:

    void find_start()
    {
        if (m_element->displacement == UMAP_EMPTY_SLOT)
            this->operator++();
    }

    T* m_element;
    const T* m_start;
    const T* m_end;
};

} // simula24


#endif // SIMULA24_CORE_STL_UNORDERED_MAP_H_