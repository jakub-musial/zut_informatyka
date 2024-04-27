#pragma once
#pragma once
#include <iostream>
#include <cmath>
#include "LinkedList.h"


template <typename T>
struct Entry
{
	std::string key;
	T value;

	Entry() : key(""), value(NULL) {}
	Entry(std::string k, T v) : key(k), value(v) {}
};

template <typename T>
class HashTable
{
private:
	size_t size, max_size;
	LinkedList<Entry<T>>* table;

public:
	HashTable();
	~HashTable();
	void add(std::string key, T value);
	size_t hash(std::string key);
	void rehash();
	void display();
	bool remove(std::string key);
	void clear();

	Entry<T>& operator [] (std::string key);
};


template <typename T> HashTable<T>::HashTable() : size(0), max_size(2), table(new LinkedList<Entry<T>>[max_size]) {}
template <typename T> HashTable<T>::~HashTable() { delete[] table; }

template <typename T> void HashTable<T>::add(std::string key, T value)
{
	if (size >= 0.75 * max_size)
	{
		rehash();
	}

	size_t h = hash(key);
	Entry<T> entry(key, value);

	if (table[h].get_size() > 0)
	{
		for (size_t i = 0; i < table[h].get_size(); i++)
		{
			if (table[h][i].key == key)
			{
				table[h][i].value = value;
				return;
			}
		}
	}
	table[h].push_back(entry);
	size++;
}

template <typename T> size_t HashTable<T>::hash(std::string key)
{
	size_t hash = 0;
	size_t key_length = key.length();
	for (size_t i = 0; i < key_length; i++)
	{
		hash += key[i] * pow(31, key_length -i-1);
	}

	return hash %= max_size;
}

template <typename T> void HashTable<T>::rehash()
{
	max_size *= 2;
	LinkedList<Entry<T>>* tmp = new LinkedList<Entry<int>>[max_size];
	for (size_t i = 0; i < max_size/2; i++)
	{
		for (size_t j = 0; j < table[i].get_size(); j++)
		{
			tmp[hash(table[i][j].key)].push_back(table[i][j]);
		}
	}
	table = tmp;
}

template <typename T> void HashTable<T>::display()
{
	size_t list_min_size = 1, list_max_size = 1, non_null_lists = 0; 
	float list_avg_size = 0;

	std::cout << "Hash Table: " << std::endl;
	std::cout << "	Current size: " << size << std::endl;
	std::cout << "	Max size: " << max_size << std::endl;
	std::cout << "	Table: " << std::endl;
	std::cout << "	{ " << std::endl;
	for (size_t i = 0; i < max_size; i++)
	{
		if (table[i].get_size() > 0)
		{
			std::cout << "		" << i << ": ";
			for (size_t j = 0; j < table[i].get_size(); j++)
			{
				std::cout << " " << table[i][j].key << " -> " << table[i][j].value << ";";
			}
			std::cout << std::endl;

			// stats collector
			if (table[i].get_size() < list_min_size) list_min_size = table[i].get_size();
			if (table[i].get_size() > list_max_size) list_max_size = table[i].get_size();
			list_avg_size += (double)table[i].get_size() / (double)size;
			non_null_lists++;
		}
	}
	std::cout << "	} " << std::endl;
	std::cout << "	Stats:" << std::endl;
	std::cout << "		list min size: " << list_min_size << std::endl;
	std::cout << "		list max size: " << list_max_size << std::endl;
	std::cout << "		non-null lists: " << non_null_lists << std::endl;
	std::cout << "		list avg size: " << list_avg_size << std::endl;
}

template <typename T> bool HashTable<T>::remove(std::string key)
{
	size_t h = hash(key);

	if (table[h].get_size() > 0)
	{
		return table[h].remove(key);
	}
}

template <typename T> void HashTable<T>::clear()
{
	delete[] table;
	max_size = 2;
	size = 0;
	table = new LinkedList<Entry<T>>[max_size];

}

template <typename T> Entry<T>& HashTable<T>::operator[] (std::string key)
{
	size_t h = hash(key);

	if (table[h].get_size() > 0)
	{
		for (size_t i = 0; i < table[h].get_size(); i++)
		{
			if (table[h][i].key == key)
			{
				return table[h][i];
			}
		}
	}
	std::cout << "Item not found" << std::endl;
}