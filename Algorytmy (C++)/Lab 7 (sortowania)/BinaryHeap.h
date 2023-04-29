#pragma once
#include "DynamicArray.h"

template <typename T>
class BinaryHeap
{
private:
	DynamicArray<T>* heap;
	//T* heap;

	void heapify_up(size_t i);
	void heapify_down(size_t i = 0, size_t end = 0);

public:
	BinaryHeap();
	BinaryHeap(DynamicArray<T>* array_ptr, bool top_down = true); //, size_t table_size);

	void add(T data);
	void display();
	T pop();
	void clear();
	void sort();
};


template <typename T> BinaryHeap<T>::BinaryHeap() : heap(new DynamicArray<T>) {};

template <typename T> BinaryHeap<T>::BinaryHeap(DynamicArray<T>* array_ptr, bool top_down) //, size_t table_size)
{
	heap = array_ptr;

	// W£SANE V1
	//for (size_t i = heap->get_size(); i-- > 0;)
	//{
	//	if (top_down) heapify_down(i, heap->get_size()-1);
	//	else heapify_up(i);
	//}

	// W£ASNE V2
	//if (top_down)
	//	for (size_t i = 0; i < heap->get_size(); i++)
	//		heapify_down(i, heap->get_size() - 1);
	//else
	//	for (size_t i = heap->get_size() - 1; i-- > 0;)
	//		heapify_up(i);

	// Z WYK£ADU
	if (top_down)
		for (size_t i = 0; i < heap->get_size(); i++)
		{
			heapify_up(i);
		}
	else
		for (size_t i = heap->get_size() - 1; i-- > 0;)
		{
			heapify_down(i, heap->get_size() - 1);
		}
}

template <typename T> void BinaryHeap<T>::add(T data)
{
	heap->add(data);
	if (heap->get_size() > 1) heapify_up(heap->get_size()-1);
}

template <typename T> void BinaryHeap<T>::heapify_up(size_t i)
{
	if (i <= 0 ) return;
	else if (heap->operator[](i) > heap->operator[]( (i-1)/2) ) heap->swap(i, (i-1)/2);
	
	heapify_up((i-1)/2);
}

template <typename T> void BinaryHeap<T>::heapify_down(size_t i, size_t end)
{
	size_t swap_index = 0;

	if (i >= end)
	{
		return;
	}
	else if (2 * i + 1 <= end && 2 * i + 2 <= end) // node has two childrens
	{
		if (heap->operator[](i) < heap->operator[](2 * i + 1) && heap->operator[](2 * i + 1) >= heap->operator[](2 * i + 2))
		{
			swap_index = 2 * i + 1;
		}
		else if (heap->operator[](i) < heap->operator[](2 * i + 2) && heap->operator[](2 * i + 2) > heap->operator[](2 * i + 1))
		{
			swap_index = 2 * i + 2;
		}
	}
	else if (2 * i + 1 <= end && 2 * i + 2 > end && heap->operator[](i) < heap->operator[](2 * i + 1)) // node has only left child
	{
		swap_index = 2 * i + 1;
	}

	if (swap_index <= end && swap_index > 0)
	{
		heap->swap(i, swap_index);
		heapify_down(swap_index, end);
	}
}


template <typename T> T BinaryHeap<T>::pop()
{
	if (heap->get_size() > 1)
	{
		T result = heap->operator[](0);
		heap->operator[](0) = heap->operator[](heap->get_size() - 1);

		DynamicArray<T>* tmp = new DynamicArray<T>;
		for (size_t i = 0; i < heap->get_size()-1; i++)
		{
			tmp->add(heap->operator[](i));
		}
		delete heap;
		heap = tmp;
		heapify_down();
		return result;
	}
	else if (heap->get_size() == 1)
	{
		T result = heap->operator[](0);
		delete heap;
		heap = new DynamicArray<T>;
		return result;
	}
	else
	{
		std::cout << "Nothing to return, heap is empty" << std::endl;
		T* tmp = new T;
		return *tmp;
	}
}

template <typename T> void BinaryHeap<T>::display()
{
	heap->display();
	std::cout << std::endl;
}

template <typename T> void BinaryHeap<T>::clear()
{
	heap->clear();
}

template <typename T> void BinaryHeap<T>::sort()
{
	for (size_t i = heap->get_size() - 1; i > 0; i--)
	{
		heap->display();
		heap->swap(0, i);
		heap->display();
		heapify_down(0, i - 1);
		heap->display();
		std::cout << "--------------------------- \n";
	}
}