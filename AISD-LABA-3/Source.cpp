#include <vector>
#include <stdio.h>
#include <iostream>
#include <queue>
#include "Graph.h"
#include "exeption.h"

using namespace std;

int minIndex(queue<Vertex>& q, int sortedIndex)
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

void insertMinToRear(queue<Vertex>& q, int min_index)
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

void sortQueue(queue<Vertex>& q)
{
	for (int i = 1; i <= q.size(); i++)
	{
		int min_index = minIndex(q, q.size() - i);
		insertMinToRear(q, min_index);
	}
}

void print(queue<Vertex> Q)
{
	while (!Q.empty())  // пока очередь не станет пустой
	{
		cout << Q.front().id_v << "\t";
		Q.pop();    // извлекаем первый элемент
	}
}

int main()
{
	queue<Vertex> Q;
	Q.push(Vertex(30));
	Q.push(Vertex(7));
	Q.push(Vertex(5));
	Q.push(Vertex(6));
	Q.push(Vertex(-1));

	print(Q);

	sortQueue(Q);
	cout << "\n-------------------" << endl;
	print(Q);
}