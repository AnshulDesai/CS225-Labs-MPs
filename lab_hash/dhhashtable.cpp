/**
 * @file dhhashtable.cpp
 * Implementation of the DHHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "dhhashtable.h"

using hashes::hash;
using hashes::secondary_hash;
using std::pair;


template <class K, class V>
DHHashTable<K, V>::DHHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
DHHashTable<K, V>::~DHHashTable()
{
    destroy();
}

template <class K, class V>
DHHashTable<K, V> const& DHHashTable<K, V>::operator=(DHHashTable const& rhs)
{
    if (this != &rhs) {
        destroy();

        copy(rhs);
    }
    return *this;
}

template <class K, class V>
DHHashTable<K, V>::DHHashTable(DHHashTable<K, V> const& other)
{
    copy(other);
}


template <class K, class V>
void DHHashTable<K, V>::destroy()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table; table = nullptr;
    delete[] should_probe; should_probe = nullptr;
}

template <class K, class V>
void DHHashTable<K, V>::copy(const DHHashTable<K, V>& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void DHHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >=
     *  0.7). **Do this check *after* increasing elems!!** Also, don't
     *  forget to mark the cell for probing with should_probe!
     */
     elems++;
     if(shouldResize()) {
       resizeTable();
     }

     size_t index = hash(key, size);
     while(table[index] != NULL){
       index = (index + secondary_hash(key, size)) % size;
     }
    should_probe[index] = true;
     table[index] = new pair<K, V>(key, value);

    // prevent warnings... When you implement this function, remove this line.
    // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
void DHHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo Implement this function
     */
     int index = findIndex(key);
     if(index > -1) {
       elems--;
       delete table[index];
       table[index] = NULL;
     }
}

template <class K, class V>
int DHHashTable<K, V>::findIndex(const K& key) const
{
    /**
     * @todo Implement this function
     */
     size_t index = hash(key, size);
     size_t start = hash(key, size);
     while(should_probe[index]) {
       if(table[index] != NULL && table[index]->first == key){
         return index;
       }
       index = (index + secondary_hash(key, size)) % size;
       if(index == start)
       {
         break;
       }
     }
    return -1;
}

template <class K, class V>
V DHHashTable<K, V>::find(K const& key) const
{
    int index = findIndex(key);
    if (index != -1) {
      return table[index]->second;
    }
    return V();
}

template <class K, class V>
V& DHHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool DHHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void DHHashTable<K, V>::clear()
{
    destroy();

    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void DHHashTable<K, V>::resizeTable()
{
    size_t sizeNew = findPrime(size * 2);
    pair<K, V>** tempTable = new pair<K, V>*[sizeNew];

    delete[] should_probe;
    should_probe = new bool[sizeNew];

    for (size_t i = 0; i < sizeNew; i++) {
        tempTable[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            size_t hashVal = hash(table[i]->first, sizeNew);
            size_t diff = secondary_hash(table[i]->first, sizeNew);
            size_t start = 0;
            size_t index = hashVal;
            while (tempTable[index] != NULL)
            {
                ++start;
                index = (hashVal + diff * start) % sizeNew;
            }
            tempTable[index] = table[i];
            should_probe[index] = true;
        }
    }

    size = sizeNew;
    delete[] table;
    table = tempTable;
}
