/*----- Tomasz Kontek 160553 Grupa Numer 4 -----*/
/*----- Metody Numeryczne Projekt Numer 2 -----*/

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip> 

using namespace std;

#define PRCH 10

void wypelnijWektorZerami(double wektor[], int rozmiar);
void wypelnijMacierzGlowna(double **macierzGlownaA,int rozmiar, double wartoscNaPrzekatnej);
void wypelnijWektorMacierzyWyrazowWolnych(double wektorWyrazowWolnych[],int rozmiar, int wspolczynnikN);
void wypiszWektor(double wektor[], int rozmiar);
void wypiszMacierz(double *macierz[], int rozmiar);
void obliczSumeMacierzyLOrazU(double *matrxiL_and_matrixU[],double *macierzGlownaA[],int rozmiar);
void obliczOdwroconaMacierzDiagonalna(double *odwroconaMacierzDiagonalna[], double *macierzGlownaA[], int rozmiar);
void pomnozMacierzPrzezWektor(double wektorWynikowy[],double *macierz[], double wektor[], int rozmiar);
void pomnozMacierze(double *macierzWynikowa[], double * pierwszaMacierz[], double *drugaMacierz[], int rozmiar);
void dodajWektory(double wektorWynikowy[], double pierwszyWektor[], double drugiWektor[],int rozmiar);
void odejmijWektory(double wektorWynikowy[], double drugiWektor[],int rozmiar);
double sumaDlaGaussa(double *macierzGlownaA[], double wektor[], int numerI,int ileSumowan,int poczatek);
void klonujMacierz(double *macierSklonowana[], double *macierzklonowana[], int rozmiar);
void etapEliminacjiNiewiadomych(double *macierzGlownaA[], int rozmiar, double wektorWyrazowWolnych[]);
void etapPostepowaniaOdwrotnego(double *macierzGlownaA[], int rozmiar, double wektorWyrazowWolnych[]);


int main()
{

	int indeksStudencki[6] = { 1,6,0,5,5,3 };
	std::clock_t start;
	double duration;
	int wartoscPrzekatnej;
	ofstream myFile;
	myFile.open("wyniki.txt");
	int N;

	for (int i = (-2); i < 22; i++) {
		if (i == (-2)) {
			//----- Punkt A i B -----//
			N = 900 + 10 * indeksStudencki[4] + indeksStudencki[5];
			wartoscPrzekatnej = (5 + indeksStudencki[3]);
		}
		else if (i == (-1)) {
			//----- Punkt C i D -----//
			N = 900 + 10 * indeksStudencki[4] + indeksStudencki[5];
			wartoscPrzekatnej = 3;
		}
		else if (i >= 0 && i < 9) {
			//----- Punkt E (100,200,300 ... ,800,900) -----//
			N = 100 * (i + 1);
			wartoscPrzekatnej = (5 + indeksStudencki[3]);
		}
		else {
			//----- Punkt E (1000,1500,2000 ... ,x,xx) -----//
			N = 500 * (i - 7);
			wartoscPrzekatnej = (5 + indeksStudencki[3]);
		}
		myFile << N << " ";
		double **macierzGlownaA = new double*[N];
		double *wektorWyrazowWolnychB = new double[N];
		double *wektorX_n = new double[N];

		for (int i = 0; i < N; i++) // Alokacja wierszy macierzy glownej
			macierzGlownaA[i] = new double[N];

		wypelnijMacierzGlowna(macierzGlownaA, N, wartoscPrzekatnej);//cout << "Wypisanie wartosci macierzy glownej" << endl;//wypiszMacierz(macierzGlownaA, N);
		wypelnijWektorZerami(wektorX_n, N);//cout << "Wypisanie wektora X_n" << endl;//wypiszWektor(wektorX_n, N);
		wypelnijWektorMacierzyWyrazowWolnych(wektorWyrazowWolnychB, N, indeksStudencki[2]);//cout << "Wypisanie wartosci wektora wyrazow wolnych" << endl; //wypiszWektor(wektorWyrazowWolnychB, N);

		//----- Metoda Jacobiego -----//

		int liczbaIteracji = 0;
		double **odwroconaMacierzDiagonalna = new double*[N];
		double **matrxiL_and_matrixU = new double*[N];
		double **matrixTJ = new double*[N];

		for (int i = 0; i < N; i++) {
			matrxiL_and_matrixU[i] = new double[N];
			matrixTJ[i] = new double[N];
			odwroconaMacierzDiagonalna[i] = new double[N];
		}
		double *matrixFJ = new double[N];

		obliczSumeMacierzyLOrazU(matrxiL_and_matrixU, macierzGlownaA, N);//cout << "Wypisanie sumy macierzy L oraz U" << endl;//wypiszMacierz(matrxiL_and_matrixU, N);
		obliczOdwroconaMacierzDiagonalna(odwroconaMacierzDiagonalna, macierzGlownaA, N);//cout << "Wypisanie wartosci odwroconej macierzy diagonalnej" << endl;//wypiszMacierz(odwroconaMacierzDiagonalna, N);
		pomnozMacierze(matrixTJ, matrxiL_and_matrixU, odwroconaMacierzDiagonalna, N);//cout << "Wypisanie macierzy TJ" << endl;//wypiszMacierz(matrixTJ, N);
		pomnozMacierzPrzezWektor(matrixFJ, odwroconaMacierzDiagonalna, wektorWyrazowWolnychB, N);//cout << "Wypisanie wektora FJ" << endl;//wypiszWektor(matrixFJ, N);

		double *tempXn = new double[N];
		double normaResiduum = 1.0;
		double *wektorResiduum = new double[N];
		start = std::clock();

		while (normaResiduum > 0.000000001) {
			pomnozMacierzPrzezWektor(tempXn, matrixTJ, wektorX_n, N);
			dodajWektory(wektorX_n, tempXn, matrixFJ, N);
			pomnozMacierzPrzezWektor(wektorResiduum, macierzGlownaA, wektorX_n, N);
			odejmijWektory(wektorResiduum, wektorWyrazowWolnychB, N);
			normaResiduum = 0.0;
			for (int i = 0; i < N; i++) {
				normaResiduum += wektorResiduum[i] * wektorResiduum[i];
			}normaResiduum = sqrt(normaResiduum);
			liczbaIteracji++;
			if (liczbaIteracji == 1000) {
				cout << "Wyniki dla metody Gaussa-Seidela sie nie zbiegaja" << endl;
				normaResiduum = -1;
				liczbaIteracji = -1;
			}
		}
		myFile << setprecision(PRCH) << (std::clock() - start) / (double)CLOCKS_PER_SEC << " ";
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		if (i == (-2) || i == (-1)) {
			cout << "Czas trwania metody Jacoba dla N =  " << N << " i przekatnych = " << wartoscPrzekatnej << " wynosi =" << duration << "\n";
			cout << "Liczba iteracji metody Jacoba wynosi = " << liczbaIteracji << endl;
			cout << "Norma residuum po zakonczeniu metody Jacoba wynosi = " << normaResiduum << endl << endl;
		}
		for (int i = 0; i < N; i++) {
			delete[] matrxiL_and_matrixU[i];
			delete[] matrixTJ[i];
			delete[] odwroconaMacierzDiagonalna[i];
		}
		delete[] matrixFJ;
		delete[] matrixTJ;
		delete[] matrxiL_and_matrixU;
		delete[] odwroconaMacierzDiagonalna;

		//----- Metoda Gaussa-Seidela -----//

		wypelnijWektorZerami(wektorX_n, N);//cout << "Wypisanie wektora X_n" << endl;//wypiszWektor(wektorX_n, N);
		normaResiduum = 1.0;
		liczbaIteracji = 0;
		start = std::clock();
		while (normaResiduum > 0.000000001) {

			for (int i = 0; i < N; i++) {
				tempXn[i] = ((-1)*(sumaDlaGaussa(macierzGlownaA, tempXn, i, i/* -1 */, 0) + sumaDlaGaussa(macierzGlownaA, wektorX_n, i, N, (i + 1))) + wektorWyrazowWolnychB[i]) / macierzGlownaA[i][i];
			}

			for (int i = 0; i < N; i++)
				wektorX_n[i] = tempXn[i];

			pomnozMacierzPrzezWektor(wektorResiduum, macierzGlownaA, wektorX_n, N);
			odejmijWektory(wektorResiduum, wektorWyrazowWolnychB, N);

			normaResiduum = 0.0;
			for (int i = 0; i < N; i++) {
				normaResiduum += wektorResiduum[i] * wektorResiduum[i];
			}normaResiduum = sqrt(normaResiduum);
			liczbaIteracji++;
			if (liczbaIteracji == 1000) {
				cout << "Wyniki dla metody Gaussa-Seidela sie nie zbiegaja" << endl;
				normaResiduum = -1;
				liczbaIteracji = -1;
			}
		}
		myFile << setprecision(PRCH) << (std::clock() - start) / (double)CLOCKS_PER_SEC << " ";
		duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		if (i == (-2) || i == (-1)) {
			cout << "Czas trwania metody Jacoba dla N =  " << N << " i przekatnych = " << wartoscPrzekatnej << " wynosi =" << duration << "\n";
			cout << "Liczba iteracji metody Gaussa-Seidela wynosi = " << liczbaIteracji << endl;
			cout << "Norma residuum po zakonczeniu metody Gaussa-Seidela wynosi = " << normaResiduum << endl << endl;
		}
		//----- Bezpoœrednia Metoda Gaussa  -----//

		double **kopiaMacierzyA = new double*[N];
		double *kopiaWyrazowWolnych = new double[N];

		for (int i = 0; i < N; i++) {
			kopiaMacierzyA[i] = new double[N];
			kopiaWyrazowWolnych[i] = wektorWyrazowWolnychB[i];
		}
		wypelnijWektorZerami(wektorX_n, N);

		start = std::clock();
		if (N < 2001) {
			klonujMacierz(kopiaMacierzyA, macierzGlownaA, N);

			etapEliminacjiNiewiadomych(kopiaMacierzyA, N, kopiaWyrazowWolnych);//wypiszMacierz(macierzGlownaA, N);
			etapPostepowaniaOdwrotnego(kopiaMacierzyA, N, kopiaWyrazowWolnych);//wypiszMacierz(kopiaMacierzyA, N);
			for (int i = 0; i < N; i++) {
				wektorX_n[i] = kopiaWyrazowWolnych[i] / kopiaMacierzyA[i][i];
			}
			pomnozMacierzPrzezWektor(wektorResiduum, macierzGlownaA, wektorX_n, N);
			odejmijWektory(wektorResiduum, wektorWyrazowWolnychB, N);

			normaResiduum = 0.0;
			for (int i = 0; i < N; i++) {
				normaResiduum += wektorResiduum[i] * wektorResiduum[i];
			}normaResiduum = sqrt(normaResiduum);
			myFile << setprecision(PRCH) << (std::clock() - start) / (double)CLOCKS_PER_SEC << endl;
			duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
			if (i == (-2) || i == (-1)) {
				cout << "Czas trwania przyblizonej metody Gaussa dla N =  " << N << " i przekatnych = " << wartoscPrzekatnej << " wynosi =" << duration << "\n";
				cout << "Norma residuum dla przyblizonej metody Gaussa wynosi " << normaResiduum << endl << endl;
			}
		}
		else {
			myFile << setprecision(PRCH) << 0.0 << endl;
		}
		for (int i = 0; i < N; i++) {
			delete[] kopiaMacierzyA[i];
			delete[]macierzGlownaA[i];
		}
		delete[] kopiaMacierzyA;
		delete[] macierzGlownaA;
		delete[] wektorWyrazowWolnychB;
		delete[] wektorX_n;


	}
	myFile.close();
	cout << "Koniec pracy programu" << endl;
	getchar();
	getchar();
	return 0;
}

//-------------------------//
void wypelnijWektorZerami(double wektor[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		wektor[i] = 0;
	}
}
//-------------------------//
void wypiszWektor(double wektor[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		cout << wektor[i] << " ";
	}cout << endl << endl;
}
//-------------------------//
void wypelnijMacierzGlowna(double *macierzGlowna[], int rozmiar, double wartoscNaPrzekatnej) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (i == j) 
				macierzGlowna[i][j] = wartoscNaPrzekatnej;
			else if (j == (i + 1) || j == (i + 2) || j == (i - 1) || j == (i - 2)) 
				macierzGlowna[i][j] = (-1);
			else 
				macierzGlowna[i][j] = 0;
		}
	}
}
//-------------------------//
void wypelnijWektorMacierzyWyrazowWolnych(double wektorWyrazowWolnych[], int rozmiar, int wspolczynnikN) {
	for (int n = 0; n < rozmiar; n++) 
		wektorWyrazowWolnych[n] = sin((n*(1 + wspolczynnikN)) / 50.0);
}
//-------------------------//
void wypiszMacierz(double *macierz[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (macierz[i][j] <10 && macierz[i][j]> (-1))
				cout << macierz[i][j] << "  ";
			else
				cout << macierz[i][j] << " ";
		}
		cout << endl;
	}cout << endl;
}
//-------------------------//
void obliczSumeMacierzyLOrazU(double *matrxiL_and_matrixU[], double *macierzGlownaA[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (j == (i + 1) || j == (i + 2) || j == (i - 1) || j == (i - 2))
				matrxiL_and_matrixU[i][j] = (-1)*macierzGlownaA[i][j];
			else
				matrxiL_and_matrixU[i][j] = 0;
		}
	}
}
//-------------------------//
void obliczOdwroconaMacierzDiagonalna(double *odwroconaMacierzDiagonalna[], double *macierzGlowna[], int rozmiar){
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (i == j)
				odwroconaMacierzDiagonalna[i][j] = 1.0 / macierzGlowna[i][j];
			else
				odwroconaMacierzDiagonalna[i][j] = 0;
		}
	}
}
//-------------------------//
void pomnozMacierze(double *macierzWynikowa[], double * pierwszaMacierz[], double *drugaMacierz[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			double suma = 0;
			for (int k = 0; k < rozmiar; k++)
				suma = suma + pierwszaMacierz[i][k] * drugaMacierz[k][j];
			macierzWynikowa[i][j] = suma;
		}
	}
}
//-------------------------//
void pomnozMacierzPrzezWektor(double wektorWynikowy[], double *macierz[], double wektor[], int rozmiar) {
	double suma;
	for (int i = 0; i < rozmiar; i++) {
		suma = 0;
		for (int j = 0; j < rozmiar; j++) {
			suma+= macierz[i][j] * wektor[j];
		}
		wektorWynikowy[i] = suma;
	}
}
//-------------------------//
void dodajWektory(double wektorWynikowy[], double pierwszyWektor[],double drugiWektor[],int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		wektorWynikowy[i] = pierwszyWektor[i] + drugiWektor[i];
	}
}
//-------------------------//
void odejmijWektory(double wektorWynikowy[], double drugiWektor[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		wektorWynikowy[i] -= drugiWektor[i];
	}
}
//-------------------------//
double sumaDlaGaussa(double *macierzGlownaA[], double wektor[], int numerI, int ileSumowan, int poczatek){
	double suma = 0.0;
	for (int j = poczatek; j < ileSumowan; j++) {
		suma += macierzGlownaA[numerI][j] * wektor[j];
	}
	return suma;
}
//-------------------------//
void etapEliminacjiNiewiadomych(double *macierzGlownaA[], int rozmiar, double wektorWyrazowWolnych[]) {
	double wspolczynnik;
	for (int i = 0; i < (rozmiar -1); i++) {
		for (int j = (i + 1); j < rozmiar; j++) {
			wspolczynnik = macierzGlownaA[j][i] / macierzGlownaA[i][i];
			for (int k = 0; k < rozmiar; k++) {
				macierzGlownaA[j][k] -= macierzGlownaA[i][k] * wspolczynnik;
			}
			wektorWyrazowWolnych[j] -= wektorWyrazowWolnych[i] * wspolczynnik;
		}
	}
}
//-------------------------//
void etapPostepowaniaOdwrotnego(double *macierzGlownaA[], int rozmiar, double wektorWyrazowWolnych[]) {
	double wspolczynnik;
	for (int i = (rozmiar - 1); i > (-1); i--) {
		for (int j = (i - 1); j > (-1); j--) {
			wspolczynnik = macierzGlownaA[j][i] / macierzGlownaA[i][i];
			for (int k = 0; k < rozmiar; k++) {
				macierzGlownaA[j][k] -= macierzGlownaA[i][k] * wspolczynnik;
			}
			wektorWyrazowWolnych[j] -= wektorWyrazowWolnych[i] * wspolczynnik;

		}
	}
}
//-------------------------//
void klonujMacierz(double *macierSklonowana[], double *macierzklonowana[], int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			macierSklonowana[i][j] = macierzklonowana[i][j];
		}
	}
}
//-------------------------//