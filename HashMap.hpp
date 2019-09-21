#include <iostream>
#include <vector>
#include <iterator>
#include <cmath>
#include <exception>


#define ZERO 0
#define SIZE 16
#define UPPER 0.75
#define LOWER 0.25


template<class KeyT, class ValueT>
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 */
class HashMap
{

    using bucket = std::vector<std::pair<KeyT, ValueT>>;

private:
    int _size;
    int _capacity;
    double _uperload;
    double _lowerload;
    bucket *_table;
    /**
     *
     * @param keyT
     * @param flag
     * @return
     */
    int _getHash(const KeyT &keyT, int flag = 0) const;
    /**
     *
     * @param size
     * @return
     */
    int _findSize(long size);
    /**
     *
     */
    void _reHash();


public:
    using iter = typename bucket::iterator;

    /**
     *
     */
    HashMap();
    /**
     *
     * @param uperload
     * @param lowerload
     */
    HashMap(double uperload, double lowerload);
    /**
     *
     * @param v1
     * @param v2
     */
    HashMap(const std::vector<KeyT> &v1, const std::vector<ValueT> &v2);
    /**
     *
     * @param other
     */
    HashMap(const HashMap &other);
    /**
     *
     * @param other
     */
    HashMap(HashMap && other);
    /**
     *
     */
    ~HashMap()
    { delete[] _table; }
    /**
     *
     * @return
     */
    int size() const
    { return _size; }
    /**
     *
     * @return
     */
    int capacity() const
    { return _capacity; }
    /**
     *
     * @return
     */
    double getLoadFactor() const
    { return (double) _size / _capacity; }
    /**
     *
     * @return
     */
    bool empty() const;
    /**
     *
     * @param keyT
     * @param valueT
     * @return
     */
    bool insert(const KeyT &keyT, const ValueT &valueT);
    /**
     *
     * @param keyT
     * @return
     */
    bool containsKey(const KeyT &keyT) const;
    /**
     *
     * @param keyT
     * @return
     */
    ValueT &at(const KeyT &keyT);
    /**
     *
     * @param keyT
     * @return
     */
    ValueT at(const KeyT &keyT) const;
    /**
     *
     * @param keyT
     * @return
     */
    bool erase(const KeyT &keyT);
    /**
     *
     * @param keyT
     * @return
     */
    int bucketSize(const KeyT &keyT) const;
    /**
     *
     */
    void clear();
    /**
     *
     * @param other
     * @return
     */
    HashMap &operator=(const HashMap &other);
    /**
     *
     * @param other
     * @return
     */

    HashMap &operator=(const HashMap && other);
    /**
     *
     * @param keyT
     * @return
     */
    ValueT &operator[](const KeyT &keyT);
    /**
     *
     * @param keyT
     * @return
     */
    ValueT operator[](const KeyT &keyT) const;
    /**
     *
     * @param other
     * @return
     */
    bool operator==(const HashMap &other);
    /**
     *
     * @param other
     * @return
     */
    bool operator!=(const HashMap &other);

    /**
     *
     */
    class const_iterator
    {


    private:
        int _capacity;
        iter _prt;
        bucket *_bucket;
        int _cur = 0;


    public:
        /**
         *
         * @param table
         * @param capacity
         * @param i
         * @param it
         */
        const_iterator(bucket *table, int capacity, int i, iter it) : _capacity(capacity), _prt(it),
                                                                      _bucket(table), _cur(i)
        {

        }
        /**
         *
         * @return
         */
        const_iterator operator++()
        {
            if(++_prt != _bucket->end())
            {
                return *this;
            }
            while ((_bucket + 1)->empty())
            {
                _cur += 1;
                ++_bucket;
            }
            if(_cur<_capacity - 1)
            {
                ++_bucket;
                _cur += 1;
                _prt = _bucket->begin();
                return *this;
            }
            _prt = _bucket->end();
            return *this;


        }
        /**
         *
         * @return
         */
        const_iterator operator++(int)
        {
            const_iterator res = *this;
            ++*this;
            return res;

        }
        /**
         *
         * @return
         */
        const std::pair<KeyT, ValueT> &operator*()
        { return *_prt; }
        /**
         *
         * @return
         */
        std::pair<KeyT, ValueT> operator*() const
        { return *_prt; }
        /**
         *
         * @return
         */
        iter &operator->()
        { return _prt; }
        /**
         *
         * @param other
         * @return
         */
        bool operator==(const const_iterator &other) const
        { return _prt == other._prt; }
        /**
         *
         * @param other
         * @return
         */
        bool operator!=(const const_iterator &other) const
        { return _prt != other._prt; }


    };
    /**
     *
     * @return
     */
    const_iterator begin() const
    {
        for (int i = 0; i < _capacity; ++i)
        {
            if (!_table[i].empty())
            {
                return const_iterator(_table + i, _capacity, i, (_table + i)->begin());

            }
        }
        return end();
    }
    /**
     *
     * @return
     */
    const_iterator end() const
    {
        return const_iterator(_table + (_capacity - 1), _capacity, _capacity - 1, (_table + (_capacity - 1))->end());
    }
    /**
     *
     * @return
     */
    const const_iterator cbegin() const
    {
        for (int i = 0; i < _capacity; ++i)
        {
            if (!_table[i].empty())
            {
                return const_iterator(_table + i, _capacity, i, (_table + i)->begin());

            }
        }
        return end();
    }
    /**
     *
     * @return
     */
    const const_iterator cend() const
    {
        return const_iterator(_table + (_capacity - 1), _capacity, _capacity - 1, (_table + (_capacity - 1))->end());
    }


};


template<class KeyT, class ValueT>
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 */
HashMap<KeyT, ValueT>::HashMap():_size(ZERO), _capacity(SIZE), _uperload(UPPER), _lowerload(LOWER),
                                 _table(new bucket[_capacity])
{

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param lowerload
 * @param uperload
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(double lowerload, double uperload):_size(ZERO), _capacity(SIZE), _uperload(uperload),
                                                                  _lowerload(lowerload),
                                                                  _table(new bucket[_capacity])
{
    if (lowerload > uperload || lowerload <= 0 || uperload >= 1)
    {
        throw std::invalid_argument("lower biger from uper");
    }

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param v1
 * @param v2
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const std::vector<KeyT> &v1, const std::vector<ValueT> &v2)
{
    if (v1.size() != v2.size())
    {
        throw std::invalid_argument("the vector have diff size ");
    }

    _size = 0;
    _capacity = _findSize(_size);
    _uperload = UPPER;
    _lowerload = LOWER;
    _table = new bucket[_capacity];

    for (int i = 0; i < v1.size(); ++i)
    {
        if (!containsKey(v1[i]))
        {
            insert(v1[i], v2[i]);
        }
        else
        {
            this->operator[](v1[i]) = v2[i];
        }
    }


}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap &other):_size(other._size), _capacity(other._capacity),
                                                     _uperload(other._uperload), _lowerload(other._lowerload),
                                                     _table(new bucket[_capacity])
{
    for (int i = 0; i < _capacity; ++i)
    {
        if (!other._table[i].empty())
        {
            _table[i] = bucket(other._table[i]);
        }

    }
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashMap && other):_size(other._size), _capacity(other._capacity),
                                                _uperload(other._uperload), _lowerload(other._lowerload),
                                                _table(new bucket[_capacity])
{
    for (int i = 0; i < _capacity; ++i)
    {
        if (!other._table[i].empty())
        {
            _table[i] = other._table[i];
        }

    }
    other._table = nullptr;

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @param flag
 * @return
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::_getHash(const KeyT &keyT, int flag) const
{
    if (flag == 0)
    {
        return std::hash<KeyT>{}(keyT) & (_capacity - 1);
    }
    else if (flag == 1)
    {
        return std::hash<KeyT>{}(keyT) & ((_capacity * 2) - 1);
    }
    else
    {
        return std::hash<KeyT>{}(keyT) & ((_capacity / 2) - 1);
    }
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::empty() const
{
    return begin() == end();
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @param valueT
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::insert(const KeyT &keyT, const ValueT &valueT)
{
    if (containsKey(keyT))
    {
        return false;
    }
    _table[_getHash(keyT)].push_back(std::pair<KeyT, ValueT>(keyT, valueT));
    _size += 1;
    _reHash();
    return true;

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::containsKey(const KeyT &keyT) const
{
    if (_table[_getHash(keyT)].empty())
    {
        return false;
    }
    for (auto &pair : _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            return true;
        }
    }
    return false;

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::at(const KeyT &keyT)
{

    if (_table == nullptr)
    {
        throw std::out_of_range("this key not exsit");
    }
    for (auto &pair: _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            return pair.second;
        }
    }
    throw std::out_of_range("this key not exsit");


}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
ValueT HashMap<KeyT, ValueT>::at(const KeyT &keyT) const
{
    for (auto &pair: _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            return pair.second;
        }
    }
    throw std::out_of_range("this key not exsit");
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::erase(const KeyT &keyT)
{
    if (!containsKey(keyT))
    {
        return false;
    }
    auto it = _table[_getHash(keyT)].begin();
    for (auto &pair : _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            _table[_getHash(keyT)].erase(it);
            _size -= 1;
            _reHash();
            return true;
        }
        ++it;
    }
    return false;

}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::bucketSize(const KeyT &keyT) const
{
    if (!containsKey(keyT))
    {
        throw std::invalid_argument("Invaild key");
    }
    return (int) _table[_getHash(keyT)].size();
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 */
template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::clear()
{
    for (int i = 0; i < _capacity; ++i)
    {
        _table[i].clear();
    }
    _size = 0;
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 * @return
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &HashMap<KeyT, ValueT>::operator=(const HashMap &other)
{
    if (*this != other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _uperload = other._uperload;
        _lowerload = other._lowerload;
        delete[] _table;
        _table = nullptr;
        _table = new bucket[other._capacity];
        for (int i = 0; i < other._capacity; ++i)
        {
            _table[i] = other._table[i];
        }
        _reHash();


    }
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
ValueT &HashMap<KeyT, ValueT>::operator[](const KeyT &keyT)
{
    if (!containsKey(keyT))
    {
        ValueT valueT;
        insert(keyT, valueT);
    }
    for (auto &pair : _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            int num = _getHash(keyT);
            return pair.second;
        }
    }
    int num = _getHash(keyT);

    return _table[num].back().second;
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param keyT
 * @return
 */
template<class KeyT, class ValueT>
ValueT HashMap<KeyT, ValueT>::operator[](const KeyT &keyT) const
{
    for (auto &pair : _table[_getHash(keyT)])
    {
        if (pair.first == keyT)
        {
            return pair.second;
        }
    }
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator==(const HashMap &other)
{
    if (_capacity != other._capacity)
    {
        return false;
    }
    for (int i = 0; i < _capacity; ++i)
    {
        if (_table[i] != other._table[i])
        {
            return false;
        }
    }
    return true;
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 * @return
 */
template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::operator!=(const HashMap &other)
{
    return !(*this == other);
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param size
 * @return
 */
template<class KeyT, class ValueT>
int HashMap<KeyT, ValueT>::_findSize(long size)
{
    int i = 1;
    while (size > std::pow(2, i))
    {
        i *= 2;
    }
    if (size / std::pow(2, i) > UPPER)
    {
        return (int) std::pow(2, i + 1);
    }
    return (int) std::pow(2, i);
}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 */
template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::_reHash()
{
    int flag;
    if (getLoadFactor() >= _lowerload && getLoadFactor() <= _uperload)
    {
        return;
    }
    int resizenum;
    if (getLoadFactor() > _uperload)
    {
        resizenum = _capacity * 2;
        flag = 1;
    }
    else
    {

        resizenum = _capacity / 2;
        flag = 2;
    }
    bucket *newtable = new bucket[resizenum];
    for (auto it = begin(); it != end(); ++it)
    {
        newtable[_getHash(it->first, flag)].push_back(std::pair<KeyT, ValueT>(it->first, it->second));
    }
    delete[] _table;
    _capacity = resizenum;
    _table = newtable;


}
/**
 *
 * @tparam KeyT
 * @tparam ValueT
 * @param other
 * @return
 */
template<class KeyT, class ValueT>
HashMap<KeyT, ValueT> &HashMap<KeyT, ValueT>::operator=(const HashMap && other)
{
    if (*this != other)
    {
        _size = other._size;
        _capacity = other._capacity;
        _uperload = other._uperload;
        _lowerload = other._lowerload;
        delete[] _table;
        _table = nullptr;
        _table = other._table;
        other._table = nullptr;


    }
    return *this;
}








