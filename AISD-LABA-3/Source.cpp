//#include <stdio.h>
//#include <conio.h>
//#include <iostream>
//#include <queue>
//#include <vector>
//#include "Graph.h"
//#include "exeption.h"
//
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
//
//int min_index(queue<Vertex>& q, int sortedIndex)
//{
//	int min_index = -1;
//	double min_val = INT_MAX;
//	int n = q.size();
//	for (int i = 0; i < n; i++)
//	{
//		Vertex curr = q.front();
//		q.pop();
//		if (curr.d<= min_val && i <= sortedIndex)
//		{
//			min_index = i;
//			min_val = curr.id_v;
//		}
//		q.push(curr);  // This is enqueue() in 
//		// C++ STL
//	}
//	return min_index;
//}
//
//void insert_min_to_rear(queue<Vertex>& q, int min_index)
//{
//	Vertex min_val(INT_MAX);
//	int n = q.size();
//	for (int i = 0; i < n; i++)
//	{
//		Vertex curr = q.front();
//		q.pop();
//		if (i != min_index)
//			q.push(curr);
//		else
//			min_val = curr;
//	}
//	q.push(min_val);
//}
//
//void sort_queue(queue<Vertex>& q)
//{
//	for (int i = 1; i <= q.size(); i++)
//	{
//		int min_i = min_index(q, q.size() - i);
//		insert_min_to_rear(q, min_i);
//	}
//}
//
//int main()
//{
//	Graph g;
//	g.add_vertex(5);
//	g.add_vertex(9);
//	g.add_vertex(7);
//	g.add_vertex(1);
//	g.add_vertex(3);
//	
//	g.add_edge(1, 9, 9);
//	g.add_edge(1, 7, 3);
//	g.add_edge(3, 5, 2);
//	g.add_edge(5, 1, 8);
//	g.add_edge(7, 1, 7);
//	g.add_edge(7, 9, 1);
//	g.add_edge(7, 3, 4);
//	g.add_edge(9, 7, 1);
//
//	queue<Vertex> q = g.queue_vertices();
//	print_queue(q);
//	sort_queue(q);
//	print_queue(q);
//	return 0;
//}