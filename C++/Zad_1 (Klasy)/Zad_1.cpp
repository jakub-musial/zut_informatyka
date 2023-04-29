#include <iostream>

using namespace std;

class Trojkat
{
	//atrybuty
	float dlugosc_wysokosci;
	float dlugosc_podstawy;

public:
	//metody
	void wczytaj_wartosci()
	{
		cout << "Podaj dlugosc wysokosci trojkata: " << endl;
		cin >> dlugosc_wysokosci;
		cout << "Podaj dlugosc podstawy trojkata: " << endl;
		cin >> dlugosc_podstawy;
	}

	void wypisz_wartosci()
	{
		cout << "Dlugosc wysokosci trojkata jest rowna: " << dlugosc_wysokosci << endl;
		cout << "Dlugosc podstawy trojkata jest rowna: " << dlugosc_podstawy << endl;
	}

	float pole()
	{
		return (dlugosc_podstawy * dlugosc_wysokosci) / 2;
	}
};

int main()
{
	Trojkat trojkat;
	trojkat.wczytaj_wartosci();
	trojkat.wypisz_wartosci();
	cout << "Pole tego trojkata jest rowne: " << trojkat.pole();
}