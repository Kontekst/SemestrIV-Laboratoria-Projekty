/*----- Tomasz Kontek 160553 Grupa 4 -----*/
/*----- Programowanie Rozproszone Laboratorium Numer 4 -----*/
//Argumenty w linii poleceń np 7 ABC
#include <windows.h>
#include <stdio.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#pragma argsused

struct daneDlaWatku
{
	int rozmiarBajty;
	int liczbaWatkowArg;
	int czyOstatniPlik;
	char nazwaPliku[25];
	char szukanyTekst[25];
}*dane;

int priorytety[3] = { THREAD_PRIORITY_BELOW_NORMAL,THREAD_PRIORITY_NORMAL,THREAD_PRIORITY_ABOVE_NORMAL };

DWORD WINAPI funkcja_watku(void *argumenty);

int main(int argc, char **argv)
{
	srand(time(NULL));
	int rozmiar = 1000000;/*00*/ // przy odkomentowaniu jednego zera ~100 M,aktualnie 10 MB, dla 10 wątków i frazy "ABC", czas przy 10 MB to ok.20-30 sekund a dla 100MB około 2 minuty
	int i;
	DWORD id;

	// |----------|

	FILE* plikRoboczyWsk;
	fopen_s(&plikRoboczyWsk, "./text.txt", "w+");

	// |----------|

	int liczbaWatkow = atoi(argv[1]);								    //printf("Liczba procesow potomnych = %d \n", liczbaWatkow);
	// |----------|

	char poszukiwanaFraza[25];
	strcpy_s(poszukiwanaFraza, sizeof poszukiwanaFraza, argv[2]);		//printf("Poszukiwany tekst to = %s \n", poszukiwanaFraza);
	int textLength = strlen(poszukiwanaFraza);							//printf("Dlugosc poszukiwanego tekstu = %d\n", textLength);

	// |----- Utworzenie pliku z losowa trescia -----|
	char losowyZnak[] = "A";
	for (i = 0; i < rozmiar; i++)
	{
		losowyZnak[0] = 'A' + (rand() % 26);
		fputs(losowyZnak, plikRoboczyWsk);
	}
	fclose(plikRoboczyWsk);
	fopen_s(plikRoboczyWsk, "./text.txt", "r");

	// |----- Podzial pliku na pare mniejszych -----|
	FILE* wskMalyPlik;
	char nazwaMalegoPliku[] = "fileA.txt";
	char przenoszonyZnak[]="X";
	for (i = 0; i < liczbaWatkow; i++) {
		nazwaMalegoPliku[4] = i + 'a';
		fopen_s(&wskMalyPlik, nazwaMalegoPliku, "w");
		if (i != liczbaWatkow - 1) {
			// |----- Zapisanie standardowej liczby zanków + reszty z dzielenia rozmiar/liczbaWatkow -----|
			for (int j = 0; j < rozmiar / liczbaWatkow; j++) {
				//fgets(randomChar,1, workFilePtr); //CHECK
				przenoszonyZnak[0] = fgetc(plikRoboczyWsk);
				fputs(przenoszonyZnak, wskMalyPlik);
			}

		}
		else {
			// |----- Zapisanie standardowej liczby znków -----|
			for (int j = 0; j < ((rozmiar / liczbaWatkow) + (rozmiar % liczbaWatkow)); j++) {
				//fgets(randomChar,1, workFilePtr); //CHECK
				przenoszonyZnak[0] = fgetc(plikRoboczyWsk);
				fputs(przenoszonyZnak, wskMalyPlik);
			}
		}
		fclose(wskMalyPlik);
	}
	fclose(plikRoboczyWsk);
	// |----------|

	HANDLE *watki = (HANDLE*)malloc(liczbaWatkow*sizeof(HANDLE));
	dane = (struct daneDlaWatku*)malloc(liczbaWatkow*sizeof(struct daneDlaWatku));

	for (i = 0; i < liczbaWatkow; i++) {
		nazwaMalegoPliku[4] = i + 'a';
		strncpy_s(dane[i].nazwaPliku, 25, nazwaMalegoPliku, 25);
		strncpy_s(dane[i].szukanyTekst, 25, poszukiwanaFraza, 25);
		dane[i].liczbaWatkowArg = liczbaWatkow;
		dane[i].rozmiarBajty = rozmiar;
		if (i == liczbaWatkow - 1) {
			dane[i].czyOstatniPlik = 1;
		}
		else {
			dane[i].czyOstatniPlik = 0;
		}
	}

	for (i = 0; i < liczbaWatkow; i++)
	{
		watki[i] = CreateThread(
			NULL,           // atrybuty bezpieczeństwa
			0,              // inicjalna wielkość stosu
			funkcja_watku,  // funkcja wątku
			(void *)&dane[i],// dane dla funkcji wątku
			0,              // flagi utworzenia
			&id);
		if (watki[i] != INVALID_HANDLE_VALUE)
		{
			//printf("Utworzylem watek %s o identyfikatorze %x\n",dane[i].nazwa, id);
			SetThreadPriority(watki[i], priorytety[i]);
		}
	}
	int czyKonczyc = 0;
	DWORD exitCode = 0;
	while (1) {

		for (int i = 0; i < liczbaWatkow; i++) {
			GetExitCodeProcess(watki[i], &exitCode);
			if (exitCode == STILL_ACTIVE)
				czyKonczyc = 0;
		}
		//if (exitCode != STILL_ACTIVE)
		//	break;
		if (czyKonczyc == 1)
			break;
		Sleep(1000);
	}
	//free(watki);
	//free(dane);
	return 0;
}

// trzy takie funkcje pracują współbieżnie w programie
DWORD WINAPI funkcja_watku(void *argumenty)
{
	struct daneDlaWatku *moje_dane = (struct daneDlaWatku*)argumenty;
	FILE* przeszukiwanyPlikWsk;
	fopen_s(&przeszukiwanyPlikWsk, moje_dane->nazwaPliku, "r"); // printf("%s\n", moje_dane->nazwaPliku); // printf("%s\n", moje_dane->szukanyTekst);
	int liczbaIteracji;
	int liczbaWystapien = 0;
	if (moje_dane->czyOstatniPlik == 0) { // n-1 plikow o tym samym rozmiarze
		liczbaIteracji = moje_dane->rozmiarBajty / moje_dane->liczbaWatkowArg;
	}
	else { // ostatni plik w ktorym moga znalezc sie pozostale pare bajtow, ktorych liczba wynosi = rozmiar % liczbaWatkow
		liczbaIteracji = moje_dane->rozmiarBajty / moje_dane->liczbaWatkowArg + moje_dane->rozmiarBajty % moje_dane->liczbaWatkowArg;
	}
	int rozmiarPoszukiwanejFrazy = strlen(moje_dane->szukanyTekst); //printf("Rozmiar poszukiwanej frazy = %d",rozmiarPoszukiwanejFrazy);
	char * bufor = (char *)calloc(rozmiarPoszukiwanejFrazy, sizeof(char)); //printf("%d", liczbaIteracji);
	for (int i = 0; i < (liczbaIteracji -rozmiarPoszukiwanejFrazy +1 ); i++) {
		fgets(bufor, (rozmiarPoszukiwanejFrazy +1), przeszukiwanyPlikWsk); //printf("%s",bufor);
		long aktualnaPozycja = ftell(przeszukiwanyPlikWsk);
		if (strcmp(bufor, moje_dane->szukanyTekst) == 0) {
			liczbaWystapien++;
		}
		fseek(przeszukiwanyPlikWsk, (aktualnaPozycja - rozmiarPoszukiwanejFrazy +1 ), SEEK_SET); // przsuniecie o 1 w stosunku do poprzedniej pozycji
	}
//	free(bufor);
	printf("Liczba wystapien w pliku %s, wynosi = %d \n", moje_dane->nazwaPliku, liczbaWystapien);

	fclose(przeszukiwanyPlikWsk);

	return 0;
}
