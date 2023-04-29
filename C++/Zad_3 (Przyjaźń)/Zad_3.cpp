#include <iostream>

using namespace std;

class Macierz
{
private:
    static const int rozmiar = 3;
    float tablica[rozmiar][rozmiar];

public:
    static const int a = 4;

    Macierz()
    {
        for (int w = 0; w < rozmiar; w++)
            for (int k = 0; k < rozmiar; k++)
                tablica[w][k] = 0;
    }
    void wczytajDane()
    {
        for (int w = 0; w < rozmiar; w++)
            for (int k = 0; k < rozmiar; k++)
                cin >> tablica[w][k];
    }
    void wypisz()
    {
        for (int w = 0; w < rozmiar; w++)
        {
            cout << endl;
            for (int k = 0; k < 3; k++)
                cout << tablica[w][k] << " ";
        }

    }
    friend Macierz* dodajMacierze(Macierz* macierz1, Macierz* macierz2);
};


Macierz* dodajMacierze(Macierz* macierz1, Macierz* macierz2)
{
    Macierz* macierz_wynik = new Macierz;

    for (int w = 0; w < Macierz::rozmiar; w++)
        for (int k = 0; k < Macierz::rozmiar; k++)
            macierz_wynik->tablica[w][k] = macierz1->tablica[w][k] + macierz2->tablica[w][k];
    
    return macierz_wynik;
}

int main()
{
    Macierz* macierz_1 = new Macierz;
    Macierz* macierz_2 = new Macierz;

    cout << "Wypelnij macierz nr 1: " << endl;
    macierz_1->wczytajDane();
    macierz_1->wypisz();

    cout << endl << endl;

    cout << "Wypelnij macierz nr 2: " << endl;
    macierz_2->wczytajDane();
    macierz_2->wypisz();

    cout << endl << endl;


    cout << "Wynik dodawania macierzy 1 i 2:" << endl << endl;
    Macierz* macierz_3 = dodajMacierze(macierz_1, macierz_2);
    macierz_3->wypisz();

    return 0;
}