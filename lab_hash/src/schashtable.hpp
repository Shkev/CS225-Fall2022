/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
#include <cassert>
#include <iostream>
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    /**
     * @todo Implement this function.
     *
     */
    size_t idx = hashes::hash(key, size);
    table[idx].push_front({key, value});
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it = table[idx].begin();
    while (it->first != key) {
        it++;
    }
    if (it != table[idx].end()) {
        table[idx].erase(it);
    }
    elems--;
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    /**
     * @todo: Implement this function.
     */
    size_t idx = hashes::hash(key, size);
    for (std::pair<K, V> p : table[idx]) {
        if (p.first == key) {
            return p.second;
        }
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    size_t new_size = findPrime(2*size);
    std::list<std::pair<K, V>>* resized_table = new std::list<std::pair<K, V>>[new_size];
    for (size_t i = 0; i < size; ++i) { // rehash all table elements
        for (std::pair<K, V> p : table[i]) {
            size_t idx = hashes::hash(p.first, new_size);
            resized_table[idx].push_front({p.first, p.second});
        }
    }
    size = new_size;
    delete[] table;
    table = resized_table;
}
