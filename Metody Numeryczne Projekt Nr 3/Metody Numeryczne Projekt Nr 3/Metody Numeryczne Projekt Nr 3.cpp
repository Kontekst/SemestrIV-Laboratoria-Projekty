/*----- Tomasz Kontek 160553 Grupa Numer 4 -----*/
/*----- Metody Numeryczne Projekt Numer 3 -----*/
/*----- Aproksymacja profilu wysokosciowego -----*/

// test1.txt p³aska pustynia solna Salar de Uyuni w Boliwii 100km d³ugoœci minimalne ró¿nice wysokoœci max = 8m
// test2.txt przekroj Himalaji 100 km, ostre wachania wysokoœci do 4 km
// test3.txt wy¿yna Tybetañska 100 km du¿e wachania wysokoœci, ró¿nica do 2,5km
// test4.txt Alpy 100km, wachania do 2,5km

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

double scoreResultWithLagrange(double dystanceX, double *measuresArray[2], int numberOfMeasurements);
void initializeArray(double*** measurements,int* numberOfLines);
void countNumberOfLinesInFile(int ptrCounter[]);
void initializeMeasurementsArray(double*** measurements, int numberOfLines[4]);
void fillMeasurementsArray(double*** measurements, int numberOfLines[4]);
void calculateLagrange(double*** measurements, int numberOfLines[4], int interval);
double calculateSingleLagrange(double ***measurements, int numberOfLines, int interval, int numberOfFile, int xCalculated);

string filesNames[] = { "test1.txt", "test2.txt", "test3.txt","test4.txt" };
string lagrangeNames[] = { "Lag1.txt", "Lag2.txt", "Lag3.txt","Lag4.txt" };
string gluedThirdDegreeNames[] = { "Glue1.txt", "Glue2.txt", "Glue3.txt","Glue4.txt" };

int main()
{

	int numberOfLines[4] = { 0,0,0,0 };
	double ***measurements = new double**[4]; // ||measurements[4][512][2]|| a dok³adniej ||measurements[4][countofLines[i]][2]||  [4 pliki][512 punktów pomiarowych][pary pomierzonych punktów (x,wysokoœæ)]
	countNumberOfLinesInFile(numberOfLines);
	initializeMeasurementsArray(measurements, numberOfLines);
	
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 512; j++)
			measurements[i][j][1] /= 1000.0;
	}
	}*/
	calculateLagrange(measurements,numberOfLines,8); 

	return 0;
}

//-------------------------// Zliczenie pomiarow
void countNumberOfLinesInFile(int *ptrCounter) {
	for (int i = 0; i < 4; i++) {
		std::string line;
		std::ifstream myfile(filesNames[i]);
		while (getline(myfile, line))
			ptrCounter[i]++;
	}
}
//-------------------------// Inicjalizacja tablicy dla pomiarow
void initializeMeasurementsArray(double*** measurements,int numberOfLines[4]) {
	for (int i = 0; i < 4; i++) {
		measurements[i] = new double*[numberOfLines[i]];
	}

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < numberOfLines[i]; k++) {
			measurements[i][k] = new double[2];
		}
	}
	fillMeasurementsArray(measurements, numberOfLines);
}
//-------------------------// Wczytanie pomiarow do tablicy
void fillMeasurementsArray(double*** measurements, int numberOfLines[4]) {
	for (int i = 0; i < 4; i++) {
		std::ifstream myFile(filesNames[i]);
		for (int j = 0; j < numberOfLines[i]; j++) {
			myFile >> measurements[i][j][0];
			myFile >> measurements[i][j][1];
		}
	}
}
//-------------------------// Procedura liczenia z Lagrange z zapisem do pliku
void calculateLagrange(double*** measurements, int numberOfLines[4],int interval) {
	ofstream myFile;
	for (int i = 0; i < 4; i++) {
		myFile.open(lagrangeNames[i]);
		for (int j = 0; j < numberOfLines[i]; j++) {
			myFile << measurements[i][j][0]<<" ";
			if ( ( j % interval != 0 ) && ( j != 0) ) { // Liczenie i zapis wyniku obliczonego z Lagrange
				myFile << calculateSingleLagrange(measurements, numberOfLines[i], interval, i, j) << endl;
			}
			else { // Zapis prawidlowej zmierzonej wartosci 
				myFile << measurements[i][j][1] << endl;
			}
		}
		myFile.close();
	}
}
//-------------------------//
double calculateSingleLagrange(double ***measurements,int numberOfLines, int interval,int numberOfFile, int xCalculated) {
	double result = 0.0;
	for (int e = 0; e < (numberOfLines / interval); e++) {
		double Ln = 1.0;
		for (int f = 0; f < (numberOfLines / interval); f++) { //Gora rownania
			if (f != e)
			Ln *= (measurements[numberOfFile][xCalculated][0] - measurements[numberOfFile][f*interval][0]);
		//	cout << measurements[numberOfFile][xCalculated][0] << " - " << measurements[numberOfFile][f*interval][0] << endl;
		}
		double temp = 1.0;
		for (int f = /*numberOfLines*/ /*e*/0; f < (numberOfLines / interval); f++) { //Gora rownania
			if (f!=e)
			temp *= ( measurements[numberOfFile][/*numberOfLines / (xCalculated + 1 )*/e*interval][0] - measurements[numberOfFile][f*interval][0]);
		//	cout <<f << " || "<<temp << endl;
			//cout <<f<<"||"<< measurements[numberOfFile][e*interval][0] << " - " << measurements[numberOfFile][f*interval][0] << endl;
			
		}
		//cout << Ln << "  |||  " << temp<<endl;
		Ln = Ln / temp; //CHECK skrocic
		result = result + measurements[ numberOfFile ][ e * interval ][ 1 ] * Ln; //CHECK skrocic
	}
	return result;
}