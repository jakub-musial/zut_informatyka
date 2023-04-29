#include <iostream>
#include <cstdlib>
#include <time.h>
#include "DynamicArray.h"
#include "BinaryHeap.h"
#include "LinkedList.h"


using namespace std;

void counting_sort(DynamicArray<int>* array_ptr);
void bucket_sort(DynamicArray<double>* array_ptr);
void bucket_sort(DynamicArray<int>* array_ptr, int buckets_ammount = 10);

void counting_sort_stable(DynamicArray<int>* array_ptr);
void bucket_sort_dynamic_table(DynamicArray<double>* array_ptr);

int main()
{	
	DynamicArray<int> a;
	a.add(5); a.add(1); a.add(4); a.add(8); a.add(0);
	//a.add(2); a.add(3); a.add(1); a.add(7); a.add(0); a.add(4);

	BinaryHeap<int> bh(&a, false);
	bh.sort();

	//a.display();
}

void counting_sort(DynamicArray<int>* array_ptr)
{
	int max = array_ptr->operator[](0);
	for (size_t i = 0; i < array_ptr->get_size(); i++)
	{
		if (array_ptr->operator[](i) > max)
			max = array_ptr->operator[](i);
	}

	DynamicArray<int>* count_array = new DynamicArray<int>(max+1);
	for (size_t i = 0; i < max + 1; i++)
	{
		size_t counter = 0;
		for (size_t j = 0; j < array_ptr->get_size(); j++)
		{
			if (i == array_ptr->operator[](j))
			{
				counter++;
			}
		}
		count_array->add(counter);
	}

	int k = 0;
	for (size_t i = 0; i <= max; i++)
	{
		for (size_t j = 0; j < count_array->operator[](i); j++)
		{
			array_ptr->operator[](k++) = i;
		}
	}
}


void counting_sort_stable(DynamicArray<int>* array_ptr)
{
	int max = array_ptr->operator[](0);
	for (size_t i = 0; i < array_ptr->get_size(); i++)
	{
		if (array_ptr->operator[](i) > max)
			max = array_ptr->operator[](i);
	}

	DynamicArray<int>* count_array = new DynamicArray<int>(max+1);
	for (size_t i = 0; i < max+1; i++)
	{
		size_t counter = 0;
		for (size_t j = 0; j < array_ptr->get_size(); j++)
		{
			if (i == array_ptr->operator[](j))
			{
				counter++;
			}
		}
		count_array->add(counter);
	//	count_array->display();

		if (i > 0)
		{
			//std::cout << "count_array[" << i - 1 << "] = " << count_array->operator[](i - 1) << " + " << "count_array[" << i << "] = " << count_array->operator[](i) << std::endl;
			count_array->operator[](i) = count_array->operator[](i - 1) + count_array->operator[](i);
		}
	}
	
	DynamicArray<int>* output = new DynamicArray<int>(array_ptr->get_size());
	for (size_t i = 0; i < array_ptr->get_size(); i++)
	{
		output->operator[](count_array->operator[](array_ptr->operator[](i)) - 1) = array_ptr->operator[](i);
	}
	output->set_size(array_ptr->get_size());
	//output->display();
}


void bucket_sort_dynamic_table(DynamicArray<float>* array_ptr)
{
	size_t size = array_ptr->get_size();
	size_t index = 0;

	DynamicArray<float>* buckets = new DynamicArray<float>[size];

	for (size_t i = 0; i < size; i++)
	{
		index = array_ptr->operator[](i) * size;
		buckets[index].add(array_ptr->operator[](i));
		buckets[index].insertion_sort();
	}

	index = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (buckets[i].get_size() > 0)
		{
			for (size_t j = 0; j < buckets[i].get_size(); j++)
			{
				array_ptr->operator[](index) = buckets[i][j];
				index++;
			}
		}
	}
	delete[] buckets;
}

void bucket_sort(DynamicArray<double>* array_ptr)
{
	size_t size = array_ptr->get_size();
	size_t index = 0;

	LinkedList<double>* buckets = new LinkedList<double>[size];

	for (size_t i = 0; i < size; i++)
	{
		index = array_ptr->operator[](i) * size;
		buckets[index].sorted_insert(array_ptr->operator[](i));
	}

	index = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (buckets[i].get_size() > 0)
		{
			for (size_t j = 0; j < buckets[i].get_size(); j++)
			{
				array_ptr->operator[](index) = buckets[i][j];
				index++;
			}
		}
	}
	delete[] buckets;
}

void bucket_sort(DynamicArray<int>* array_ptr, int buckets_ammount)
{
	int min = array_ptr->operator[](0), max = array_ptr->operator[](0);
	for (size_t i = 1; i < array_ptr->get_size(); i++)
	{
		if (array_ptr->operator[](i) < min) min = array_ptr->operator[](i);
		else if (array_ptr->operator[](i) > max) max = array_ptr->operator[](i);
	}

	int range = (max - min) / buckets_ammount;
	LinkedList<double>* buckets = new LinkedList<double>[buckets_ammount];
	size_t index = 0;

	for (size_t i = 0; i < array_ptr->get_size(); i++)
	{

		index = array_ptr->operator[](i) / range;

		if (index <= buckets_ammount - 1)
			buckets[index].sorted_insert(array_ptr->operator[](i));
		else
			buckets[buckets_ammount-1].sorted_insert(array_ptr->operator[](i));
	}

	index = 0;
	for (size_t i = 0; i < buckets_ammount; i++)
	{
		if (buckets[i].get_size() > 0)
		{
			/*std::cout << "Size: " << buckets[i].get_size() << std::endl;
			std::cout << "zawartosc: ";*/
			for (size_t j = 0; j < buckets[i].get_size(); j++)
			{
				//std::cout << "[" << i << "]" << "[" << j <<"] = " << buckets[i][j] << ", ";
				array_ptr->operator[](index) = buckets[i][j];
				index++;
			}
			/*std::cout << std::endl;
			buckets[i].display();
			std::cout << std::endl;*/
		}
		//std::cout << buckets[i].get_size() << std::endl;
	}
	delete[] buckets;
}