#pragma once
#include<iostream>

template<class Key, class Data>
class TItem
{
protected:
	Key* key = nullptr;
	Data* data = nullptr;
public:
	TItem();
	TItem(Key _key, Data _data );
	TItem(Key& _key, Data& _data);
	TItem(Key* _key , Data* _data );

	TItem(const TItem<Key, Data>& _item);

	~TItem();
	Key* GetKey();
	void SetKey(Key _key);
	void SetKey(Key* _key);
	Data* GetData();
	void SetData(Data _data);
	void SetData(Data* _data);
	bool operator == (const TItem<Key, Data>& _item);
	bool operator != (const TItem<Key, Data>& _item);
	bool operator > (const TItem<Key, Data>& _item);
	bool operator < (const TItem<Key, Data>& _item);
};



template<class Key, class Data>
inline TItem<Key, Data>::TItem()
{
	key = new Key;
	data = new Data;
}

template<class Key, class Data>
inline TItem<Key, Data>::TItem(Key _key, Data _data )
{
	key = new Key;
	data = new Data;
	*key = _key;
	*data = _data;

}

template<class Key, class Data>
inline TItem<Key, Data>::TItem(Key& _key, Data& _data)
{
	key = new Key;
	data = new Data;

	*key = _key;
	*data = _data;
}

template<class Key, class Data>
inline TItem<Key, Data>::TItem(Key* _key, Data* _data)
{
	key = new Key;
	data = new Data;

	key = _key;
	data = _data;
}

template<class Key, class Data>
inline TItem<Key, Data>::TItem(const TItem<Key, Data>& _item)
{
	if (_item.data == nullptr || _item.key == nullptr) throw "empty object";
	else
	{
		data = new Data;
		data = _item.data;
		key = new Key;
		key = _item.key;
	}
}

template<class Key, class Data>
inline TItem<Key, Data>::~TItem()
{
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
	if (key != nullptr)
	{
		delete key;
		key = nullptr;
	}

}

template<class Key, class Data>
inline Key* TItem<Key, Data>::GetKey()
{
	return key;
}

template<class Key, class Data>
inline void TItem<Key, Data>::SetKey(Key _key)
{
	*key = _key;
}
template<class Key, class Data>
inline void TItem<Key, Data>::SetKey(Key* _key)
{
	*key = *(_key);
}
template<class Key, class Data>
inline Data* TItem<Key, Data>::GetData()
{
	return data;
}

template<class Key, class Data>
inline void TItem<Key, Data>::SetData(Data _data)
{
	*data = _data;
}
template<class Key, class Data>
inline void TItem<Key, Data>::SetData(Data* _data)
{
	*data = *(_data);
}
template<class Key, class Data>
inline bool TItem<Key, Data>::operator ==(const TItem<Key, Data>& _item)
{
	if (this == &_item) return true;
	else
		if (*key != *(_item.key)) return false;
		else 
			return true;
}
template<class Key, class Data>
inline bool TItem<Key, Data>::operator !=(const TItem<Key, Data>& _item)
{
	return(!(*this) == _item);
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator >(const TItem<Key, Data>& _item)
{
	if (*key > *(_item.key))
		return true;
	else 
		return false;
}
template<class Key, class Data>
inline bool TItem<Key, Data > ::operator <(const TItem<Key, Data>& _item)
{

	if (*key < *(_item.key))
		return true;
	else 
		return false;
}


