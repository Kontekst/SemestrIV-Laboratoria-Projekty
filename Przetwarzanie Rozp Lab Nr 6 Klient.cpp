/*----- Tomasz Kontek 160553 Grupa Numer 4 -----*/
/*----- Przetwarzanie Rozproszone Laboratorium Numer 6 -----*/

// 85 % powtarza sie w kodzie zrodlowym dla serwera i tam jest caly opis

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define ST_PORT 3015

int main(int argc, char * argv[])
{
	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	WORD wersja = MAKEWORD(2, 0);

	WSAStartup(wersja, &wsas);
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset((void *)(&sa), 0, sizeof(sa));

	sa.sin_family = AF_INET;
	sa.sin_port = htons(ST_PORT);
	sa.sin_addr.s_addr = inet_addr("127.0.0.1"); // Host lokalny

	int result;
	result = connect(s, (struct sockaddr FAR *) &sa, sizeof(sa)); //Proba polaczenia z podanym komputerem
	if (result == SOCKET_ERROR) {
		printf("\nBlad polaczenia!");
		return 0;
	}

	int length;
	char buffer[80];
	FILE * pFile;
	size_t nret;
	size_t nmemb = 256;
	for (;;)
	{
		fopen_s(&pFile, "Dane.txt", "r");
		if (pFile == NULL) {
			fputs("File error", stderr);
			return 0;
		}
		
		while (!feof(pFile))
		{
			if (fgets(buffer, 80, pFile) == NULL) break;
			send(s, buffer, 80, 0);
		}
		fclose(pFile);
		break;
	}
	closesocket(s);
	WSACleanup();
	return 0;
}

