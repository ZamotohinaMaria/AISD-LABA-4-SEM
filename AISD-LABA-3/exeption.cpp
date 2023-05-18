#include <stdio.h>
#include <iostream>
#include "exeption.h"

using namespace std;

void EZeroVertexesSize:: print_exeption() const
{
	cout << "Graph is empty" << endl;
}

void EElementNotExist::print_exeption() const
{
	cout << "Vertex with id" << id << "not exist" << endl;
}