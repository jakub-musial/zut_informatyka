#include "DynamicArray.h"

using namespace std;

int main()
{
    //DynamicArray<int> array;
    //
    //array.add(5);
    //array.add(10);
    //array.add(6);
    //array.add(3);
    //array.add(7);
    //array.add(20);

    //array.display();

    //cout << endl << endl << "array[3] = " << array[3] << endl;

    //cout << endl << endl << "zamien wartosc array[3] na 10" << endl; 
    //array[3] = 10;
    //cout << "array[3] = " << array[3] << endl;

    //cout << endl << endl << "Sortowanie babelkowe: " << endl;
    //array.buble_sort();
    //array.display();

    //cout << endl;

    //array.clear();
    //array.display();
    //cout << endl;
    //array.add(100);
    //array.add(200);
    //array.add(300);
    //array.display();


    DynamicArray<string> s;
    s.add("a");

    cout << "SIZE: " << s.size << endl;
    cout << "LAST ELEMENT: " << s.last_element << endl;

    s.display();
    return 0;
}
