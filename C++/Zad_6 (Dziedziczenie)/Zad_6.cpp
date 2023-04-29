#include <iostream>

using namespace std;

class Osoba
{   
    string imie, nazwisko;

public:
    Osoba() {}
    Osoba(string i, string n)
    {
        imie = i;
        nazwisko = n;
    }
    
    void wypisz()
    {
        cout << imie << " " << nazwisko;
    }
};

class Ksiazka
{
    string tytul;
    Osoba autor;

public:
    Ksiazka() {}
    Ksiazka(string t, string i, string n)
    {
        tytul = t;
        autor.Osoba::Osoba(i, n);
    }
    void wypisz()
    {
        cout << tytul << " "; autor.wypisz();
    }
};

class Czytelnik :public Osoba
{
    static const int rozmiar = 3;
    Ksiazka* przeczytane[rozmiar] = {};

public:
    Czytelnik(string i, string n) : Osoba(i, n) {}
    
    void setPrzeczytane(Ksiazka *k1, Ksiazka *k2, Ksiazka *k3)
    {
        przeczytane[0] = k1;
        przeczytane[1] = k2;
        przeczytane[2] = k3;

    }

    void wypiszKsiazki()
    {
        for (int i = 0; i < rozmiar; i++)
        {
            przeczytane[i]->wypisz(); 
            cout << endl;
        }
    }
};

int main()
{
    Ksiazka k1("Symfonia C++", "Jerzy", "Grebosz");
    Ksiazka k2("Opus magnum C++ 11", "Jerzy", "Grebosz");
    Ksiazka k3("Wladca Pierscieni", "John Ronald Reuel", "Tolkien");
    Ksiazka k4("Solaris", "Stanislaw", "Lem");
    Ksiazka k5("Rok 1984", "George", "Orwell");

    Czytelnik cz1("Jan", "Kowalski");
    Czytelnik cz2("Anna", "Nowak");
    Czytelnik cz3("Wojciech", "Suchodolski");

    cz1.setPrzeczytane(&k1,&k2,&k3);
    cz2.setPrzeczytane(&k1,&k4,&k5);
    cz3.setPrzeczytane(&k2,&k3,&k5);

    cz1.wypisz(); cout << ":" << endl; cz1.wypiszKsiazki(); cout << endl;
    cz2.wypisz(); cout << ":" << endl; cz2.wypiszKsiazki(); cout << endl;
    cz3.wypisz(); cout << ":" << endl; cz3.wypiszKsiazki(); cout << endl;
}