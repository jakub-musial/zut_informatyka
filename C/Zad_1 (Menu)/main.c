#include <stdio.h>
#include <stdlib.h>

int choice, choice1, choice2;
char imie[10], rasa[10], plec[10], profesja[15];


int main()
{

	system("cls");
	do
	{
		system("cls");
		printf_s("KREATOR POSTACI\n\n");
		printf_s("1.Nowa Postac\n");
		printf_s("2.Stworzona Postac\n");
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
				printf_s("1.Imie: %s\n",imie);
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
							strcpy(rasa, "Czlowiek");
							break;
						case 2:
							strcpy(rasa, "Elf");
							break;
						case 3:
							strcpy(rasa, "Ork");
							break;
						case 4:
							strcpy(rasa, "Krasnolud");
							break;
						case 5:
							strcpy(rasa, "Niziolek");
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
							strcpy(plec, "Kobieta");
							break;
						case 2:
							strcpy(plec, "Mezczyzna");
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
						case 1:
							strcpy(profesja, "Wojownik");
							break;
						case 2:
							strcpy(profesja, "Lotr");
							break;
						case 3:
							strcpy(profesja, "Lowca");
							break;
						case 4:
							strcpy(profesja, "Skrytobojca");
							break;
						case 5:
							strcpy(profesja, "Mag");
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
		case 0:
			break;
		}
	} while (choice != 0);

	printf_s("Dziekuje za skorzystanie z programu");
}
