#include <iostream>
#include <random>
#include <functional>  
#include <math.h>
#include <ctime>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <fstream>
#include <iomanip>

#include "Node.h"
#include "Path.h"

using namespace std;

#define SIZE_OF_MAP 15
#define NUMBER_OF_NODES ((SIZE_OF_MAP*SIZE_OF_MAP)/3)
#define NUMBER_OF_CONNECTIONS (NUMBER_OF_NODES) // Te¿ by by³o fajnie zwiekszyc ten wspolczynnik bo dla grafow bardzo gestych A* ma jeszcze lepsze wyniki

void prepare_nodes(Node ***map, Node **set_of_nodes, Node** set_of_nodes2);
void make_connections(Node **set_of_nodes, Node** set_of_nodes2);
void display_map(Node ***map);
void display_connections(Node **set_of_nodes);
double dijkstra(Node *first, Node *last);
double fRand(double fMin, double fMax); // Generuje liczbe double z zakresu <fMin,fMax>

double a_star(Node **set_of_nodes_for_A_star); // Algorytm A*

int main()
{
	srand(time(NULL));
	Node ***map;
	Node **set_of_nodes;
	Node **set_of_nodes2;

	clock_t begin_dijkstra, begin_astar, end_dijkstra, end_astar;
	double resule_astar, result_dijkstra;
	cout << "Wyniki dla SIZE_OF_MAP = " << SIZE_OF_MAP << " NUMBER_OF_NODES = " << NUMBER_OF_NODES << " NUMBER_OF_CONNECTIONS = " << NUMBER_OF_CONNECTIONS << endl;
	cout << "Czas dijkstra \t czas A* \t odleglosc dijkstra \t odleglosc A*\n";
	// generowanie mapy		
	map = new Node**[SIZE_OF_MAP];
	set_of_nodes = new Node*[NUMBER_OF_NODES];
	set_of_nodes2 = new Node*[NUMBER_OF_NODES];

	for (int i = 0; i < NUMBER_OF_NODES; i++) {
		set_of_nodes[i] = NULL;
		set_of_nodes2[i] = NULL;
	}

	for (int i = 0; i < SIZE_OF_MAP; i++)
		map[i] = new Node*[SIZE_OF_MAP];
	for (int k = 0; k < 50; k++)
	{
		for (int i = 0; i < SIZE_OF_MAP; i++)
			for (int j = 0; j < SIZE_OF_MAP; j++)
				map[i][j] = NULL;

		prepare_nodes(map, set_of_nodes, set_of_nodes2);
		make_connections(set_of_nodes, set_of_nodes2);

		//----- Algorytm A* -----//
		begin_astar = clock();
		resule_astar = a_star(set_of_nodes2);
		end_astar = clock() - begin_astar;

		begin_dijkstra = clock();
		result_dijkstra = dijkstra(set_of_nodes[0], set_of_nodes[1]);
		end_dijkstra = clock() - begin_dijkstra;

		
		cout << setprecision(20) << ((double)end_dijkstra) / CLOCKS_PER_SEC << "\t" << ((double)end_astar) / CLOCKS_PER_SEC << "\t" << result_dijkstra << "\t" << resule_astar << endl;

		//usuwanie

		for (int i = 0; i < SIZE_OF_MAP; i++)
			for (int j = 0; j < SIZE_OF_MAP; j++)
				delete map[i][j];
	}
	for (int i = 0; i < SIZE_OF_MAP; i++)
		delete[] map[i];

	delete[] set_of_nodes;
	delete[] map;

	return 0;
}
void prepare_nodes(Node ***map, Node **set_of_nodes, Node** set_of_nodes2)
{
	int pos_x, pos_y;

	map[0][0] = new Node(0, 0, 0, NUMBER_OF_NODES);// Zdefiniowanie wêz³a pocz¹tkowego na pozycji (0,0)
	map[SIZE_OF_MAP - 1][SIZE_OF_MAP - 1] = new Node(SIZE_OF_MAP - 1, SIZE_OF_MAP - 1, 1, NUMBER_OF_NODES);// Zdefiniowanie wêz³a koñcowego na pozycji (n-1,n-1) gdzie n to szerokoœæ mapy

	set_of_nodes[0] = map[0][0];
	set_of_nodes[1] = map[SIZE_OF_MAP - 1][SIZE_OF_MAP - 1];

	set_of_nodes2[0] = map[0][0];
	set_of_nodes2[0]->set_length_from_begining(0.0);
	set_of_nodes2[0]->set_length_from_end(sqrt(pow(((double)(SIZE_OF_MAP - 1) - 0), 2) + pow((SIZE_OF_MAP - 1 - 0), 2)));
	set_of_nodes2[1] = map[SIZE_OF_MAP - 1][SIZE_OF_MAP - 1];
	set_of_nodes2[1]->set_length_from_end(sqrt(pow(((double)(SIZE_OF_MAP - 1) - (SIZE_OF_MAP - 1)), 2) + pow((SIZE_OF_MAP - 1 - (SIZE_OF_MAP - 1)), 2)));

	for (int i = 2; i < NUMBER_OF_NODES; i++)
	{
		do
		{
			pos_x = rand() % SIZE_OF_MAP;
			pos_y = rand() % SIZE_OF_MAP;
		} while (map[pos_x][pos_y] != NULL);
		map[pos_x][pos_y] = new Node(pos_x, pos_y, i, NUMBER_OF_NODES);
		set_of_nodes[i] = map[pos_x][pos_y];
		set_of_nodes2[i] = map[pos_x][pos_y];
		set_of_nodes2[i]->set_length_from_end(sqrt(pow(((double)(SIZE_OF_MAP - 1) - pos_x), 2) + pow((SIZE_OF_MAP - 1 - pos_y), 2))); // Ustawienie odlegosci do koncowego punktu w linii prostej
	}
}

void make_connections(Node **set_of_nodes, Node** set_of_nodes2)
{
	double length;
	int node_1;
	int node_2;

	int delta_x, delta_y;
	for (int i = 0; i < NUMBER_OF_CONNECTIONS; i++)
	{
		if (i != 0) {
			do
			{
				node_1 = rand() % NUMBER_OF_NODES;
				node_2 = rand() % NUMBER_OF_NODES;

				//sprawdzenie czy nie generujemy sciezki miedzy tym samym wezlem, oraz czy juz taka sciezka nie istnieje
			} while (node_1 == node_2 ||
				set_of_nodes[node_1]->get_next_path()->
				check_if_already_is_path(set_of_nodes[node_2]) ||

				set_of_nodes[node_2]->get_next_path()->
				check_if_already_is_path(set_of_nodes[node_1]));
		}
		else {
			node_1 = 0;
			node_2 = 1;
		}
		//obliczenie dlugosci z pitagorasa

		delta_x = set_of_nodes[node_1]->get_x() - set_of_nodes[node_2]->get_x();
		delta_y = set_of_nodes[node_1]->get_y() - set_of_nodes[node_2]->get_y();
		length = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
		//length = abs(delta_x) + abs(delta_y);
		//length += fRand(0.0, double(SIZE_OF_MAP)); //Parametr losowy
		if (i == 0)
			length *= 100; // Mamy zapewniona sciezke od poczatku do konca, jest ona bardzo dluga aby w zasadzie byla tylko ostatecznoscia 

		//przypisanie sciezki do obu wierzcholkow 
		//tak na prawde stworzenie nowej dla kazdego, ale przy pracy algorytmow nalezy sprawdzac czy wezel zostal odwiedzony, a nie czy sciezka
		set_of_nodes[node_1]->set_next_path(length, set_of_nodes[node_2]);
		set_of_nodes[node_2]->set_next_path(length, set_of_nodes[node_1]);
		set_of_nodes2[node_1]->set_next_path_Astar(length, set_of_nodes2[node_2]);
		set_of_nodes2[node_2]->set_next_path_Astar(length, set_of_nodes2[node_1]);
	}
}

//funkcja do wyswietlania mapy, niebezpieczna pryz duzej wartosci SIZE_OF_MAP
void display_map(Node ***map)
{
	for (int i = 0; i < SIZE_OF_MAP; i++) {
		for (int j = 0; j < SIZE_OF_MAP; j++)
			if (map[i][j] != NULL)
				cout << "X";
			else
				cout << "_";
		cout << endl;
	}
}
//funkcja do wyswietlania POLACZEN, niebezpieczna przy duzej wartosci SIZE_OF_MAP
void display_connections(Node **set_of_nodes)
{
	Path *p;
	for (int i = 0; i < NUMBER_OF_NODES; i++)
	{
		p = set_of_nodes[i]->get_next_path();
		while (p != NULL)
		{
			cout << set_of_nodes[i]->get_nr() << " " << p->get_length() << " " << p->get_end()->get_nr() << endl;
			p = p->get_next_path();
		}
		cout << endl;
	}
}

//funkcje do dijkstry
double dijkstra(Node *first, Node *last)
{
	if (first->get_next_path() == NULL)
		return 0;
	first->set_length_from_start(0);
	Node* n, *actual = first;
	Path* p;
	do
	{
		p = actual->get_next_path();
		actual->visit();
		while (p != NULL)
		{
			//pobranie wierzcholka polaczonego z aktualnym
			n = p->get_end();
			//tylko jesli jest nieodwiedzony ustwiamy nowa wartosc i miejsce w kolejce
			if (n->is_Visited() == false)
			{
				//jezeli jeszcze nie ustalono wartosci to ustaw i wstaw do kolejki
				if (n->get_length_from_start() == NULL)
				{
					n->set_length_from_start(actual->get_length_from_start() + p->get_length());
					first->set_next_node(n);
				}//jesli juz ustalono wartosc to sprawdz czy nowa wartosc jest lepsza
				else if (n->get_length_from_start() > (actual->get_length_from_start() + p->get_length()))
				{//jesli jest to ja ustal i popraw pozycje w kolejce
					n->set_length_from_start(actual->get_length_from_start() + p->get_length());
					n->go_up();
				}
			}
			p = p->get_next_path();
		}
		//pobierz nastepny wezel
		actual = first->get_next_node();
		first->remove_first_node();
		//wyjdz jesli juz nie ma nieodwiedzonych wezlow lub gdy natrafilismy na koniec
	} while (actual != NULL && actual != last);
	//jak osiagnieto koniec to zwrocona wartosc bedzie > 0, jesli nie ma sciezki do konca to zwrocone zostanie 0
	return last->get_length_from_start();
}




//-------------------------//

double fRand(double fMin, double fMax) // Generuje liczbe double z zakresu <fMin,fMax>
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

//-------------------------//
// Sprawdza czy co njamniej jedna wartosc w tablicy ma wartosc true
bool isNotEmpty(bool array[NUMBER_OF_NODES]) {
	for (int i = 0; i < NUMBER_OF_NODES; i++) {
		if (array[i] == true)
			return true;
	}

	return false;
}

//-------------------------//

double a_star(Node **set_of_nodes) {

	//----- Algorytm A* -----//

	bool nodes_to_visit[NUMBER_OF_NODES]; // Zawiera wezly do rozpatrzenia
	bool nodes_excluded[NUMBER_OF_NODES]; // Zawiera wezly ktorych aktualnie nie rozpatrujemy

	for (int i = 0; i < NUMBER_OF_NODES; i++) {
		nodes_to_visit[i] = false;
		nodes_excluded[i] = false;
	}

	nodes_to_visit[0] = true;

	int actual_node_number = 0;
	int previous_node_number = 0;
	int temp_length_from_beginning = 0;

	do {
		// 1* Wybranie ze zbioru wezlow ktore sa w polaczeniu z wezlem z poszukiwanym numerem
		previous_node_number = actual_node_number; // Przechowanie numeru poprzednio odwiedzonego wezla
		nodes_to_visit[previous_node_number] = false;
		bool first_choice = true;
		double temp_best_heuristic = 0.0;
		for (int i = 0; i < NUMBER_OF_NODES; i++) {
			if (nodes_to_visit[i] == true && first_choice == false && i != previous_node_number) {
				// cout << i <<" h= "<<set_of_nodes[i]->get_heuristic()<< " <<>>"; // For debugging
				if (set_of_nodes[i]->get_heuristic() < temp_best_heuristic) {
					actual_node_number = i;
					temp_best_heuristic = set_of_nodes[i]->get_heuristic();
				}
			}
			if (nodes_to_visit[i] == true && first_choice == true && i != previous_node_number) {
				//cout << i << " h= "<< set_of_nodes[i]->get_heuristic()<<" |<>|"; // For debugging
				temp_best_heuristic = set_of_nodes[i]->get_heuristic();
				actual_node_number = i;
				first_choice = true;
			}
		}
		// cout << "Wybrano nowy wezel nr " << actual_node_number << endl; // For debugging
		// Umieszczenie wybranego wezla w odwiedzonych i usuniecie z niedowiedzonych
		nodes_excluded[actual_node_number] = true;

		// Jesli jest to wezel koncowy to konczymy algorytm
		if (set_of_nodes[actual_node_number]->get_nr() == 1) {
			// Znaleziono najkrotsza sciezke, wyjscie z funkcji
			set_of_nodes[actual_node_number]->set_length_from_begining(
				set_of_nodes[actual_node_number]->parent->get_length_from_begining() + set_of_nodes[actual_node_number]->get_length_of_path_to(set_of_nodes[actual_node_number]->parent->get_nr()/*previous_node_number*/)// Odleglosc od poprzedniego wierzcholka do //
			);
			break;
		}
		// Dla wszystkich sasiadow aktualnego algorytmu wyznaczamy wartosc i rodzica
		for (int i = 0; i < NUMBER_OF_NODES; i++) {
			int nr_of_neighbour;
			// Ta funkcja w rzeczywosti wykona sie tyle razy ile jest polaczen z danego wezla
			if (set_of_nodes[actual_node_number]->paths[i] != NULL) // Sprawdzene czy ten wierzcholek jest do odwiedzenia
				nr_of_neighbour = set_of_nodes[actual_node_number]->paths[i]->get_dest()->get_nr();
			else
				break;

			if (nodes_excluded[nr_of_neighbour] == true) // S¹siad jest na wykluczonej liscie
				continue;
			else if (nodes_to_visit[nr_of_neighbour] == false) { // Jesli nie znajduje sie na liscie do odwiedzenia
				nodes_to_visit[nr_of_neighbour] = true;
				set_of_nodes[nr_of_neighbour]->parent = set_of_nodes[actual_node_number];
				set_of_nodes[nr_of_neighbour]->set_length_from_begining(set_of_nodes[actual_node_number]->get_length_from_begining() + set_of_nodes[actual_node_number]->paths[i]->get_length()); // Aktualizacja g(x)
				set_of_nodes[nr_of_neighbour]->set_heuristic(); // Aktualizacja f(x)
			}
			else {
				double temp_g = set_of_nodes[actual_node_number]->get_length_from_begining() + set_of_nodes[actual_node_number]->paths[i]->get_length();
				if (temp_g < set_of_nodes[nr_of_neighbour]->get_length_from_begining()) { // Jesli nowa wartosc funkcji g(x) jest lepsza 
					set_of_nodes[nr_of_neighbour]->parent = set_of_nodes[actual_node_number]; // Aktualny wezel staje sie rodziecem dla sasiada
					set_of_nodes[nr_of_neighbour]->set_length_from_begining(set_of_nodes[actual_node_number]->get_length_from_begining() + set_of_nodes[actual_node_number]->paths[i]->get_length()); // Aktualizacja g(x)
					set_of_nodes[nr_of_neighbour]->set_heuristic(); // Aktualizacja f(x)
				}
			}

		}
	} while (isNotEmpty(nodes_to_visit));



	Node* temp = set_of_nodes[1];
	//cout << "Dlugosc sciezki  znalezionej przez A* wynosi = " << set_of_nodes[1]->get_length_from_begining() << endl;
//	cout << "Droga powrotna to wezly = ";
/*	while (temp->parent != NULL) {
		cout << temp->get_nr() << "-";
		temp = temp->parent;
	}cout << temp->get_nr() << endl;*/
	return  set_of_nodes[1]->get_length_from_begining();
}