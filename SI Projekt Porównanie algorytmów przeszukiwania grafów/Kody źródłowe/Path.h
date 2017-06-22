#pragma once
#include <iostream>
#include "Node.h"
class Path
{
	//Path to lista jednokierunkowa zawierajaca wszystkie sciezki danego wezla 
	double length;
	Node *end;
	Path *next_path;
	Node *destination;
public:
	Path();
	Path(double length, Node *dest);
	Path(double length, Node *begin, Node *end);
	~Path();
	void set_next_path(double length, Node *begin, Node *end);
	Path* get_next_path();
	Path* get_last_path();
	double get_length();
	bool check_if_already_is_path(Node *end);
	Node* get_end();
	Node* get_dest();
};