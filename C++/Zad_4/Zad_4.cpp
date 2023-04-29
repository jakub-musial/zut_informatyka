#include <iostream>

using namespace std;

class Pracownik
{
    string imie, nazwisko, stanowisko;
    float stawka;

    public:
    //setters
    void setImie(string s) { imie = s; }
    void setNazwisko(string s) { nazwisko = s; }
    void setStanowisko(string s) { stanowisko = s; }
    void setStawka(float f) { stawka = f; }

    //getters
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    string getStanowisko() { return stanowisko; }
    float getStawka() { return stawka; }

    Pracownik(string im="brak", string na="brak", string st="brak", float s=0)
    {
        imie = im;
        nazwisko = na;
        stanowisko = st;
        stawka = s;
    }
};

class Firma
{
    static const int rozmiar = 3;
    Pracownik* tablica[rozmiar];


    public:
    void dodajPracownikow()
    {
        string imie, nazwisko, stanowisko;
        float stawka;
        cout << "Wprowadz dane pracownikow: " << endl<< endl;
        for (int i = 0; i < 3; i++)
        {
            tablica[i] = new Pracownik;
            cout << "Pracownik nr " << i + 1 << endl;
            cout << "Imie: "; cin >> imie; tablica[i]->setImie(imie);
            cout << "Nazwisko: "; cin >> nazwisko; tablica[i]->setNazwisko(nazwisko);
            cout << "Stanowisko: "; cin >> stanowisko; tablica[i]->setStanowisko(stanowisko);
            cout << "Stawka: "; cin >> stawka; tablica[i]->setStawka(stawka);
            cout << endl;
        }
    }
    void wypiszDane()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << "Dane pracownika nr " << i + 1 << endl;
            cout << "Imie: " << tablica[i]->getImie() << endl;
            cout << "Nazwisko: " << tablica[i]->getNazwisko() << endl;
            cout << "Stanowisko: " << tablica[i]->getStanowisko() << endl;
            cout << "Stawka: " << tablica[i]->getStawka() << endl << endl;
        }
    }
};


int main()
{
    Firma firma;
    firma.dodajPracownikow();
    firma.wypiszDane();
}