#include <iostream>
#include <cstdlib>
#include <time.h>
#include "HashTable.h"

int main()
{
	//HashTable<int> ht;

	//ht.display();

	//ht.add("aaa", 4);
	//ht.add("bbb", 6);
	//ht.add("ccc", 8);
	//ht.add("ddd", 10);
	//ht.add("fff", 101);
	//ht.add("g", 97);
	//ht.add("hhh", 16);
	//ht.add("ii", 20);

	//ht.display();

	//ht.clear();

	//ht.display();

	//ht.add("aaa", 8);

	//ht.display();
	
	HashTable<int> ht;

	size_t n = 0;
	std::cout << "Liczba obiektow w tablicy mieszjacej: ";
	std::cin >> n;
	std::cout << std::endl;

	srand(time(NULL));

	for (size_t i = 0; i < n; i++)
	{
		std::string key;
		for (int i = 0; i < 6; i++) key += rand() % 26 + 65;
		ht.add(key, rand() % 100000);
	}

	ht.display();




	 
}
