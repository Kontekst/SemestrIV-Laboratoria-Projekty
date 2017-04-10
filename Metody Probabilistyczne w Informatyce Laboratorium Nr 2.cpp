// |----- 160553 Tomasz Kontek -----|
#include "stdafx.h"
#include <iostream>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

using namespace std;

long long int pow(int exponent, int power);

int _tmain(int argc, _TCHAR* argv[])

{
	// |----- Zad 2.2 -----|
	long long int a = 69069;
	long long int c = 1;
	long long int M = pow(2, 32);
	int tablicaPrzedzialow[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	unsigned int result = 15;
	M -= 1;
	long long int przedzial = M / 10;
	int temp;
	for (int i = 0; i < 100000; i++){
		result =( a*result + 1) % M;
		temp = result / przedzial;
		tablicaPrzedzialow[temp]++;
	}

	for (int i = 0; i < 10; i++){
		cout << tablicaPrzedzialow[i] << endl;
	}
	cout << endl << endl;

	// |----- Zad 2.6 -----|

	int tablicaPrzedzialow2[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
	result = 0xD2000000;
	bool t1, t2;
	for (int i = 0; i < 100000; i++){
		for (int i = 24; i >= 0; i--){
			//cout << result<< " ";
			t1 = CHECK_BIT(result, i + 7);
			t2 = CHECK_BIT(result, i + 3);
			if (t1 == t2){
				result &= ~(1 << i);  // CLEAR
			}else{ result |= 1 << i; //SET
			}
		}result = result << 24;
		temp = result / przedzial;
		tablicaPrzedzialow2[temp]++;
	}

	for (int i = 0; i < 10; i++){
		cout << tablicaPrzedzialow2[i] << endl;
	}
	return 0;
}

long long int pow(int exponent, int power) {
	long long int result = 1;
	for (int i = 0; i < power; i++) {
		result *= exponent;
	}
	return result;
}
