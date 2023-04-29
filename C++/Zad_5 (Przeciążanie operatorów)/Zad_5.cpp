#include <iostream>

using namespace std;

class Ulamek
{
	int licznik, mianownik;

	int nwd(int a, int b)
	{
		if (a != b)
			return nwd(a>b ? a-b : a, b>a ? b-a : b);
		return a;
	}
	int nww(int k, int n)
	{
		return (k*n) / nwd(k, n);
	}

	public:
	Ulamek() {}
	Ulamek(int l, int m)
	{
		licznik = l;

		if (m == 0)
		{
			cout << "Mianownik musi byc rozny od zera!" << endl;
			exit(0);
		}
		else
		{
			mianownik = m;
		}
	}

	void setLicznik(int l)
	{
		licznik = l;
	}

	void setMianownik(int m)
	{
		if (m == 0)
		{
			cout << "Mianownik musi byc rozny od zera!" << endl;
			exit(0);
		}
		else
		{
			mianownik = m;
		}
	}

	void wypisz()
	{
		cout << licznik << "/" << mianownik;
	}

	Ulamek operator + (const Ulamek &obj)
	{
		Ulamek wynik;
		if (mianownik != obj.mianownik)
		{
			int wm = nww(mianownik, obj.mianownik);
			wynik.licznik = licznik*(wm/mianownik) + obj.licznik*(wm/obj.mianownik);
			wynik.mianownik = wm;
			return wynik;
		}
		else
		{
			wynik.licznik = licznik + obj.licznik;
			wynik.mianownik = mianownik;
			return wynik;
		}
	}

	Ulamek operator - (const Ulamek &obj)
	{
		Ulamek wynik;
		if (mianownik != obj.mianownik)
		{
			int wm = nww(mianownik, obj.mianownik);
			wynik.licznik = licznik*(wm/mianownik) - obj.licznik*(wm/obj.mianownik);
			wynik.mianownik = wm;
			return wynik;
		}
		else
		{
			wynik.licznik = licznik - obj.licznik;
			wynik.mianownik = mianownik;
			return wynik;
		}
	}

	Ulamek operator * (const Ulamek &obj)
	{
		Ulamek wynik;
		wynik.licznik = licznik * obj.licznik;
		wynik.mianownik = mianownik * obj.mianownik;
		return wynik;
	}

	Ulamek operator / (const Ulamek& obj)
	{
		Ulamek wynik;
		wynik.licznik = licznik * obj.mianownik;
		wynik.mianownik = mianownik * obj.licznik;
		return wynik;
	}
};


int main()
{
	Ulamek u1, u2;

	int l, m;
	cout << "Ulamek_1:" << endl;
	cout << "Licznik: ";  cin >> l; u1.setLicznik(l);
	cout << "Mianownik: ";  cin >> m; u1.setMianownik(m);
	cout << endl << endl;

	cout << "Ulamek_2:" << endl;
	cout << "Licznik: ";  cin >> l; u2.setLicznik(l);
	cout << "Mianownik: ";  cin >> m; u2.setMianownik(m);
	cout << endl << endl;


	cout << "DODAWANIE" << endl;
	Ulamek u3 = u1 + u2;
	u3.wypisz();

	cout << endl<< endl << "ODEJMOWANIE" << endl;
	Ulamek u4 = u1 - u2;
	u4.wypisz();

	cout << endl << endl << "MNOZENIE" << endl;
	Ulamek u5 = u1 * u2;
	u5.wypisz();

	cout << endl << endl << "DZIELENIE" << endl;
	Ulamek u6 = u1 / u2;
	u6.wypisz();
	cout << endl;
}
