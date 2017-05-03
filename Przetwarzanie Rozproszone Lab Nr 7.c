// Tomasz Kontek 160553 grupa 4
// Przetwarzanie Rozproszone Laboratorium Numer 7 - watki POSIX
// Kompilacja gcc -pthread nazwaPliku.c
// Wywolanie z linii polecen ./a.out
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_PRIME 100
int wyniki[100];
int liczbaLiczbPierwszych;
int tablicaLiczbPierwszych[MAX_PRIME];
pthread_mutex_t m_p;

void zapisDoTablicy(int argLiczba){
	pthread_mutex_lock(&m_p);
	tablicaLiczbPierwszych[liczbaLiczbPierwszych] = argLiczba;
	liczbaLiczbPierwszych++;
	pthread_mutex_unlock(&m_p);
}

void * f(void * i){
	int liczba = *(int *)i;
	if(liczba<2)
		return NULL;
	int j;
	for( j=2 ; j*j<=liczba; j++)
		if( liczba % j == 0)
			return NULL;
	zapisDoTablicy(liczba);
	return NULL;
}

int compare(const void *a,const void *b){
	return (*(int*)a - *(int*)b);
}

int main(){

	int przedzial[2];

	printf("Podaj przedzial dolny\n");
	scanf("%d",&przedzial[0]);
	if(przedzial[0]<=0)
		przedzial[0]=1;

	printf("Podaj przedzial gorny\n");
	scanf("%d",&przedzial[1]);
	if(przedzial[1]<=0)
		przedzial[1]=przedzial[0]+100;
	// Przedzialy sa domkniete czyli np <4,6> = 4,5,6

	void *arg[100];
	pthread_t threadsArray[100];
	int argumenty[100];
	int k;
	int i;
	int iloscPrzeszukiwanychLiczb = przedzial[1] - przedzial[0] + 1;
	int calkowityLicznikPrzeszukiwanychLiczb = 0;
	int czesciowyLicznikPrzeszukiwanychLiczb;
	for( i = przedzial[0]; i <= przedzial[1]; i=i+100){
		czesciowyLicznikPrzeszukiwanychLiczb = 0;
		for( k = 0;k<100; k++){
			if(calkowityLicznikPrzeszukiwanychLiczb== iloscPrzeszukiwanychLiczb)
				break;
			argumenty[k]=i+k;
			arg[k]= &argumenty[k];
			pthread_create(&threadsArray[k],NULL,f,arg[k]);
			czesciowyLicznikPrzeszukiwanychLiczb++;
			calkowityLicznikPrzeszukiwanychLiczb++;
		}

		for( k = 0;k<100;k++){
			if(czesciowyLicznikPrzeszukiwanychLiczb == k)
				break;
			pthread_join(threadsArray[k],NULL);
		}

		if(calkowityLicznikPrzeszukiwanychLiczb==iloscPrzeszukiwanychLiczb)
			break;
	}
	
	qsort(tablicaLiczbPierwszych,liczbaLiczbPierwszych,sizeof(int),compare);
	for( i = 0; i < liczbaLiczbPierwszych; i++)
		printf("Liczba nr %d = %d\n", i, tablicaLiczbPierwszych[i]);

	return 0;
}
