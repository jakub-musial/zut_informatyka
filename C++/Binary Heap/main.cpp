#include <iostream>
#include "BinaryHeap.h"

int main()
{
	BinaryHeap<int> bh;
	bh.add(19);
	bh.add(68);
	bh.add(15);
	bh.add(51);
	bh.add(50);
	bh.add(88);
	bh.add(59);
	bh.add(91);
	bh.add(31);
	bh.add(5);

	bh.display();
	bh.pop();
	bh.display();	
	bh.pop();
	bh.display();	
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();
	bh.pop();
	bh.display();

}   