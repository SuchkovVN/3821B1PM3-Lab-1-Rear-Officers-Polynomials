#pragma once
#include<iostream>

template<class Key, class Data>
class TMap
{
protected:
	size_t size = 0;
	Data* data = nullptr;
	Key* key = nullptr;
	size_t count = 0;

public:
	TMap(size_t _size = 0);
	TMap(size_t _size, Key* _key, Data* _data);
	TMap(TMap<Key, Data>& Another_Map);
	//TMap(TMap<Key, Data>&& Another_Map) noexcept;
  ~TMap();
  size_t Size();
  size_t Count();
  Key GetKey(size_t ind);
  bool IsFull();
  void Insert(Key _key, Data _data);
  bool IsInsertKey(const Key _key) const;

  const Data& operator[] (Key _key) const;
  Data& operator[] (Key _key);
  bool operator == (const TMap<Key, Data>& map);
  bool operator != (const TMap<Key, Data>& map);
  TMap<Key, Data> operator = (const TMap<Key, Data>& map);
 //TMap<K, V> operator = (TMap<K, V>&& map);
  


};

template<class Key, class Data>
inline TMap<Key, Data>::TMap(size_t _size)// we can create array with size = 0, also we can delete this array witout excpetion 
{
  size = _size;
  data = new Data[_size];
  key = new Key[_size];
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(size_t _size, Key* _key, Data* _data) // arrays(Key*,Data*) must contains unique elements
{

  size = _size;
  count = _size;
  
  for (size_t i = 0; i < size; i++)
  {
    key[i] = _key[i];
    data[i] = _data[i];
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(TMap<Key, Data>& Another_Map)
{
  if (Another_Map.data == nullptr || Another_Map.key == nullptr)
  {
    data = nullptr;
    key = nullptr;
    size = 0;
    count = 0;
  }
  else
  {
    if (count > size) throw "Count greater than size! It's impossible!";
    size = Another_Map.size;
    count = Another_Map.count;
    data = new Data[size];
    key = new Key[size];

    for (size_t i = 0; i < count; i++)
    {
      data[i] = Another_Map.data[i];
      key[i] = Another_Map.key[i];
    }
  }
}

//template<class Key, class Data>
//inline TMap<Key, Data>::TMap(TMap<Key, Data>&& Another_Map)
//{
//  count = Another_Map.count;
//  size = Another_Map.size;
//  data = Another_Map.values;
//  key = Another_Map.keys;
//
//  Another_Map.count = 0;
//  Another_Map.size = 0;
//  Another_Map.key = nullptr;
//  Another_Map.data = nullptr;
//}

template<class Key, class Data>
inline TMap<Key, Data>::~TMap()
{
  if (data != nullptr)
  {
    delete[] data;
    data = nullptr;
  }
  if (key != nullptr)
  {
    delete[] key;
    key = nullptr;
  }
  
}

template<class Key, class Data>
inline size_t TMap<Key, Data>::Size()
{
  return size;
}

template<class Key, class Data>
inline size_t TMap<Key, Data>::Count()
{
  return count;
}

template<class Key, class Data>
inline Key TMap<Key, Data>::GetKey(size_t ind)
{ 
  if (ind >= 0 && ind < count)
    return key[ind];
  else 
    throw "Exception! Out of range in array Key* key";
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsFull()
{
  if (count == size)
    return true;
  else
    return false;
}

template<class Key, class Data>
inline void TMap<Key, Data>::Insert(Key _key, Data _data)
{
  for (size_t i = 0; i < count; i++)
  {
    if (key[i] == _key) throw "the elem with<key,data> is not unique!";
  }
  if (count == size)
  {
    Data* temp1 = new Data[size];
    Key* temp2 = new Key[size];
    
    for (size_t i = 0; i < count; i++)
    {
      temp1[i] = data[i];
      temp2[i] = key[i];
    }

    delete[] data;
    delete[] key;

    size = size * 2; // we will use one of the strategies for allocating space - multiplying the quantity by 2
    data = new Data[size];
    key = new Key[size];

    for (size_t i = 0; i < count; i++)
    {
      data[i] = temp1[i];
      key[i] = temp2[i];
    }

    delete[] temp1;
    temp1 = nullptr;
    delete[] temp2;
    temp2 = nullptr;

    key[count] = _key;
    data[count] = _data;
    count++;
  }
  else if ( count < size)
  {
    key[count] = _key;
    data[count] = _data;
    count++;
  }
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsInsertKey(const Key _key) const
{
  
  bool have_elem = false;
  for (size_t i = 0; i < count; i++)
  {
    if (key[i] == _key)
      return true;
  }
  if (have_elem == false)
    return false;
}

template<class Key, class Data>
inline const Data& TMap<Key, Data>::operator[](Key _key) const
{
  bool have_similar = false;
  for (size_t i = 0; i < count; i++)
  {
    if (key[i] == _key)
      return key[i];
    have_similar = true;
  }
  if (have_similar == false)
    throw "The map doesn't have this elem with this key";
}

template<class Key, class Data>
inline Data& TMap<Key, Data>::operator[](Key _key)
{
  bool have_similar = false;
  for (size_t i = 0; i < count; i++)
  {
    if (key[i] == _key)
      return data[i];
    have_similar = true;
  }
  if (have_similar == false)
    throw "The map doesn't have this elem with this key";
}

template<class Key, class Data>
inline bool TMap<Key, Data>::operator==(const TMap<Key, Data>& map)
{
  if (size != map.size || count != map.count)
    return false;
  for (size_t i = 0; i < size; i++)
    if (key[i] != map.key[i] || data[i] != map.data[i])
      return false;
  return true;
}

template<class Key, class Data>
inline bool TMap<Key, Data>::operator!=(const TMap<Key, Data>& map)
{

  return !(*this == map);
}

template<class Key, class Data>
inline TMap<Key, Data> TMap<Key, Data>::operator=(const TMap<Key, Data>& map)
{
  if (this != &map)
  {
    if (key != nullptr && data != nullptr)
    {
      delete[] key;
      key = nullptr;
      delete[] data;
      data = nullptr;
    }
    count = map.count;
    size = map.size;
    key = new Key[size];
    data = new Data[size];
    for (size_t i = 0; i < size; i++)
    {
      data[i] = map.data[i];
      key[i] = map.keys[i];
    }
  }
  else
    throw "copy itself";
  return *this;
}

