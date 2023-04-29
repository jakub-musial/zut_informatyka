#include <iostream>

using namespace std;


class Prostokat
{
	private:

	float dlugosc;
	float szerokosc;

	public:

	Prostokat(float d, float sz)
	{
		dlugosc = d;
		szerokosc = sz;
	}

	Prostokat(const Prostokat &prostokat2)
	{
		dlugosc = prostokat2.dlugosc;
		szerokosc = prostokat2.szerokosc;
	}

	float pole()
	{
		return dlugosc * szerokosc;
	}

	float obwod()
	{
		return 2 * dlugosc + 2 * szerokosc;
	}

	void set_dlugosc(float d)
	{
		dlugosc = d;
	}

	void set_szerokosc(float sz)
	{
		szerokosc = sz;
	}
};

int main()
{
	cout << "PROSTOKAT" << endl << endl;

	Prostokat prostokat1(4, 5);
	cout << "Pole: " << prostokat1.pole() << endl;
	cout << "Obwod: " << prostokat1.obwod() << endl << endl;

	cout << "---------------------------------" << endl << endl;
	cout << "KOPIA PROSTKATA" << endl << endl;

	Prostokat prostokat2(prostokat1);
	cout << "Pole: " << prostokat2.pole() << endl;
	cout << "Obwod: " << prostokat2.obwod() << endl << endl;

	prostokat2.set_dlugosc(10);
	prostokat2.set_szerokosc(20);
	cout << "Pole: " << prostokat2.pole() << endl;
	cout << "Obwod: " << prostokat2.obwod() << endl;
}
