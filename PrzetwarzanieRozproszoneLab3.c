/*----- Przetwarzanie Rozproszone Laboratorium Nr 3 -----*/
/*----- Tomasz Kontek 160553 grupa 4 -----*/
/*----- Rename file to lab.c -----*/
/*----- gcc -c lab.c -o lab.o -----*/
/*----- gcc lab.o -0 lab.out -----*/
/*----- Przykladowe wywolanie ./lab.out 3 AB -----*/
/*----- Liczba procesow musi byc mniejsza od 23 -----*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main(int argc,char** argv){

	srand(time(NULL));
	FILE* workFilePtr;
	workFilePtr = fopen("./text.txt","w");
	int size = 100000000; // ~100 Mb
	int i = 0;
	int liczbaProcesowPotomnych = atoi(argv[1]); // printf("Liczba procesow potomnych = %d \n",liczbaProcesowPotomnych);


	char textSearched[20];
	strcpy(textSearched,argv[2]);//printf("Poszukiwany tekst to = %s \n",textSearched);
	int textLength=strlen(textSearched); printf("Dlugosc poszukiwanego tekstu = %d\n",textLength);

	/*----- Utworzenie pliku z losowa trescia -----*/
	char randomChar[] = "A";
	for( i = 0; i < size; i++)
	{
		randomChar[0]= 'A' + (random()%26);
		fputs(randomChar,workFilePtr);
	}
	fclose(workFilePtr);


	/*----- Podzial pliku na pare mniejszych -----*/
	char option []="split -n   text.txt T --additional-suffix=.txt"; 
	option[9]=liczbaProcesowPotomnych + '0'; printf("Opcja = %s \n",option);
	system(option); // Nowe pliki to Taa.txt Tab.txt Tac.txt itd...


	/*---- Tworzenie procesow potomnych -----*/
	int pid;
	char prefix;
	for( i = 0; i < liczbaProcesowPotomnych; i++)
	{
		pid = fork();
		if(pid!=0)
		{
			printf("Dziala proces potomny nr = | %d |, przeszukujacy plik Ta%d.txt",pid,i+'a');
			prefix = i +'a';
			char grepOption[100]="grep -o '";
			char grepOptionEnd[]="' Taa.txt |wc -l";
			grepOptionEnd[4]=prefix;
			strncat(grepOption,textSearched,textLength);
			strncat(grepOption,grepOptionEnd,16);//printf("Grep opcja = %s \n",grepOption);
			printf("%d",system(grepOption));
			printf("\n");
			break;
		}else {/*printf("Dziala proces glowny\n");*/}
	}

	return 0;
}