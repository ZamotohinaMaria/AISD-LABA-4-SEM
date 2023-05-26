#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "Graph.h"
#include "exeption.h"

using namespace std;

Graph::~Graph()
{
	delete_graph();
}

void Graph::delete_graph()
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->edges.clear();
	}
	vertexes.clear();
}

void Graph::print()
{
	if (vertexes.size() == 0) cout << "Graph is empty" << endl;
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		auto curr = v->edges.begin();
		auto end = v->edges.end();
		cout << v->id_v << ": ";
		while (curr != end)
		{
			cout << curr->id_to << " -> ";
			curr++;
		}
		cout << "NULL" << endl;
	}
}

//----------------------------
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

vector<Vertex> Graph:: all_vertices() const
{
	vector<Vertex> vert;
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		vert.push_back(vertexes[find_vertex(v->id_v)]);
	}
	return vert;
}

queue<Vertex> Graph::queue_vertices() const
{
	queue<Vertex> vert;
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		vert.push(vertexes[find_vertex(v->id_v)]);
	}
	return vert;
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

	auto current = vertexes[index_v].edges.begin();
	auto end = vertexes[index_v].edges.end();

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

	auto current = vertexes[index_v].edges.begin();
	auto end = vertexes[index_v].edges.end();

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
				current++;
			}
		}
	}

	return count;
}

//---------------------------------
vector<Vertex> Graph::walk(int id_first)
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->color = white;
		v->id_prev = INT_MAX;
	}

	int index_first = find_vertex(id_first);
	return search_in_width(vertexes[index_first]);

	//for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	//{
	//	if (v->color == white) 
	//	{
	//		cout << "Vertexes, that cannot be reached from the vertex" << id_first << endl;
	//		int index = find_vertex(v->id_v);
	//		search_in_width(vertexes[index]);
	//	}
	//}
}

//void print_queue(queue<Vertex> queue)
//{
//	cout << "queue: ";
//	while (!queue.empty())
//	{
//		cout << queue.front().id_v << "\t";
//		queue.pop();
//	}
//	cout << endl;
//}

void insert_into_queue(queue<Vertex>& q, Vertex v)
{
	queue<Vertex> Q = q;
	while (!Q.empty())
	{
		if (Q.front().id_v == v.id_v) return;
		Q.pop();
	}
	q.push(v);
}

vector<Vertex> Graph::search_in_width(Vertex& first_v)
{
	cout << "Walk for vertex " << first_v.id_v << endl;
	vector<Vertex> way;
	queue<Vertex> Q;
	vertexes[find_vertex(first_v.id_v)].color = gray;
	Q.push(vertexes[find_vertex(first_v.id_v)]);
	//print_queue(Q);
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		Q.pop();
		way.push_back(u);
		vector<Vertex> v_neighbour = neighbour_of_vertex(u.id_v);
		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			if (v->color == white)
			{
				vertexes[find_vertex(v->id_v)].color = gray;
				vertexes[find_vertex(v->id_v)].id_prev = u.id_v;
				int i = find_vertex(v->id_v);
				insert_into_queue(Q, vertexes[i]);
			}
		}
		vertexes[find_vertex(u.id_v)].color = black;
		//print_queue(Q);
	}
	return way;
}

int min_index(queue<Vertex>& q, int sortedIndex)
{
	int min_i = -1;
	double min_val = INT_MAX;
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = q.front();
		q.pop();
		if (curr.d <= min_val && i <= sortedIndex)
		{
			min_i = i;
			min_val = curr.d;
		}
		q.push(curr);  
	}
	return min_i;
}

void insert_min_to_rear(queue<Vertex>& q, int min_i)
{
	Vertex min_val(INT_MAX);
	int n = q.size();
	for (int i = 0; i < n; i++)
	{
		Vertex curr = q.front();
		q.pop();
		if (i != min_i)
			q.push(curr);
		else
			min_val = curr;
	}
	q.push(min_val);
}

void sort_queue(queue<Vertex>& q)
{
	for (int i = 1; i <= q.size(); i++)
	{
		int min_i = min_index(q, q.size() - i);
		insert_min_to_rear(q, min_i);
	}
}

queue<Vertex>Graph:: update_queue(queue<Vertex> Q)
{
	queue<Vertex> new_q;
	while (Q.empty() == false)
	{
		Vertex u = Q.front();
		for (auto v = vertexes.begin(); v != vertexes.end(); v++)
		{
			if (u.id_v == v->id_v) new_q.push(vertexes[find_vertex(v->id_v)]);
		}
		Q.pop();
	}
	return new_q;
}

//----------------------------------------
void Graph::relax(Vertex& u, Vertex& v)
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
		vertexes[find_vertex(v.id_v)].d = u.d + w;
		vertexes[find_vertex(v.id_v)].id_prev = u.id_v;
	}
}

void Graph::deicstra(Vertex& first)
{
	for (auto v = vertexes.begin(); v != vertexes.end(); v++)
	{
		v->d = INT_MAX;
		v->id_prev = INT_MAX;
	}
	vertexes[find_vertex(first.id_v)].d = 0;

	vector<Vertex> S;
	queue<Vertex> Q = queue_vertices();

	while (Q.empty() == false)
	{
		sort_queue(Q);
		//print_queue(Q);
		Vertex u = Q.front();
		Q.pop();
		S.push_back(u);
		vector<Vertex> v_neighbour = neighbour_of_vertex(u.id_v);
		for (auto v = v_neighbour.begin(); v != v_neighbour.end(); v++)
		{
			int i = find_vertex(v->id_v);
			relax(u, vertexes[i]);
		}
		Q = update_queue(Q);
	}
}

vector<Vertex> Graph::shortest_path(int id_from, int id_to)
{
	int index_from = find_vertex(id_from);
	deicstra(vertexes[index_from]);
	int cur_index = find_vertex(id_to);

	vector<Vertex> way;

	while (cur_index != index_from)
	{
		if (cur_index != -1)
		{
			way.push_back(vertexes[cur_index]);
			int id_prev = vertexes[cur_index].id_prev;
			cur_index = find_vertex(id_prev);
		}
		else
		{
			way.clear();
			return way;
		}
	}
	way.push_back(vertexes[index_from]);
	return way;
}



