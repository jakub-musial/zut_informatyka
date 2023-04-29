#ifndef ZMIENNE_H_INCLUDED
#define ZMIENNE_H_INCLUDED

#define NAZWAMIEJSCA 25
#define rozmiar 4

int choice, choice1, choice2;
char imie[10], rasa[10], plec[10], profesja[15];
//23.11.2021
int wydane_pkt;
int eq_size;
int dostepne_pkt;
int* atrybuty;
int** ekwipunek;
//05.12.2021
void ustaw_atrybut(int* tab, int indeks_atrybutu, int pkt);
void znajdz_przedmiot(int** ekwipunek, int indeks_przedmiotu);
void zapisz();
int losuj_przedmioty();
//12.01.2022
void jednowymiarowa(int** tab);
void init_1D(int* tab);
void remove_1D(int** tab);
void dwuwymiarowa(int*** tab, int size);
void init_2D(int** tab, int size);
void remove_2D(int** tab, int size);
//26.01.2022
struct Punkt;
struct Lokacja;
struct Lokacja losuj_lokacje();
void Menu();
#endif // ZMIENNE_H_INCLUDED
