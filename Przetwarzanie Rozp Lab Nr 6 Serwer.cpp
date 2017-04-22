/*----- Tomasz Kontek 160553 Grupa Numer 4 -----*/
/*----- Przetwarzanie Rozproszone Laboratorium Numer 6 -----*/

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define ST_PORT 3015
// Jesli nie nadam konkretnego portu tylko wpisze w strukture port nr 0, to  WinSock wyznaczy numer portu <1024,5000> ktory mozna odczytac getsockname()

int main()
{
	// |----- Ladowanie wersji 2.0 biblioteki Winsock (#include <winsock.h> dla wersji 1.1) -----|
	WSADATA wsas;
	int result;
	WORD wersja;
	wersja = MAKEWORD(2, 0); // Wersja 2.0, dla wersji 1.1 mamy MAKEWORD(1,1); 
	result = WSAStartup(wersja, &wsas);
	if (result)
		printf("Nie udalo sie zaladowac biblioteki winsock");

	// |----- Utworzenie gniazda -----|
	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = gniazdko internetowe SOCK_STREAM = strumieniowe (czyli protokol TCP, UDP jest z kolei datagramowy(i nie poprawia przeklaman bitow w transmisji)) 

	// |----- Utworzenie struktury adresowej -----|
	struct sockaddr_in sa; // struct mozna pominac
	memset((void*)(&sa), 0, sizeof(sa)); // Wypelnienie obszaru struktury zerami
	sa.sin_family = AF_INET; // Rodzina protokol internetowych
	sa.sin_port = htons(ST_PORT); // Nr portu na ktorym serwer nasluchuje
	sa.sin_addr.s_addr = htonl(INADDR_ANY); // Okreslenie dla jakich adresow beda akceptowane polaczenia, tutaj nasluchuje na wszystkich interfejsach sieciowych

	// |----- Dowiazanie struktury sieciowej do gniazdka -----|
	result = bind(s, (struct sockaddr FAR*)&sa, sizeof(sa));
	if (result)
		printf("Nie udalo sie dowiazac gniazdka do struktury sieciowej");
	// |----------|

	result = listen(s, 5); // serwer nasluchuje z kolejka max 5 klientow, szosty zostanie odrzucony
	if (result)
		printf("Nie udalo sie dowiazac gniazdka do struktury sieciowej");
	else
		printf("Rozpoczynam nasluchiwanie portu nr %d\n", ntohs(sa.sin_port));
	// |----------|

	SOCKET si;
	struct sockaddr_in sc;
	int lenc;
	char buf[80];
	int endServerWork = 0;
	FILE* newFilePtr;
	char newFileName[] = "fileA.txt";
	// |----- Petla obslugi kolejnych polaczen -----|

	for (;;) {
		lenc = sizeof(sc);
		// |----- Accept przenosi pierwsze zadania z kolejki w gnaizdku 's' do tymaczasowego gniazdka si ktore sluzy do obslugi klienta -----|

		si = accept(s, (struct sockaddr FAR*)&sc, &lenc);
		// Recv odbiera dane z gniazdka i przesyla do bufora, Arg3 = rozmiar bufora Arg4 = specjalne znaczniki
		while (recv(si, buf, 80, 0) > 0) {
			fopen_s(&newFilePtr, newFileName, "w");
			newFileName[4] = newFileName[4] + 1;
			endServerWork++;
			fputs(buf, newFilePtr);
			printf("\n%s", buf);
			fclose(newFilePtr);
		}

		if (endServerWork == 10) {
			closesocket(si);
			closesocket(s);
			WSACleanup();
			return 0;
		}

	}
	return 0;
}

