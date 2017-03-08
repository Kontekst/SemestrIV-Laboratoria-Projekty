
// Tomasz Kontek 160553.cpp : Defines the entry point for the console application.
//

//Lista jednokierunkowa
/*
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>

using namespace std;


struct lista
{
	int	number;
	struct  lista *next;
} *top = NULL;

void insert(struct lista *ptr, int liczba){
	if (ptr == NULL){
		cout << "Dopisanie elementu na poczatku listy" << endl;
		ptr = (struct lista *)malloc(sizeof(struct lista));
		ptr->number = liczba;
		ptr->next = NULL;
	}
	else{
		bool alfa = 1;
		while (alfa){
			if (ptr->next == NULL){
				struct lista* p;
				p = (struct lista *)malloc(sizeof(struct lista));
				ptr->next = p;
				p->number = liczba;
				p->next = NULL;
				alfa = 0;
			}
			else{
				ptr = ptr->next;
			}
		}
	}
}

void wypisz(struct lista *ptr){
	lista * temp;
	temp = ptr;
	while (temp != NULL){
		cout << temp->number << " " << endl;
		temp = temp->next;
	}
}

lista* usun(struct lista *ptr, int liczba){
	struct lista *topp;
	topp = ptr;
	struct lista * temp1;
	struct lista * temp2;
	temp1 = ptr;
	temp2 = ptr;
	while (temp1 != NULL &&  temp1->number == liczba){
		topp = temp1->next;
		temp2 = temp1;//previous;
		temp1 = temp1->next;
	}

	while (temp1 != NULL){
		bool flaga = 1;
		if (temp1->number == liczba){
			temp2->next = temp1->next;
			flaga = 0;
		}
		if (flaga == 1){
			temp2 = temp1;//previous;
		}
		temp1 = temp1->next;
	}

	return topp;
}


int _tmain(int argc, _TCHAR* argv[])
{
	top = (struct lista *)malloc(sizeof(struct lista));
	top->number = 10;
	top->next = NULL;
	wypisz(top);
	cout << "||<<<<>>>>||" << endl;
	insert(top, 1);
	insert(top, 3);
	insert(top, 5);
	insert(top, 5);
	insert(top, 7);
	wypisz(top);
	cout << "||<<<<>>>>||" << endl;
	top = usun(top, 5);
	wypisz(top);
	cout << "||<<<<>>>>||" << endl;
	return 0;
}


*/
//Lista dwukierunkowa
#include "stdafx.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct element
{
	struct element *previous;
	int number;
	struct element *next;
} *beginn;

struct element *insert(int obj, struct element *ptr)
{
	struct element
		*p;
	p = ptr->next; /* weŸ adres analizowanego elementu*/
	if (p != NULL) /* czy koniec listy*/
	{
		if (obj > (p->number)){
			p->next = insert(obj, p);
		}
		else
		{
			/* utwórz nowy element*/
			p->previous = (struct element *)
				malloc(sizeof(struct element));
			/* zapamiêtaj adres nowego elementu*/
			p = p->previous;
			/* zainicjuj sk³adowe nowego elementu*/
			p->number = obj;
			p->next = ptr->next;
			p->previous = ptr;
		}
	}
	else /* koniec listy */
	{
		/* utwórz nowy element*/
		p = (struct element *)malloc(sizeof(struct element));
		/* zainicjuj sk³adowe nowego elementu*/
		p->number = obj;
		p->next = NULL;
		p->previous = ptr;
	}
	return p; /* zwróæ adres nowego elementu*/
}


struct element * deleting(struct element *ptr, int numberArg){ //Usuwanie lementu listy z wartoœci¹ number
	struct element *p = ptr; //beginning
	struct element *top = ptr;

	while (p != NULL &&  p->number == numberArg){
		top = p->next;
		p = p->next;
	}
	
	while (p != NULL){
		if (p->next!=NULL && p-> next->number == numberArg){
			p->next = p->next->next;
			p->next->next->previous = p;
		}
		p = p->next;
	}
	return top;
}

		void wypisz(struct element *ptr){
			while (ptr != NULL){
				cout << ptr->number << " ";
				ptr = ptr->next;
			}
			cout << endl << endl;
		}

		int _tmain(int argc, _TCHAR* argv[])
		{
			beginn = (struct element *) malloc(sizeof(struct element));
			beginn->number = -1;
			beginn->next = NULL;
			beginn->previous = NULL;

			for (int i = 0; i < 10; i++){
				beginn->next = insert(i, beginn);
			}

			wypisz(beginn); //OK

			beginn->next = insert(15, beginn);
			beginn->next = insert(6, beginn);
			beginn->next = insert(20, beginn);

			wypisz(beginn); //OK

			beginn = deleting(beginn, 6);
			wypisz(beginn);

			beginn->next = insert(15, beginn);
			wypisz(beginn);

			return 0;
		}



