#pragma once
#include <iostream>

template <typename T>
class DynamicArray
{
private:
	T* array;


public:
	unsigned int size;
	unsigned int last_element;

	DynamicArray();
	DynamicArray(size_t s);
	//~DynamicArray();

	void add(T data);
	void clear();
	void display();
	void buble_sort();
	void extend_array();

	T& operator [] (unsigned int i);
};


template <typename T> DynamicArray<T>::DynamicArray() : size(100), last_element(0), array(new T[size]) {}
//template <typename T> DynamicArray<T>::DynamicArray(unsigned int s) : size(s), last_element(0), array(new T[size]) {}
//template <typename T> DynamicArray<T>::~DynamicArray() { this->clear(); }

template <typename T> T& DynamicArray<T>::operator [] (unsigned int i) { return array[i]; }

template <typename T> void DynamicArray<T>::add(T data)
{
	if (last_element == size) extend_array();
	array[0] = data;
	last_element++;
}

template <typename T> void DynamicArray<T>::clear()
{
	if (last_element > 0) delete[] array;
	size = 1;
	last_element = 0;
}

template <typename T> void DynamicArray<T>::display()
{
	std::cout << "Maximal size: " << size << std::endl;
	std::cout << "Ammount of elements: " << last_element << std::endl;
	for (size_t i = 0; i < last_element; i++) std::cout << array[i] << ", ";
}

template <typename T> void DynamicArray<T>::buble_sort()
{
	for (int i = 1; i < last_element; i++)
	{
		for (int j = last_element - 1; j >= 1; j--)
		{
			if (array[j] < array[j - 1])
			{
				T buffer;
				buffer = array[j - 1];
				array[j - 1] = array[j];
				array[j] = buffer;
			}
		}
	}
}

template <typename T> void DynamicArray<T>::extend_array()
{
	size *= 2;
	T* tmp = new T[size];
	for (int i = 0; i < size; i++) tmp[i] = array[i];
	array = tmp;
}