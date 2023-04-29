#include <iostream>
#include <vector>

using namespace std;

void wypisz_wektor(vector<int>* v)
{
    for (auto element : *v)
    {
        cout << element << ", ";
    }
}

int main()
{
    //1.
    cout << "1) ";
    vector<int> v1{ 3, 50, 10 };
    wypisz_wektor(&v1);
    cout << endl << endl;

    //2.
    cout << "2) ";
    v1.emplace(v1.begin(), -50);
    wypisz_wektor(&v1);
    cout << endl << endl;
    
    //3.
    cout << "3) ";
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    wypisz_wektor(&v1);
    cout << endl << endl;

    //4.
    vector<int> v2{ 1, 2, 3 };

    //5.
    cout << "5) ";
    v1.insert(v1.begin() + 2, v2.begin(), v2.end());
    wypisz_wektor(&v1);
    cout << endl << endl;

    //6.
    int tab[5] = { -1,-2,-3,-4 };

    //7.
    cout << "7) ";
    v1.insert(v1.end(), tab, tab+4);
    wypisz_wektor(&v1);
    cout << endl << endl;

    //8.
    cout << "8) ";
    v1.erase(v1.begin() + 1, v1.begin() + 13);
    wypisz_wektor(&v1);
    cout << endl << endl;

    //9.
    cout << "9) " << endl;
    swap(v1, v2);
    cout << "wektor v1 = "; wypisz_wektor(&v1); cout << endl;
    cout << "wektor v2 = "; wypisz_wektor(&v2); cout << endl;
    cout << endl << endl;
}