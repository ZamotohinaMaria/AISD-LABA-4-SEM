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
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->id_v == id_find_v) return true;
	}
	return false;
}

int Graph::find_vertex(int id_find_v) const
{
	if (vertexes.size() == 0) throw EZeroVertexesSize();
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->id_v == id_find_v) return int(v - vertexes.begin());
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

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->id_v == id_remove_v) remove_edge(v->id_v, id_remove_v);
	}

	vertexes[remove_index].edges.clear();
	vertexes.erase(vertexes.begin() + remove_index);
	return true;
}

//---------------------------
bool Graph::remove_edge(int id_from, int id_to)
{

}