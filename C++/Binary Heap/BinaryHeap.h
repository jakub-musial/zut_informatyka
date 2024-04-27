#pragma once
#include "DynamicArray.h"

template <typename T>
class BinaryHeap
{
private:
	DynamicArray<T>* heap;

	void heapify_up(size_t i);
	void heapify_down(size_t i = 0);

public:
	BinaryHeap();

	void add(T data);
	void display();
	T pop();
	void clear();
};


template <typename T> BinaryHeap<T>::BinaryHeap() : heap(new DynamicArray<T>) {};

template <typename T> void BinaryHeap<T>::add(T data)
{
	heap->add(data);
	if (heap->get_size() > 1) heapify_up(heap->get_size()-1);
}

template <typename T> void BinaryHeap<T>::heapify_up(size_t i)
{
	if (i == 0) return;
	else if (heap->operator[](i) > heap->operator[]( (i-1)/2) ) heap->swap(i, (i-1)/2);
	
	heapify_up((i-1)/2);
}

template <typename T> void BinaryHeap<T>::heapify_down(size_t i)
{
	if (i == heap->get_size()-1  && 2*i+1 > heap->get_size()-1 && 2*i+2 > heap->get_size()-1)// || heap->operator[](i) >= heap->operator[](2*i+1) && heap->operator[](i) >= heap->operator[](2*i+2))
	{
		//std::cout << "RETURN: " << "[" << i << "] = " << heap->operator[](i) << std::endl;
		//std::cout << "2*i+1: " << heap->operator[](2 * i + 1) << "  " << "2*i+2: " << heap->operator[](2 * i + 2) << std::endl;
		return;
	}	
	else if (2*i+1 < heap->get_size() && heap->operator[](i) < heap->operator[](2 * i + 1) && heap->operator[](2 * i + 1) > heap->operator[](2 * i + 2))
	{
		//std::cout << "LEFT CHILD: " << "[" << i << "] <-> " << "[" << 2*i+1 << "]" << " = " << heap->operator[](i) << " <-> " << heap->operator[](2 * i + 1) << std::endl;
		heap->swap(i, 2 * i + 1);
		heapify_down(2 * i + 1);
	} 
	else if (2*i+2 < heap->get_size() && heap->operator[](i) < heap->operator[](2 * i + 2) && heap->operator[](2 * i + 2) > heap->operator[](2 * i + 1))
	{
		//std::cout << "RIGHT CHILD: " << "[" << i << "] <-> " << "[" << 2 * i + 1 << "]" << " = " << heap->operator[](i) << " <-> " << heap->operator[](2 * i + 2) << std::endl;
		heap->swap(i, 2 * i + 2);
		heapify_down(2 * i + 2);
	}
	return;
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
		//std::cout << "PRZED heapify_down: ";
		//for (size_t i = 0; i < heap->get_size(); i++) std::cout << heap->operator[](i) << ", "; std::cout << std::endl;
		heapify_down();
		//std::cout << std::endl; std::cout << "PO heapify_down: ";
		//for (size_t i = 0; i < heap->get_size(); i++) std::cout << heap->operator[](i) << ", "; std::cout << std::endl;
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