#pragma once

#include <iostream>
//#include <cstdlib>

template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* prev_node = nullptr;
		Node* next_node = nullptr;
	};

	unsigned int size = 0;
	Node* head = nullptr; 
	Node* tail = nullptr;

public:
	LinkedList()  {}
	~LinkedList() { clear(); }
	
	void push_back(T new_data)
	{
		Node* new_node = new Node;
		
		if (head == nullptr) //if new_node is first node in Linked_list
		{
			new_node->prev_node = nullptr;
			head = new_node;
		}
		else
		{
			new_node->prev_node = tail;
			tail->next_node = new_node;
		}

		new_node->data = new_data;
		new_node->next_node = nullptr; //next_node always point at nullptr when new_node is last node
		tail = new_node;
		size++;
	}

	void push_front(T new_data)
	{
		Node* new_node = new Node;

		if (head == nullptr) //if new_node is first node in Linked_list
		{
			new_node->next_node = nullptr;
			tail = new_node;
		}
		else
		{
			new_node->next_node = head;
			head->prev_node = new_node;
		}

		new_node->data = new_data;
		new_node->prev_node = nullptr; //prev_node always point at nullptr when new_node is first node
		head = new_node;
		size++;
	}

	void pop_back()
	{
		Node* tmp = new Node;
		tmp = tail;

		if (head == tail) //if there is only one node
		{
			head = tail = nullptr;
		}
		else
		{
			(tail->prev_node)->next_node = nullptr;
			tail = tail->prev_node;
		}

		size--;
		delete tmp;
	}

	void pop_front()
	{
		Node* tmp = new Node;
		tmp = head;

		if (head == tail) //if there is only one node
		{
			head = tail = nullptr;
		}
		else
		{
			(head->next_node)->prev_node = nullptr;
			head = head->next_node;
		}

		size--;
		delete tmp;
	}

	Node* find(T cmp)
	{
		Node* curr_node = head;
		while (curr_node != nullptr)
		{
			if (curr_node->data == cmp) return curr_node; 

			curr_node = curr_node->next_node;
		}
		return nullptr;
	}

	Node* find(std::string key)
	{
		Node* curr_node = head;
		while (curr_node != nullptr)
		{
			if (curr_node->data.key == key) return curr_node;

			curr_node = curr_node->next_node;
		}
		return nullptr;
	}

	void remove(T cmp)
	{
		Node* curr_node = find(cmp);
		if (curr_node == nullptr)    std::cout << "Can't remove non-existing object" << std::endl; 
		else if (curr_node == head)  pop_front(); 
		else if (curr_node == tail)  pop_back();  
		else
		{
			(curr_node->next_node)->prev_node = curr_node->prev_node;
			(curr_node->prev_node)->next_node = curr_node->next_node;
			delete curr_node;
		}
		std::cout << "Successfully removed object" << std::endl;
	}

	bool remove(std::string key)
	{
		Node* curr_node = find(key);
		if (curr_node == nullptr)
		{
			return false;
		}

		else if (curr_node == head)
		{
			pop_front();
		}

		else if (curr_node == tail)
		{
			pop_back();
		}
		else
		{
			(curr_node->next_node)->prev_node = curr_node->prev_node;
			(curr_node->prev_node)->next_node = curr_node->next_node;
			delete curr_node;
		}
		return true;
	}

	void sorted_insert(T new_data)
	{
		if (head == nullptr || new_data <= head->data) 
		{
			push_front(new_data); 
		}
		else if (tail->data <= new_data)
		{
			push_back(new_data);
		}
		else
		{
			Node* curr_node = head;
			Node* new_node = new Node;
			while (curr_node != nullptr && curr_node->data <= new_data)
			{
				curr_node = curr_node->next_node;
			}
			//settings for new_node
			new_node->data = new_data;
			new_node->prev_node = curr_node->prev_node;
			new_node->next_node = curr_node;
			
			//settings for prev_node
			curr_node->prev_node->next_node = new_node;
			
			//settings for curr_node
			curr_node->prev_node = new_node;

			size++;
		}
	}

	void clear()//bool clear_data = false)
	{
		Node* curr_node = head;
		Node* next = nullptr;
		while (curr_node != nullptr)
		{
			next = curr_node->next_node;
			//delete(curr_node->data);
			delete(curr_node);
			curr_node = next;

		}
		delete curr_node;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void display()
	{
		//if (size > 0)
		//{
		//	std::cout << "***********************" << std::endl;
		//	std::cout << "Size: " << size << std::endl;
		//	std::cout << "Head: " << head << std::endl;
		//	std::cout << "Tail: " << tail << std::endl;
		//	std::cout << "***********************" << std::endl << std::endl;
		//}

		Node* tmp = head;
		std::cout << "Data: ";
		while (tmp != nullptr)
		{
			//std::cout << "Address: " << tmp << std::endl;
			std::cout << tmp->data << ",";
			//std::cout << "Preview node: " << tmp->prev_node << std::endl;
			//::cout << "Next node: " << tmp->next_node << std::endl << std::endl;
			tmp = tmp->next_node;
		}
		std::cout << std::endl;
	}

	unsigned int get_size() 
	{ 
		return size; 
	}

	T& operator [] (unsigned int index)
	{
		Node* curr_node = nullptr;

		if (index < 0 || index > size - 1 || size == 0)
		{
			printf("list index out of range");
			T* trash = new T;
			return *trash;
		}

		else if (index <= size / 2)
		{
			curr_node = head;
			for (unsigned int i = 0; i < index; i++)
			{
				curr_node = curr_node->next_node;
			}
			return curr_node->data;
		}
		else if (index > size / 2 )
		{
			curr_node = tail;
			for (unsigned int i = size - 1; i > index; i--)
			{
				curr_node = curr_node->prev_node;
			}
			return curr_node->data;
		}
	}
};

template<typename T>
bool operator <= (T& left, T& right)
{
	if (left.data <= right.data)      { return true;  }
	else if (left.data <= right.data) { return true;  }
	else                              { return false; }
}