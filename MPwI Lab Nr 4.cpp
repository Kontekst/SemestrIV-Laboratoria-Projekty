// |----- 160553 Tomasz Kontek -----|

#include "stdafx.h"
#include <iostream>
#include <time.h>

using namespace std;

double valuesXY[4][4];
double sumy[4];
int tablicaPrzedzialow[4][4];

int main()
{
	srand(time(NULL));
	valuesXY[0][0] = 0.2;
	valuesXY[0][1] = 0.0;
	valuesXY[0][2] = 0.0;
	valuesXY[0][3] = 0.1;

	valuesXY[1][0] = 0.05;
	valuesXY[1][1] = 0.0;
	valuesXY[1][2] = 0.1;
	valuesXY[1][3] = 0.05;

	valuesXY[2][0] = 0.05;
	valuesXY[2][1] = 0.1;
	valuesXY[2][2] = 0.0;
	valuesXY[2][3] = 0.05;

	valuesXY[3][0] = 0.1;
	valuesXY[3][1] = 0.0;
	valuesXY[3][2] = 0.0;
	valuesXY[3][3] = 0.2;

	//zerowaæ sumy????????????
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			sumy[i] += valuesXY[i][j];
		}
	}

	//for (int j = 0; j < 4; ++j) cout << sumy[j]<<endl;


	double result1;
	double result2;
	int xx, yy;
	for (int i = 0; i < 100000; i++) {
		result1 = ((double)rand() / (double)(RAND_MAX));
		result2 = ((double)rand() / (double)(RAND_MAX));


		if (result1 < 0.30) {
			xx = 0;
			if (result2 < 0.2 / sumy[0]) {
				yy = 0;
			}
			else if (result2 < 0.2 / sumy[0])
			{
				yy = 1;
			}
			else if (result2 < 0.2 / sumy[0])
			{
				yy = 2;
			}
			else
			{
				yy = 3;
			}
		}



		else if (result1 < 0.50) {
			xx = 1;
			if (result2 < 0.05 / sumy[1]) {
				yy = 0;
			}
			else if (result2 < 0.05 / sumy[1]) {
				yy = 1;
			}
			else if (result2 < 0.15 / sumy[1])
			{
				yy = 2;
			}
			else
			{
				yy = 3;
			}
		}

		else if (result1 < 0.70) {
			xx = 2;
			if (result2 < 0.05 / sumy[2]) {
				yy = 0;
			}
			else if (result2 < 0.15 / sumy[2]) {
				yy = 1;
			}
			else if (result2 < 0.15 / sumy[2])
			{
				yy = 2;
			}
			else
			{
				yy = 3;
			}
		}



		else  {
			xx = 3;
			if (result2 < 0.1 / sumy[3]) {
				yy = 0;
			}
			else if (result2 < 0.1 / sumy[3]) {
				yy = 1;
			}
			else if (result2 < 0.1 / sumy[3])
			{
				yy = 2;
			}
			else
			{
				yy = 3;
			}
		}



		tablicaPrzedzialow[xx ][yy]++;

	}


	

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << tablicaPrzedzialow[i][j] <<" ";
		}
		cout << endl;
	}

	return 0;
}
