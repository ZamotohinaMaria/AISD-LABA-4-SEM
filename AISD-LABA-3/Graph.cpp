#include <vector>
#include <stdio.h>
#include "Graph.h"
#include "exeption.h"

using namespace std;

Graph::~Graph()
{
	vertexes.clear();
}

//проверка-добавление-удаление вершин
bool Graph::contain_vertex(int id_find_v) const
{
	if (vertexes.size() == 0) throw EZeroVertexesSize();
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_find_v) return true;
	}
	return false;
}

int Graph::find_vertex(int id_find_v) const
{
	if (vertexes.size() == 0) throw EZeroVertexesSize();
	for (auto i = vertexes.begin(); i != vertexes.end(); i++)
	{
		if (i->id_v == id_find_v) return int(i-vertexes.begin());
	}
	return -1;
}

void Graph::add_vertex(int id_v)
{
	Vertex v(id_v);
	vertexes.push_back(v);
}

bool Graph::remove_vertex(int id_remove_v)
{
	if (vertexes.size() == 0) throw EZeroVertexesSize();
	int remove_index = find_vertex(id_remove_v);
	if (remove_index == -1) throw EElementNotExist(id_remove_v);

}