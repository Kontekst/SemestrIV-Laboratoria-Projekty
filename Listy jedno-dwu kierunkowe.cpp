
/*----- Tomasz Kontek 160553 Przetwarzanie Rozproszone laboratorium nr 1 -----*/
// Lista jednokierunkowa LIFO
// Lista dwukierunkowa liczb posortowanych rosnaco

#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

/*-------------------------*/
/*----- LIFO -----*/
struct singlyLinkedListElement
{
	int	number;
	struct  singlyLinkedListElement *next;
}* singlyFirstElement = NULL;
/*-------------------------*/

/*-------------------------*/
struct doublyLinkedListElement
{
	int number;
	struct doublyLinkedListElement *previous;
	struct doublyLinkedListElement *next;
} *doublyFirstElement=NULL;
/*-------------------------*/

void pushIntoSinglyLinkedList(int numberArg);
void deleteFromSinglyLinkedList(int numberArg);
void popSinglyLinkedList();
void printSinglyLinked();
struct doublyLinkedListElement* insertIntoDoublyLinked(int numberArg);
struct doublyLinkedListElement* deleteFromDoublyLinkedList(int numberArg);
void printDoublyLinked();

int main()
{
	int mode = 0;
	int numberArg = 0;

	while (true) {
		cout << "|| Wybierz opcje" << endl;
		cout << "|| 1 = Dodanie elementu do listy jednokierunkowej" << endl;
		cout << "|| 2 = Usuniecie elementu z listy jednokierunkowej" << endl;
		cout << "|| 3 = Wypisanie listy jednokierunkowej" << endl;
		cout << "|| 4 = Usun pierwszy element listy jednokierunkowej" << endl;
		cout << "|| 5 = Dodanie elementu do listy dwukierunkowej" << endl;
		cout << "|| 6 = Usuniecie elementu z listy dwukierunkowej" << endl;
		cout << "|| 7 = Wypisanie listy  dwukierunkowej" << endl;
		cout << endl;
		cin >> mode; 
		switch (mode) {
		case 1:
			cout << "Podaj liczbe ktora chcesz dodac do listy jednokierunkowej" << endl;
			cin >> numberArg;
			pushIntoSinglyLinkedList(numberArg);
			system("cls");
			break;
		case 2:
			cout << "Podaj liczbe ktora chcesz usunac z listy jednokierunkowej" << endl;
			cin >> numberArg;
			deleteFromSinglyLinkedList(numberArg);
			system("cls");
			break;
		case 3:
			printSinglyLinked();
			break;
		case 4:
			popSinglyLinkedList();
			system("cls");
			break;
		case 5:
			cout << "Podaj liczbe ktora chcesz wpisac do listy dwukierunkowej" << endl;
			cin >> numberArg;
			doublyFirstElement = insertIntoDoublyLinked(numberArg);
			system("cls");
			break;
		case 6:
			cout << "Podaj liczbe ktora chcesz usunac z listy dwukierunkowej" << endl;
			cin >> numberArg;
			doublyFirstElement = deleteFromDoublyLinkedList(numberArg);
			system("cls");
			break;
		case 7:
			printDoublyLinked();
			break;
		default:
			break;
		}
	}
	
	return 0;
}

/*---- Singly linked list-----*/

/*-------------------------*/
/*----- Dodanie jednego elementu o podanej wartości na koniec listy -----*/
void pushIntoSinglyLinkedList(int numberArg) {
	struct singlyLinkedListElement* newPtr = NULL;
	newPtr = singlyFirstElement;
	singlyFirstElement= (struct singlyLinkedListElement *)malloc(sizeof(struct singlyLinkedListElement));
	singlyFirstElement->number = numberArg;
	singlyFirstElement->next = newPtr;
}
/*-------------------------*/

/*-------------------------*/
/*----- Usunięcie jednego elementu o podanej wartości -----*/
void deleteFromSinglyLinkedList(int numberArg) {
	struct singlyLinkedListElement* newPtr= singlyFirstElement;
	struct singlyLinkedListElement* tempPtr = singlyFirstElement;
	bool continuation = 1;
	if (singlyFirstElement == NULL) {
	}
	else if (singlyFirstElement != NULL && singlyFirstElement->number == numberArg)
	{
		singlyFirstElement = singlyFirstElement->next;
		delete tempPtr;
	}
	else {
		while (newPtr->next != NULL && continuation == 1) {
			if (newPtr->next->number == numberArg) {
				tempPtr = newPtr->next;
				newPtr->next = newPtr->next->next;
				delete tempPtr;
				continuation = 0;
			}if (continuation == 1)
				newPtr = newPtr->next;
		}
	}
}
/*-------------------------*/

/*-------------------------*/
void popSinglyLinkedList() {
	struct singlyLinkedListElement* tempPtr;
	if (singlyFirstElement != NULL) {
		tempPtr = singlyFirstElement;
		singlyFirstElement=singlyFirstElement->next;
		delete tempPtr;
	}
}
/*-------------------------*/

/*-------------------------*/
void printSinglyLinked() {
	cout << "<<<<<>>>>>" << endl;
	singlyLinkedListElement * temp=singlyFirstElement;
	while (temp != NULL) {
		cout << temp->number<< endl;
		temp = temp->next;
	}
	cout << "<<<<<>>>>>" << endl << endl;
}
/*-------------------------*/

/*----- Doubly linked list -----*/

/*-------------------------*/
/*----- Dodanie jednego elementu do listy -----*/
struct doublyLinkedListElement *insertIntoDoublyLinked( int numberArg )
{
	struct doublyLinkedListElement *newPtr;
	struct doublyLinkedListElement *tempPtr;
	
	if (doublyFirstElement == NULL) {
		doublyFirstElement = (struct doublyLinkedListElement *)malloc(sizeof(struct doublyLinkedListElement));
		doublyFirstElement->number = numberArg;
		doublyFirstElement->next = NULL;
		doublyFirstElement->previous = NULL;
		return doublyFirstElement;
	}

	if (doublyFirstElement->number > numberArg) {
		newPtr = (struct doublyLinkedListElement *)malloc(sizeof(struct doublyLinkedListElement));
		doublyFirstElement->previous = NULL;
		newPtr->next = doublyFirstElement;
		newPtr->number = numberArg;
		newPtr->previous = NULL;
		return newPtr;
	}

	tempPtr = doublyFirstElement;
	while (true) {
		if (tempPtr->next != NULL) {
			if (tempPtr->next->number > numberArg) {
				newPtr = (struct doublyLinkedListElement *)malloc(sizeof(struct doublyLinkedListElement));
				newPtr->next = tempPtr->next;
				newPtr->previous = tempPtr;
				newPtr->number = numberArg;
				tempPtr->next->previous = newPtr;
				tempPtr->next = newPtr;
				return doublyFirstElement;
			}
		}
		else {
			newPtr = (struct doublyLinkedListElement *)malloc(sizeof(struct doublyLinkedListElement));
			newPtr->next = NULL;
			newPtr->previous = tempPtr;
			newPtr->number = numberArg;
			tempPtr->next = newPtr;
			return doublyFirstElement;
		}
		tempPtr = tempPtr->next;
	}
}
/*-------------------------*/

/*-------------------------*/
struct doublyLinkedListElement * deleteFromDoublyLinkedList(int numberArg) {
	doublyLinkedListElement *newPtr = doublyFirstElement;
	if (doublyFirstElement->number == numberArg) {
		if (doublyFirstElement->next == NULL) {
			delete doublyFirstElement;
			return NULL;
		}
		else {
			newPtr = doublyFirstElement->next;
			newPtr->previous = NULL;
			delete doublyFirstElement;
			return newPtr;
		}
	}
	while (newPtr != NULL) {
		if (newPtr->number == numberArg) {
			if (newPtr->next != NULL) {
				newPtr->previous->next = newPtr->next;
				newPtr->next->previous = newPtr->previous;
				delete newPtr;
				return doublyFirstElement;
			}
			else {
				newPtr->previous->next = NULL;
				delete newPtr;
				return doublyFirstElement;
			}
		}
		newPtr = newPtr->next;
	}
	return doublyFirstElement;
}

/*-------------------------*/

/*-------------------------*/
void printDoublyLinked() {
	struct doublyLinkedListElement *tempPtr = doublyFirstElement;
	cout << "<<<<<>>>>>" << endl;
	while (tempPtr != NULL) {
		cout << tempPtr->number << " ";
		tempPtr = tempPtr->next;
	}
	cout << endl << "<<<<<>>>>>" << endl << endl;
}
/*-------------------------*/
