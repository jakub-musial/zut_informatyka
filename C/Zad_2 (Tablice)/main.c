#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//07.11.2021
int choice, choice1, choice2;
char imie[10], rasa[10], plec[10], profesja[15];

//23.11.2021
int wydane_pkt;
int eq_size;
#define rozmiar 4
int pkt = 20;
int atrybuty[rozmiar] = { 0, 0, 0, 0 };


int main()
{

	system("cls");
	do
	{
		system("cls");
		printf_s("KREATOR POSTACI\n\n");
		printf_s("1.Nowa Postac\n");
		printf_s("2.Stworzona Postac\n");
		printf_s("3.Atrybuty <--[Tablice]\n");
		printf_s("4.Ekwipunek <--[Tablice]\n");
		printf_s("0.Wyjscie\n\n");
		printf_s("Wybierz opcje: ");
		scanf_s("%d", &choice);
		getchar();

		switch (choice)
		{
		default:
			printf_s("Nie ma takiej opcji");
			system("timeout 5");
			system("cls");
			break;

		case 1: //NOWA POSTAC
			do
			{
				system("cls");
				printf_s("NOWA POSTAC\n\n");
				printf_s("1.Imie: %s\n", imie);
				printf_s("2.Rasa: %s\n", rasa);
				printf_s("3.Plec: %s\n", plec);
				printf_s("4.Profesja: %s\n", profesja);
				printf_s("0.Powrot\n");
				printf_s("Wybierz opcje: ");
				scanf_s("%d", &choice1);
				getchar();

				switch (choice1)
				{
				default:
					printf_s("Nie ma takiej opcji");
					system("timeout 5");
					system("cls");
					break;
				case 1: //NOWA POSTAC/IMIE
					system("cls");
					printf_s("Podaj swe imie: ");
					scanf_s("%s", imie, 10);
					break;
				case 2: //NOWA POSTAC/RASA
					do
					{
						system("cls");
						printf_s("RASA\n\n");
						printf_s("1.Czlowiek\n");
						printf_s("2.Elf\n");
						printf_s("3.Ork\n");
						printf_s("4.Krasnolud\n");
						printf_s("5.Niziolek\n");
						printf_s("0.Powrot\n");
						printf_s("Wybierz opcje: ");
						scanf_s("%d", &choice2);
						getchar();
						switch (choice2)
						{
						default:
							printf_s("Nie ma takiej opcji");
							system("timeout 5");
							system("cls");
							break;
						case 1:
							strcpy_s(rasa, 10, "Czlowiek");
							break;
						case 2:
							strcpy_s(rasa, 10, "Elf");
							break;
						case 3:
							strcpy_s(rasa, 10, "Ork");
							break;
						case 4:
							strcpy_s(rasa, 10, "Krasnolud");
							break;
						case 5:
							strcpy_s(rasa, 10, "Niziolek");
							break;
						case 0:
							system("cls");
							break;
						}
						break;
					} while (choice2 != 0);
					break;
				case 3: //NOWA POSTAC/PLEC
					do
					{
						system("cls");
						printf_s("PLEC\n\n");
						printf_s("1.Kobieta\n");
						printf_s("2.Mezczyzna\n");
						printf_s("0.Powrot\n");
						printf_s("Wybierz opcje: ");
						scanf_s("%d", &choice2);
						switch (choice2)
						{
						case 1:
							strcpy_s(plec, 10, "Kobieta");
							break;
						case 2:
							strcpy_s(plec, 10, "Mezczyzna");
							break;
						}
						break;
					} while (choice2 != 0);
					break;
				case 4: //NOWA POSTAC/PROFESJA
					do
					{
						system("cls");
						printf_s("PROFESJA\n\n");
						printf_s("1.Wojownik\n");
						printf_s("2.Lotr\n");
						printf_s("3.Lowca\n");
						printf_s("4.Skrytobojca\n");
						printf_s("5.Mag\n");
						printf_s("0.Powrot\n");
						printf_s("Wybierz opcje: ");
						scanf_s("%d", &choice2);
						switch (choice2)
						{
						default:
							printf_s("Nie ma takiej opcji");
							system("timeout 5");
							system("cls");
							break;
						case 0:
							break;
						case 1:
							strcpy_s(profesja, 10, "Wojownik");
							break;
						case 2:
							strcpy_s(profesja, 10, "Lotr");
							break;
						case 3:
							strcpy_s(profesja, 10, "Lowca");
							break;
						case 4:
							strcpy_s(profesja, 10, "Skrytobojca");
							break;
						case 5:
							strcpy_s(profesja, 10, "Mag");
							break;
						}
						break;
					} while (choice2 != 0);
					break;
				case 0: //NOWA POSTAC/EXIT
					break;
				}

			} while (choice1 != 0);
			break;
		case 2: //STWORZONA POSTAC
			do
			{
				system("cls");
				if (strlen(imie) == 0 || strlen(rasa) == 0 || strlen(plec) == 0 || strlen(profesja) == 0)
				{
					printf_s("Nie posiadasz jeszcze zadnej postaci\n\n");
					printf_s("Wcisnij ENTER aby wyjsc");
					while (getchar() != '\n');
				}
				else
				{
					printf_s("\033[0;37m TWOJA POSTAC\n\n");
					printf_s("\033[0;37m Imie: \033[1;31m %s \n", imie);
					printf_s("\033[0;37m Rasa:\033[0;32m %s \n", rasa);
					printf_s("\033[0;37m Plec: \033[0;33m %s \n", plec);
					printf_s("\033[0;37m Profesja: \033[0;35m %s \n\n", profesja);
					printf_s("\033[0;37m Wcisnij ENTER aby wyjsc");
					while (getchar() != '\n');
					break;
				}
			} while (choice2 != 0);
			break;
		case 3: //ATRYBUTY
			do
			{
				system("cls");
				printf_s("ATRYBUTY\n\n");
				printf_s("1.Sila: %d\n", atrybuty[0]);
				printf_s("2.Zrecznosc: %d\n", atrybuty[1]);
				printf_s("3.Moc: %d\n", atrybuty[2]);
				printf_s("4.Wytrzymalosc: %d\n", atrybuty[3]);
				printf_s("0.Powrot\n");
				printf_s("								pkt do wydania: %d\n", pkt);
				printf_s("Ktory atrybut chcesz rozwinac: ");
				scanf_s("%d", &choice2);
				switch (choice2)
				{
				default:
					printf_s("Nie ma takiej opcji");
					system("timeout 5");
					system("cls");
					break;
				case 0:
					break;
				case 1:
					printf_s("Ile punktow przeznaczysz na sile: ");
					scanf_s("%d", &wydane_pkt);
					if (atrybuty[0] != 0)
					{
						pkt += atrybuty[0];
					}

					if (wydane_pkt > pkt)
					{
						printf_s("Nie posiadasz takiej ilosci punktow");
						system("timeout 5");
						system("cls");
					}
					else
					{
						pkt -= wydane_pkt;
						atrybuty[0] = wydane_pkt;
					}
					break;
				case 2:
					printf_s("Ile punktow przeznaczysz na zrecznosc: ");
					scanf_s("%d", &wydane_pkt);
					if (atrybuty[1] != 0)
					{
						pkt += atrybuty[1];
					}

					if (wydane_pkt > pkt)
					{
						printf_s("Nie posiadasz takiej ilosci punktow");
						system("timeout 5");
						system("cls");
					}
					else
					{
						pkt -= wydane_pkt;
						atrybuty[1] = wydane_pkt;
					}
					break;
				case 3:
					printf_s("Ile punktow przeznaczysz na moc: ");
					scanf_s("%d", &wydane_pkt);
					if (atrybuty[2] != 0)
					{
						pkt += atrybuty[2];
					}

					if (wydane_pkt > pkt)
					{
						printf_s("Nie posiadasz takiej ilosci punktow");
						system("timeout 5");
						system("cls");
					}
					else
					{
						pkt -= wydane_pkt;
						atrybuty[2] = wydane_pkt;
					}
					break;
				case 4:
					printf_s("Ile punktow przeznaczysz na wytrzymalosc: ");
					scanf_s("%d", &wydane_pkt);
					if (atrybuty[3] != 0)
					{
						pkt += atrybuty[3];
					}

					if (wydane_pkt > pkt)
					{
						printf_s("Nie posiadasz takiej ilosci punktow");
						system("timeout 5");
						system("cls");
					}
					else
					{
						pkt -= wydane_pkt;
						atrybuty[3] = wydane_pkt;
					}
					break;
				}

			} while (choice2 != 0);
			break;
		case 4:
			do
			{
				system("cls");
				if (atrybuty[0] == 0)
				{
					printf_s("Wilkosc ekwipunku jest zalezna od ilosci punktow wydanych w atrybut sily");
					while (getchar() != '\n');
				}
				else
				{
					eq_size = atrybuty[0];
					int ekwipunek[eq_size][eq_size];
					for (int i = 0; i < eq_size; i++)
                        for (int j = 0; j < eq_size; j++)
                        {
                            ekwipunek[i][j] = rand() % 5 + 1;
                        }
					printf_s("EKWIPUNEK\n\n");
					printf_s("Wielkosc ekwipunku [%d][%d]\n\n", eq_size, eq_size);
					printf_s("Lista przedmiotow:\n");
					printf_s("1.Miecz\n");
					printf_s("2.Tarcza\n");
					printf_s("3.Luk\n");
					printf_s("4.Amulet\n");
					printf_s("5.Chleb\n");
					printf_s("Czego szukasz: ");
					scanf_s("%d", &choice2);
					switch(choice2)
					{
                    default:
                        printf_s("Nie ma takiej opcji");
                        system("timeout 5");
                        system("cls");
                        break;
                    case 0:
                        break;
                    case 1:
                        printf_s("Miecz znajdziesz pod indeksem: \n");
                        do
                        {
                            for (int i = 0; i < eq_size; i++)
                            {
                                for (int j = 0; j < eq_size; j++)
                                {
                                    if (ekwipunek[i][j] == 1)
                                    {
                                        printf_s("[%d][%d]\n", i, j);
                                    }
                                }
                            }
                            getchar();
                        }while (getchar() != '\n');
                        break;
                    case 2:
                        printf_s("Tarcze znajdziesz pod indeksem: \n");
                        do
                        {
                            for (int i = 0; i < eq_size; i++)
                            {
                                for (int j = 0; j < eq_size; j++)
                                {
                                    if (ekwipunek[i][j] == 2)
                                    {
                                        printf_s("[%d][%d]\n", i, j);
                                    }
                                }
                            }
                            getchar();
                        }while (getchar() != '\n');
                        break;
                    case 3:
                        printf_s("Luk znajdziesz pod indeksem: \n");
                        do
                        {
                            for (int i = 0; i < eq_size; i++)
                            {
                                for (int j = 0; j < eq_size; j++)
                                {
                                    if (ekwipunek[i][j] == 3)
                                    {
                                        printf_s("[%d][%d]\n", i, j);
                                    }
                                }
                            }
                            getchar();
                        }while (getchar() != '\n');
                        break;
                    case 4:
                        printf_s("Amulet znajdziesz pod indeksem: \n");
                        do
                        {
                            for (int i = 0; i < eq_size; i++)
                            {
                                for (int j = 0; j < eq_size; j++)
                                {
                                    if (ekwipunek[i][j] == 4)
                                    {
                                        printf_s("[%d][%d]\n", i, j);
                                    }
                                }
                            }
                            getchar();
                        }while (getchar() != '\n');
                        break;
                    case 5:
                        printf_s("Chleb znajdziesz pod indeksem: \n");
                        do
                        {
                            for (int i = 0; i < eq_size; i++)
                            {
                                for (int j = 0; j < eq_size; j++)
                                {
                                    if (ekwipunek[i][j] == 5)
                                    {
                                        printf_s("[%d][%d]\n", i, j);
                                    }
                                }
                            }
                            getchar();
                        }while (getchar() != '\n');
                        break;
					}

                }
			} while (choice2 != 0);
			break;
		case 0:
			break;
		}
	} while (choice != 0);

	printf_s("Dziekuje za skorzystanie z programu");
}
