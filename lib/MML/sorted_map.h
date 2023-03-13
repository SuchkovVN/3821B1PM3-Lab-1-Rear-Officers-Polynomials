#pragma once
#include<iostream>
#include"map.h"
#include"item.h"


template<class Key,class Data>
class TSMap : public TMap<Key,Data>
{
	protected:
		TItem<Key, Data>* items;
		size_t size = 0;
		size_t count = 0;
	public:
		TSMap(size_t _size = 100);
		void SetFirstObjects(TItem<Key, Data>& _item);
	//	void SetObjects(size_t _size, TItem<Key, Data>* _item);
		TSMap(const TSMap<Key, Data>& _map);
		~TSMap();
		
		Data* Find( Key& _key);
		void Add(Key* _key, Data* _data);
		void Delete( Key& _key);
		size_t BinarySearch(Key& _key);
};

template<class Key, class Data>
inline TSMap<Key, Data>::TSMap(size_t _size)
{ 
	if (_size > 0)
	{
		items = new TItem<Key,Data>[_size];
		size = _size;
	}
	size = _size;
	count = 0;
}

template<class Key, class Data>
inline void TSMap<Key, Data>::SetFirstObjects(TItem<Key, Data>& _item)
{
	if (count < size)
	{
		items[count].SetKey(_item.GetKey());
		items[count].SetData(_item.GetData());
		count++;
	}
}

//template<class Key, class Data>
//inline void TSMap<Key, Data>::SetObjects(size_t _size, TItem<Key, Data>* _item)
//{
//}

template<class Key, class Data>
inline TSMap<Key, Data>::TSMap(const TSMap<Key, Data>& _map)
{
	if (_map.items == nullptr) throw "empty object";
	size = _map.size;
	count = _map.count;
	items = new TItem<Key, Data>[_map.size];
	for (size_t i = 0; i < count; i++)
	{
		items[i].SetKey(_map.items[i].GetKey());
		items[i].SetData(_map.items[i].GetData());
	}

}

template<class Key, class Data>
inline TSMap<Key, Data>::~TSMap()
{
	if (items != nullptr)
		delete[] items;

}

//template<class Key, class Data>
//inline Data& TSMap<Key, Data>::operator[](const Key& _key)
//{
//	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// there's some kind of joke with this method. We are trying to return the link, but we are denied access to the "protected" field of the TItem class
//}

template<class Key, class Data>
inline Data* TSMap<Key, Data>::Find(Key& _key)
{
	if (BinarySearch(_key) >= 0)
		return(items[BinarySearch(_key)].GetData());
	else
		throw "Can't find the object with this key";
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Add(Key* _key, Data* _data)
{
	int q = 0;
	int i = 0;
	if (count == size)
	{
		TItem<Key, Data>* _items = new TItem<Key, Data>[size * 2];
		size = size * 2;

		for (size_t i = 0; i < count; i++)
		{
			_items[i].SetKey(*(items[i].GetKey()));
			_items[i].SetData(*(items[i].GetData()));
		}

		delete[] items;
		items = new TItem<Key, Data>[size];

		for (size_t i = 0; i < count; i++)
		{
			items[i].SetKey(*(_items[i].GetKey()));
			items[i].SetData(*(_items[i].GetData()));
		}
		delete[] _items;
		_items = nullptr;
	}

		size_t start = 0;
		size_t index = count / 2;
		size_t end = count - 1;
		Key k;
		while (start <= end)
		{
			if (*(items[index].GetKey()) == *(_key))
			{
				throw " this object is already in the array";
			}
			if (*(_key) > ( * (items[index].GetKey())))
			{
				start = index;
				index = (start + end) / 2;
			}
			if (*(_key) <  ( * (items[index].GetKey())))
			{
				end = index;
				index = (end - start) / 2;
			}
			if (start == end)
			{
				break;
				index = start;
			}
		}
	
		k = *(items[index].GetKey());
		if (*(_key) > k)
		{
			index++;
			TItem<Key, Data>* _items = new TItem<Key, Data>[size];

			for (i = 0; i < count; i++) //copying the array
			{
				_items[i].SetKey(*(items[i].GetKey()));
				_items[i].SetData(*(items[i].GetData()));
			}

			items[index].SetKey(_key);
			items[index].SetData(_data);

			i = index;
			count++;

			for (i = index; i < count; i++) 
			{
				items[i+1].SetKey(*(_items[i].GetKey()));
				items[i+1].SetData(*(_items[i].GetData()));
			}
			delete[] _items;
			_items = nullptr;
		}
		else if( (*(_key) > k) && index == 0 )
		{
			TItem<Key, Data>* _items = new TItem<Key, Data>[size];

			for (i = 0; i < count; i++) //copying the array
			{
				_items[i].SetKey(*(items[i].GetKey()));
				_items[i].SetData(*(items[i].GetData()));
			}

			items[index].SetKey(_key);
			items[index].SetData(_data);
			i = 1; count++;
			for (i = 1; i < count; i++)
			{
				items[i].SetKey(*(_items[i-1].GetKey()));
				items[i].SetData(*(_items[i-1].GetData()));
			}
			delete[] _items;
			_items = nullptr;
		}

		else if ( (*(_key) > k )&& index > 0 )
		{
			index--;
			TItem<Key, Data>* _items = new TItem<Key, Data>[size];

			for (i = 0; i < count; i++) //copying the array
			{
				_items[i].SetKey(*(items[i].GetKey()));
				_items[i].SetData(*(items[i].GetData()));
			}

			items[index].SetKey(_key);
			items[index].SetData(_data);

			i = index;
			count++;
			for (i = index; i < count; i++)
			{
				items[i].SetKey(*(_items[i - 1].GetKey()));
				items[i].SetData(*(_items[i - 1].GetData()));
			}
			delete[] _items;
			_items = nullptr;
		}	
	
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Delete( Key& _key)
{
	size_t index = BinarySearch(_key);
	if (index >= 0)
	{
		for (size_t i = index; i < count-1; i++)
		{
			items[i].SetKey(*(items[i+1].GetKey()));
			items[i].SetData(*(items[i+1].GetData()));
		}
		count--;
	}
	else
		throw "Can't find the object with this key";
}

template<class Key, class Data>
inline size_t TSMap<Key, Data>::BinarySearch(Key& _key)
{
	size_t start = 0;
	size_t index = count / 2;
	size_t end = count - 1;
	while (start <= end)
	{
		if (*(items[index].GetKey()) == _key)
		{
			return index;
		}
		if (_key > *(items[index].GetKey()))
		{
			start = index; 
			index = (start + end) / 2;
		}
		if (_key < *(items[index].GetKey()))
		{
			end = index;
			index = (end - start) / 2;
		}
		if (start == end)
		{
			return -1;
		}
	}
}


