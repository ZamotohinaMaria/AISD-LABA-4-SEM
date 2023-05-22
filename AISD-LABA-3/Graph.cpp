#include <vector>
#include <stdio.h>
#include <queue>
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
	if (vertexes.size() == 0) throw "EZeroVertexesSize()";
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->id_v == id_find_v) return true;
	}
	return false;
}

int Graph::find_vertex(int id_find_v) const
{
	if (vertexes.size() == 0) throw "EZeroVertexesSize()";
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
	if (vertexes.size() == 0) throw "EZeroVertexesSize()";
	int remove_index = find_vertex(id_remove_v);
	if (remove_index == -1) throw "EElementNotExist(id_remove_v)";

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		//if (v->id_v == id_remove_v) remove_edge(v->id_v, id_remove_v);
		remove_edge(v->id_v, id_remove_v);
	}

	vertexes[remove_index].edges.clear();
	vertexes.erase(vertexes.begin() + remove_index);
	return true;
}

//---------------------------
void Graph::add_edge(int id_from, int id_to, double w)
{
	if (vertexes.size() == 0) "throw EZeroVertexesSize()";
	int index_from = find_vertex(id_from);
	if (index_from == -1) "throw EElementNotExist(index_from)";

	Edge e = Edge(id_to, w);
	vertexes[index_from].edges.push_front(e);
}

bool Graph::remove_edge(int id_from, int id_to)
{
	if (vertexes.size() == 0) "throw EZeroVertexesSize()";
	int index_from = find_vertex(id_from);
	if (index_from == -1) "throw EElementNotExist(index_from)";

	auto prev = vertexes[index_from].edges.before_begin();
	auto current = vertexes[index_from].edges.begin();
	auto end = vertexes[index_from].edges.end();

	while (current != end)
	{
		if (current->id_to == id_to)
		{
			vertexes[index_from].edges.erase_after(prev);
			return true;
		}
		prev++;
		current++;
	}

	return false;
}

bool Graph::has_edge(int id_from, int id_to) const
{
	if (vertexes.size() == 0) "throw EZeroVertexesSize()";
	int index_from = find_vertex(id_from);
	if (index_from == -1) throw "EElementNotExist(index_from)";

	auto current = vertexes[index_from].edges.begin();
	auto end = vertexes[index_from].edges.end();

	while (current != end)
	{
		if (current->id_to == id_to) return true;
		current++;
	}

	return false;
}
//-----------------------------------

vector<Vertex> Graph::neighbour_of_vertex(int id_v)
{
	if (vertexes.size() == 0) "throw EZeroVertexesSize()";
	int index_v = find_vertex(id_v);
	if (index_v == -1) "throw EElementNotExist(index_v)";

	vector<Vertex> v_neighbour;

	auto current = vertexes[id_v].edges.begin();
	auto end = vertexes[id_v].edges.end();

	while (current != end)
	{
		int i = find_vertex(current->id_to);
		v_neighbour.push_back(vertexes[i]);
		current++;
	}

	return v_neighbour;
}

int Graph::degree(int id_v) const
{
	if (vertexes.size() == 0) "throw EZeroVertexesSize()";
	int index_v = find_vertex(id_v);
	if (index_v == -1) "throw EElementNotExist(index_v)";

	int count = 0;

	auto current = vertexes[id_v].edges.begin();
	auto end = vertexes[id_v].edges.end();

	while (current != end)
	{
		count += 1;
		current++;
	}

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->id_v != id_v)
		{
			auto current = v->edges.begin();
			auto end = v->edges.end();

			while (current != end)
			{
				if (current->id_to == id_v) count += 1;
			}
		}
	}

	return count;
}

void Graph::walk()
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->color = white;
	}

	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		if (v->color == white) 
		{
			int index = find_vertex(v->id_v);
			search_in_width(vertexes[index]);
		}
	}
}

void Graph::search_in_width(Vertex& first_v)
{
	queue<Vertex> Q;
	Q.push(first_v);
	first_v.color = gray;
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		Q.pop();
		vector<Vertex> v_neighbour = neighbour_of_vertex(u.id_v);
		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			if (v->color == white)
			{
				v->color = gray;
				int i = find_vertex(v->id_v);
				Q.push(vertexes[i]);
			}
		}
		u.color = black;
	}
}

void Graph::Relax(Vertex u, Vertex v)
{
	double w = 0;
	auto current = u.edges.begin();
	auto end = u.edges.end();

	while (current != end)
	{
		if (current->id_to == v.id_v)
			w = current->weight;
		current++;
	}
	if (v.d > u.d + w)
	{
		v.d = u.d + w;
		v.id_prev = u.id_v;
	}
}

void Graph::Deicstra(Vertex first)
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->d = INT_MAX;
		v->id_prev = INT_MAX;
	}
	first.d = 0;
	vector<Vertex> S;
	queue<Vertex> Q;
	sortQueue(Q);
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		S.push_back(u);
		vector<Vertex> v_neighbour = neighbour_of_vertex(u.id_v);
		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			int i = find_vertex(v->id_v);
			Relax(u, vertexes[i]);
		}
	}
}

void Graph::shortest_path(int id_from, int id_to)
{
	int index_from = find_vertex(id_from);
	int cur_index = find_vertex(id_to);

	vector<int> way;

	while (cur_index != index_from)
	{
		way.push_back(vertexes[cur_index].id_v);
		int id_prev = vertexes[cur_index].id_prev;
		cur_index = find_vertex(id_prev);
	}
	way.push_back(id_from);
}

int Graph:: minIndex(queue<Vertex>& q, int sortedIndex)
{
	int min_index = -1;
	int min_val = INT_MAX;
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = q.front();
		q.pop(); 
		if (curr.id_v <= min_val && i <= sortedIndex)
		{
			min_index = i;
			min_val = curr.id_v;
		}
		q.push(curr);  // This is enqueue() in 
		// C++ STL
	}
	return min_index;
}

void Graph::insertMinToRear(queue<Vertex>& q, int min_index)
{
	Vertex min_val(INT_MAX);
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = q.front();
		q.pop();
		if (i != min_index)
			q.push(curr);
		else
			min_val = curr;
	}
	q.push(min_val);
}

void Graph:: sortQueue(queue<Vertex>& q)
{
	for (int i = 1; i <= q.size(); i++)
	{
		int min_index = minIndex(q, q.size() - i);
		insertMinToRear(q, min_index);
	}
}

