#pragma once
#include <iostream>

template <typename T>
class DynamicArray
{
private:
	T* tab;
	size_t max_size;
	size_t size;

public:
	DynamicArray();
	DynamicArray(size_t s);
	~DynamicArray();

	void add(T data);
	void clear();
	void display();
	void buble_sort();
	void extend_array();
	void swap(size_t i1, size_t i2);
	size_t get_size();

	T& operator [] (unsigned int i);
};


template <typename T> DynamicArray<T>::DynamicArray() : size(0), max_size(1) , tab(new T[1]) {}
template <typename T> DynamicArray<T>::DynamicArray(size_t s) : max_size(s), size(0), tab(new T[max_size]) {}
template <typename T> DynamicArray<T>::~DynamicArray() { }//clear(); }

template <typename T> T& DynamicArray<T>::operator [] (unsigned int i) 
{ 
	return tab[i]; 
}

template <typename T> void DynamicArray<T>::add(T data)
{
	if (size == max_size) extend_array();
	tab[size] = data;
	size++;
}

template <typename T> void DynamicArray<T>::clear()
{
	if (size > 0) delete[] tab;
	max_size = 1;
	size = 0;
}

template <typename T> void DynamicArray<T>::display()
{
	std::cout << "Maximal size: " << max_size << std::endl;
	std::cout << "Ammount of elements: " << size << std::endl;
	for (size_t i = 0; i < size; i++) std::cout << tab[i] << ", ";
}

template <typename T> void DynamicArray<T>::buble_sort()
{
	for (int i = 1; i < size; i++)
	{
		for (int j = size - 1; j >= 1; j--)
		{
			if (tab[j] < tab[j - 1])
			{
				T buffer;
				buffer = tab[j - 1];
				tab[j - 1] = tab[j];
				tab[j] = buffer;
			}
		}
	}
}

template <typename T> void DynamicArray<T>::extend_array()
{
	max_size *= 2;
	T* tmp = new T[max_size];
	for (int i = 0; i < size; i++) tmp[i] = tab[i];
	delete[] tab;
	tab = tmp;
}

template <typename T> size_t DynamicArray<T>::get_size()
{
	return size;
}

template <typename T> void DynamicArray<T>::swap(size_t i1, size_t i2)
{
	T tmp = tab[i1];
	tab[i1] = tab[i2];
	tab[i2] = tmp;
}