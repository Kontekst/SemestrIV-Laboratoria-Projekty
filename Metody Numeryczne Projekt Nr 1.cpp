// MetodyNumeryczneProjekt160553nr1.cpp : Defines the entry point for the console application.
// Tomasz Kontek 160553 grupa nr 4
// Implementacja i badanie funkcji ln( 1 + x )

#define PRCH 10 //High precision
#define PRCL 2 //Low precision

#include <math.h>
#include <fstream>
#include <iomanip> 
#include <iostream>

using namespace std;

ofstream myFile;
float  absoluteError[5];

/*****************************************************************************/

template<typename number> number potega(number zmienna, int stopien) {
	number wynik = 1;
	for (int i = 0; i < stopien; i++) {
		wynik = wynik*zmienna;
	}
	return wynik;
}

/*****************************************************************************/

template<typename number> void dodawanieSzereguMalejaco(number zmienna, int liczbaIteracji, int errorNumber) {
	// Następny wyraz cišgu obliczam wykorzystujšc poprzedni
	number wynik = 0;
	int minus = 1;
	number powNum=zmienna;
	myFile << "Liczba sumowanych wyrazow = " << liczbaIteracji;
	for (int i = 1; i < liczbaIteracji; i++) {
		wynik = wynik + powNum * minus / i;
		minus *= -1;
		powNum *= zmienna;
	}
	myFile << ", wynik = " << wynik << " Błšd bezwzględny = "<<wynik-absoluteError[errorNumber]<<"\n";
}

template<typename number> void dodawanieSzereguMalejacoZDefinicji(number zmienna, int liczbaIteracji, int errorNumber) {
	// Następny wyraz cišgu obliczam z definicji 
	number wynik = 0;
	int minus;
	
	if (liczbaIteracji % 2 == 0)
		minus = -1;
	else
		minus = 1;

	number powNum = zmienna;
	myFile << "Liczba sumowanych wyrazow = " << liczbaIteracji;
	for (int i = liczbaIteracji; i >0 ; i--) {
		wynik = wynik + potega(zmienna,i) * minus / i; //minus oraz 'i' nie obliczam z definicji poniewaz sa typu int, co nie wplywa na roznice w liczeniu z definicji czy wykorzystujac poprzedni wyraz
		minus *= -1;
	}
	myFile << ", wynik = " << wynik << " Błšd bezwzględny = " << wynik - absoluteError[errorNumber] << "\n";
}

/*****************************************************************************/


template<typename number> void dodawanieSzereguRosnaco(number zmienna, int liczbaIteracji, int errorNumber) {
	// Następny wyraz cišgu obliczam wykorzystujšc poprzedni
	number wynik = 0;
	int minus;
	
	if (liczbaIteracji % 2 == 0)
		minus = -1;
	else
		minus = 1;

	number powNum = potega(zmienna, liczbaIteracji);
	myFile << "Liczba sumowanych wyrazow = " << liczbaIteracji;
	for (int i = liczbaIteracji; i >0; i--) {
		wynik = wynik + powNum * minus / i;
		minus *= -1;
		powNum /= zmienna;
	}
	myFile << ", wynik = " << wynik << " Błšd bezwzględny = " << wynik - absoluteError[errorNumber] << "\n";
}

template<typename number> void dodawanieSzereguRosnacoZDefinicji(number zmienna, int liczbaIteracji, int errorNumber) {
	// Następny wyraz cišgu obliczam z definicji 
	number wynik = 0;
	int minus;

	if (liczbaIteracji % 2 == 0)
		minus = -1;
	else
		minus = 1;

	number powNum = zmienna;
	myFile << "Liczba sumowanych wyrazow = " << liczbaIteracji;
	for (int i = liczbaIteracji; i >0; i--) {
		wynik = wynik + potega(zmienna, i) * minus / i; //minus oraz 'i' nie obliczam z definicji poniewaz sa typu int, co nie wplywa na roznice w liczeniu z definicji czy wykorzystujac poprzedni wyraz
		minus *= -1;
	}
	myFile << ", wynik = " << wynik << " Błšd bezwzględny = " << wynik - absoluteError[errorNumber] << "\n";
}


/*****************************************************************************/

int main()
{
	myFile.open ("wyniki.txt");
	
	if (myFile.is_open()) {
		myFile << "Tomasz Kontek 160553 grupa 4\n";
		myFile << "Przykladowe wyniki dla funkji log() z biblioteki math.h, do argumentu dodaje '1' co daje funkcje ln(1+x)\n";
		myFile << "Argument \tWynik\n";
		
		for (float i = 0.0; i < 1.1; i += 0.1) {
			myFile << setprecision(PRCL) << i<< "\t\t" << setprecision(PRCH) <<log(1.0 + i) << "\n";
		}

		myFile << endl << endl;

		absoluteError[0] = log(1.0 + 0.1);
		absoluteError[1] = log(1.0 + 0.3);
		absoluteError[2] = log(1.0 + 0.5);
		absoluteError[3] = log(1.0 + 0.7);
		absoluteError[4] = log(1.0 + 0.9);

		/*****************************************************************************/
		int errorNumber = 0;
		myFile << "\n\nWyniki w przypadku dodawania wyrazow szeregu malejaco\nprzy obliczaniu kolejnego wyrazu korzystam z poprzedniego wyrazu, w obliczeniach korzystam z formatu float\n\n";
		for (float argument = 0.1; argument < 1.1; argument += 0.2) {
			myFile << "Argument x wynosi " <<setprecision(PRCL)<< argument << setprecision(PRCH)<<endl;
			dodawanieSzereguMalejaco(argument, 10, errorNumber);
			dodawanieSzereguMalejaco(argument, 25, errorNumber);
			dodawanieSzereguMalejaco(argument, 50, errorNumber);
			dodawanieSzereguMalejaco(argument, 100, errorNumber);
			dodawanieSzereguMalejaco(argument, 150, errorNumber);
			errorNumber++;
			myFile << endl;
		}

		errorNumber = 0;
		myFile << "\n\nWyniki w przypadku dodawania wyrazow szeregu malejaco\nprzy obliczaniu kolejnego wyrazu korzystam z wzoru z definicji, w obliczeniach korzystam z formatu float\n\n";
		for (float argument = 0.1; argument < 1.1; argument += 0.2) {
			myFile << "Argument x wynosi " << setprecision(PRCL) << argument << setprecision(PRCH) << endl;
			dodawanieSzereguMalejacoZDefinicji(argument, 10,errorNumber);
			dodawanieSzereguMalejacoZDefinicji(argument, 25, errorNumber);
			dodawanieSzereguMalejacoZDefinicji(argument, 50, errorNumber);
			dodawanieSzereguMalejacoZDefinicji(argument, 100, errorNumber);
			dodawanieSzereguMalejacoZDefinicji(argument, 150, errorNumber);
			errorNumber++;
			myFile << endl;
		}
		/*****************************************************************************/
		errorNumber = 0;
		myFile << "\n\nWyniki w przypadku dodawania wyrazow szeregu rosnšco\nprzy obliczaniu kolejnego wyrazu korzystam z poprzedniego wyrazu, w obliczeniach korzystam z formatu float\n\n";
		for (float argument = 0.1; argument < 1.1; argument += 0.2) {
			myFile << "Argument x wynosi " << setprecision(PRCL) << argument << setprecision(PRCH) << endl;
			dodawanieSzereguRosnaco(argument, 10, errorNumber);
			dodawanieSzereguRosnaco(argument, 25, errorNumber);
			dodawanieSzereguRosnaco(argument, 50, errorNumber);
			dodawanieSzereguRosnaco(argument, 100, errorNumber);
			dodawanieSzereguRosnaco(argument, 150, errorNumber);
			errorNumber++;
			myFile << endl;
		}

		errorNumber = 0;
		myFile << "\n\nWyniki w przypadku dodawania wyrazow szeregu rosnšco\nprzy obliczaniu kolejnego wyrazu korzystam z wzoru z definicji, w obliczeniach korzystam z formatu float\n\n";
		for (float argument = 0.1; argument < 1.1; argument += 0.2) {
			myFile << "Argument x wynosi " << setprecision(PRCL) << argument << setprecision(PRCH) << endl;
			dodawanieSzereguRosnacoZDefinicji(argument, 10, errorNumber);
			dodawanieSzereguRosnacoZDefinicji(argument, 25, errorNumber);
			dodawanieSzereguRosnacoZDefinicji(argument, 50, errorNumber);
			dodawanieSzereguRosnacoZDefinicji(argument, 100, errorNumber);
			dodawanieSzereguRosnacoZDefinicji(argument, 150, errorNumber);
			errorNumber++;
			myFile << endl;
		}

	}
	getchar();
	myFile.close();
    return 0;
}
