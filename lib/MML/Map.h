#pragma once
#include <iostream>
using namespace std;

template <class K, class V>
class TMap
{
protected:
  size_t size;
  V* values;
  K* keys;
  size_t count;
public:
  TMap(size_t sz, K* key, V* val);
  TMap(size_t sz = 1);
  TMap(const TMap<K, V>& map);
  TMap(TMap<K, V>&& map) noexcept;
  ~TMap();

  size_t Size();
  size_t Count();
  K GetKey(size_t ind);
  bool IsFull();
  void Insert(K key, V val, bool unique);
  bool IsInsertKey(const K key) const;

  const V& operator[] (K key) const;
  V& operator[] (K key);
  bool operator == (const TMap<K, V>& map);
  bool operator != (const TMap<K, V>& map);
  TMap<K, V> operator = (const TMap<K, V>& map);
  TMap<K, V> operator = (TMap<K, V>&& map);

  friend ostream& operator <<(ostream& ostr, const TMap<K, V>& map)
  {
    ostr << "Keys:\tValues:" << endl;
    for (size_t i = 0; i < map.count; i++)
    {
      ostr << map.keys[i] << "\t" << map.values[i] << endl;
    }
    return ostr;
  }

  friend istream& operator >>(istream& istr, TMap<K, V>& map)
  {
    V val;
    for (size_t i = 0; i < map.count; i++)
    {
      cout << "Value of key " << map.keys[i] << ":";
      istr >> val;
      map[map.keys[i]] = val;
    }
    return istr;
  }
};

template<class K, class V>
inline TMap<K, V>::TMap(size_t sz, K* key, V* val)
{
  if (val != nullptr && key != nullptr && sz != 0)
  {
    count = sz;
    size = sz;
    values = new V[size];
    keys = new K[size];
    for (size_t i = 0; i < size; i++)
    {
      values[i] = val[i];
      keys[i] = key[i];
    }
  }
  else
    throw "exeption";
}

template<class K, class V>
inline TMap<K, V>::TMap(size_t sz)
{
  if (sz != 0)
  {
    size = sz;
    count = 0;
    values = new V[size];
    keys = new K[size];
    for (size_t i = 0; i < size; i++)
    {
      values[i] = {};
      keys[i] = {};
    }
  }
  else
    throw out_of_range("size must be grather than zero");
}

template<class K, class V>
inline TMap<K, V>::TMap(const TMap<K, V>& map)
{
  if (map.values == nullptr || map.keys == nullptr)
  {
    values = nullptr;
    keys = nullptr;
    size = 0;
  }
  else
  {
    count = map.count;
    size = map.size;
    values = new V[size];
    keys = new K[size];
    for (size_t i = 0; i < size; i++)
    {
      values[i] = map.values[i];
      keys[i] = map.keys[i];
    }
  }
}

template<class K, class V>
inline TMap<K, V>::TMap(TMap<K, V>&& map) noexcept
{
  count = map.count
  size = map.size;
  values = map.values;
  keys = map.keys;

  map.count = 0;
  map.size = 0;
  map.keys = nullptr;
  map.values = nullptr;
}

template<class K, class V>
inline TMap<K, V>::~TMap()
{
  if (keys != nullptr && values != nullptr)
  {
    delete[] keys;
    delete[] values;
    size = 0;
    count = 0;
    keys = nullptr;
    values = nullptr;
  }
}

template<class K, class V>
inline size_t TMap<K, V>::Size()
{
  return size;
}

template<class K, class V>
inline size_t TMap<K, V>::Count()
{
  return count;
}

template<class K, class V>
inline K TMap<K, V>::GetKey(size_t ind)
{
  return keys[ind];
}

template<class K, class V>
inline bool TMap<K, V>::IsFull()
{
  return (size == count);
}

template<class K, class V>
inline void TMap<K, V>::Insert(K key, V val, bool unique)
{
  if (IsInsertKey(key) && unique)
  {
    for (size_t i = 0; i < size; i++)
      if (keys[i] == key)
        values[i] = val;
  }
  else
  {
    if (!IsFull())
    {
      keys[count] = key;
      values[count] = val;
      count++;
    }
    else
    {
      TMap<K, V> map(size * 2);
      for (size_t i = 0; i < count; i++)
      {
        map.values[i] = values[i];
        map.keys[i] = keys[i];
      }
      map.keys[count] = key;
      map.values[count] = val;
      map.count = count + 1;
      *this = map;
    }
  }
}

template<class K, class V>
inline bool TMap<K, V>::IsInsertKey(const K key) const
{
  for (size_t i = 0; i < size; i++)
    if (keys[i] == key)
      return true;
  return false;
}

template<class K, class V>
inline const V& TMap<K, V>::operator[](K key) const
{
  for (size_t i = 0; i < size; i++)
    if (keys[i] == key)
      return values[i];
  throw out_of_range("No such key");
}

template<class K, class V>
inline V& TMap<K, V>::operator[](K key)
{
  for (size_t i = 0; i < size; i++)
    if (keys[i] == key)
      return values[i];
  throw out_of_range("No such key");
}

template<class K, class V>
inline bool TMap<K, V>::operator==(const TMap<K, V>& map)
{
  if (size != map.size || count != map.count)
    return false;
  for (size_t i = 0; i < size; i++)
    if (keys[i] != map.keys[i] || values[i] != map.values[i])
      return false;
  return true;
}

template<class K, class V>
inline bool TMap<K, V>::operator!=(const TMap<K, V>& map)
{
  return !(*this == map);
}

template<class K, class V>
inline TMap<K, V> TMap<K, V>::operator=(const TMap<K, V>& map)
{
  if (this != &map)
  {
    if (keys != nullptr && values != nullptr)
    {
      delete[] keys;
      delete[] values;
    }
    count = map.count;
    size = map.size;
    keys = new K[size];
    values = new V[size];
    for (size_t i = 0; i < size; i++)
    {
      values[i] = map.values[i];
      keys[i] = map.keys[i];
    }
  }
  else
    throw "copy itself";
  return *this;
}

template<class K, class V>
inline TMap<K, V> TMap<K, V>::operator=(TMap<K, V>&& map)
{
  if (this != &map)
  {
    count = map.count;
    size = map.size;
    values = map.values;
    keys = map.keys;

    map.count = 0;
    map.size = 0;
    map.keys = nullptr;
    map.values = nullptr;
  }
  else
    throw "copy itself";
  return *this;
}

