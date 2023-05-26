#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <queue>
#include <vector>
#include "Graph.h"
#include "exeption.h"

using namespace std;
template <class T>
int InputValue()
{
	T num = 0;
	while (!(cin >> num) || (cin.peek() != '\n'))
	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "\nIncorrect value...\n";
	}

	return num;
}

int getkey()
{
	int key = getch();
	if ((key == 0) || (key == 224)) key = getch();
	return key;
}

int menu1()
{
	cout << endl << "This is main menu" << endl;
	cout << "Press 1 to add vertex" << endl;
	cout << "Press 2 to add edge" << endl;
	cout << "Press 3 to delete vertex" << endl;
	cout << "Press 4 to delete edge" << endl;
	cout << "Press 5 to get degree and all neighbours of vertex" << endl;
	cout << "Press 6 to do walk" << endl;
	cout << "Press 7 to find min way between vertexes with Deicstra " << endl;
	cout << "Press 8 to do the task" << endl;

	cout << "\nPress Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if (((key >= 49) && (key <= 56)) || (key == 27)) return key;
	}
}

int InputNewVertex(const Graph& g)
{
	int id_v = InputValue<int>();
	while (g.contain_vertex(id_v) == true)
	{
		cout << "this vertex already exists, input new id" << endl;
		id_v = InputValue<int>();
	}
	return id_v;
}

int InputExistsVertex(Graph& g)
{
	int id_v = InputValue<int>();
	while (g.contain_vertex(id_v) == false)
	{
		cout << "This vertex doesn't exists, input corrext id" << endl;
		id_v = InputValue<int>();
	}
	return id_v;
}

double InputEdgeWeight()
{
	double weight = InputValue<double>();
	while (weight <= 0)
	{
		cout << "Weight must be > 0" << endl;
		weight = InputValue<double>();
	}
	return weight;
}

void AddVertex(Graph& g)
{
	cout << "input vertex id" << endl;
	int id_v = InputNewVertex(g);
	g.add_vertex(id_v);
}

void AddEdge(Graph& g)
{
	cout << "input id from: ";
	int id_from = InputExistsVertex(g);

	cout << "\ninput id to: ";
	int id_to = InputExistsVertex(g);

	cout << "\ninput edge's weight: ";
	double weight = InputEdgeWeight();
	g.add_edge(id_from, id_to, weight);
}

void DeleteVertex(Graph& g)
{
	cout << "Input vertex id" << endl;
	int id_v = InputExistsVertex(g);
	g.remove_vertex(id_v);
}

void DeleteEdge(Graph& g)
{
	cout << "input id from: ";
	int id_from = InputExistsVertex(g);

	cout << "\ninput id to: ";
	int id_to = InputExistsVertex(g);
	g.remove_edge(id_from, id_to);
}

void DergreeAndNeighbours(Graph& g)
{
	cout << "Input vertex id" << endl;
	int id_v = InputExistsVertex(g);
	cout << "Vertex degree = " << g.degree(id_v) << endl;
	cout << "Vertex neighbours:" << endl;
	vector<Vertex> neighbours = g.neighbour_of_vertex(id_v);
	for (auto i = neighbours.begin(); i != neighbours.end(); i++)
	{
		cout << i->id_v << '\t';
	}
	cout << endl;
}

void Walk(Graph& g)
{
	cout << "Input vertex id" << endl;
	int id_v = InputExistsVertex(g);
	vector<Vertex> way = g.walk(id_v);
	for (auto w = way.begin(); w != way.end(); w++)
		cout << w->id_v << " -> ";
	cout << "NULL" << endl;
}

void Revers_Vector(vector<Vertex>& v)
{
	for (int i = 0; i < v.size() / 2; i++) {
		Vertex tmp = v[i];
		v[i] = v[(v.size() - 1) - i];
		v[(v.size() - 1) - i] = tmp;
	}
}

void Deicstra(Graph& g)
{
	cout << "input id from: ";
	int id_from = InputExistsVertex(g);

	cout << "\ninput id to: ";
	int id_to = InputExistsVertex(g);

	vector<Vertex> way = g.shortest_path(id_from, id_to);
	Revers_Vector(way);
	double len_way = 0;
	cout << "Shortest way" << endl;
	for (auto w = way.begin(); w != way.end(); w++)
	{
		cout << w->id_v << " -> ";
		if (w->id_v == id_to) len_way = w->d;
	}
	cout << "NULL" << endl;
	cout << "Lenght way:" << len_way << endl;

	vector<Vertex> vert = g.all_vertices();
	for (auto w = vert.begin(); w != vert.end(); w++)
		cout << w->id_v << "-" << w->d << endl;
}

void Task(Graph& g)
{
	//буду считать сумму путей от каждой вершины до каждой другой и -> буду выбирать наименьшее
	vector<Vertex> g_vert = g.all_vertices();
	int id_min = -1;
	double min_len = INT_MAX;
	for (int i = 0; i < g_vert.size(); i++)
	{
		g.deicstra(g_vert[i]);
		double v_len = 0;
		vector<Vertex> vert_i = g.all_vertices();
		cout << "---" << g_vert[i].id_v << "---" << endl;
		for (auto v = vert_i.begin(); v != vert_i.end(); v++)
		{
			cout << v->id_v << ": " << v->d << endl;
			if (v->d == INT_MAX)
			{
				v_len = INT_MAX;
				break;
			}
			v_len += v->d;
		}

		if (v_len < min_len)
		{
			min_len = v_len;
			id_min = i;
		}
		vert_i.clear();
	}

	cout << "the vertex that is suitable for the warehouse (the closest one for everyone else)\n" << g_vert[id_min].id_v << endl;
}

Graph CreateGraph()
{
	Graph g;
	cout << "Input number of vertexes in the graph: ";
	int n = InputValue<int>();
	while (n < 1)
	{
		cout << "Input the correct value" << endl;
		n = InputValue<int>();
	}

	cout << "First of all create array of vertexes" << endl;
	int i = 0;
	while (i < n)
	{
		AddVertex(g);
		i += 1;
	}
	cout << endl;

	cout << "Input edges between vertexes" << endl;
	bool flag = true;
	while (flag == true)
	{
		AddEdge(g);
		cout << endl << "if you want to continue, input 1, else input 0 " << endl;
		flag = InputValue<bool>();
		if (flag != true) break;
	}

	return g;
}

int main()
{
	//Graph g = CreateGraph();
	Graph g;
	g.add_vertex(5);
	g.add_vertex(9);
	g.add_vertex(7);
	g.add_vertex(1);
	g.add_vertex(3);

	g.add_edge(1, 9, 9);
	g.add_edge(1, 7, 3);
	g.add_edge(3, 5, 2);
	g.add_edge(5, 1, 8);
	g.add_edge(7, 1, 7);
	g.add_edge(7, 9, 1);
	g.add_edge(7, 3, 4);
	g.add_edge(9, 7, 1);
	
	while (true)
	{
		system("cls");
		cout << "Hello, this is the laba 3 by Zamotohina Maria\n" <<endl;
		cout << "This is your graph:" << endl;
		g.print();

		int m1 = menu1();
		if (m1 == 27) break;
		switch (m1)
		{
		case 49:
			AddVertex(g);
			system("pause");
			break;
		case 50:
			AddEdge(g);
			system("pause");
			break;
		case 51:
			DeleteVertex(g);
			system("pause");
			break;
		case 52:
			DeleteEdge(g);
			break;
		case 53:
			DergreeAndNeighbours(g);
			system("pause");
			break;
		case 54:
			Walk(g);
			system("pause");
			break;
		case 55:
			Deicstra(g);
			system("pause");
			break;
		case 56:
			Task(g);
			system("pause");
			break;
		}
	}

	return 0;
}