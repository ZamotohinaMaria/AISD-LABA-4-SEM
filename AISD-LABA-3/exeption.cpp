#include <stdio.h>
#include <iostream>
#include "exeption.h"

using namespace std;

void EZeroVertexesSize:: print_exeption() const
{
	cout << "Exeption: Graph is empty" << endl;
}

EElementNotExist::EElementNotExist(int id) : id(id) {};

void EElementNotExist::print_exeption() const
{
	cout << "Exeption: Vertex with id" << id << "not exist" << endl;
}