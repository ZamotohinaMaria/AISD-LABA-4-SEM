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
	cout << "Press 1 to create new tree" << endl;
	cout << "Press 2 to change tree on the screen" << endl;
	cout << "Press 3 to delete tree on the screen" << endl;
	cout << "Press 4 to do the task" << endl;

	cout << "\nNavigation:" << endl;
	cout << "\tNext tree ->" << endl; //77
	cout << "\tPrev tree <-" << endl; //75
	cout << "\nPress Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 27) || (key == 77) || (key == 75)) return key;
	}
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
		cout << "Input id of " << i + 1 << "vertex: ";
		int id = InputValue<int>();
		g.add_vertex(id);
		i += 1;
	}
	cout << endl;

	cout << "Input edges between vertexes" << endl;
	bool flag = true;
	while (flag == true)
	{
		cout << "id_from ";
		int id_from = InputValue<int>();
		cout << "id_to ";
		int id_to= InputValue<int>();
		cout << "weight ";
		double weight = InputValue<double>();
		g.add_edge(id_from, id_to, weight);
		cout << endl << "if you want to continue, input 1, else input 0 " << endl;
		flag = InputValue<bool>();
		if (flag != true) break;
	}

	cout << "this is your graph" << endl;
	return g;
}

//
////после текущего элемента
//vector<Graph> InsertInArray(vector<Graph>& array, int a_cur)
//{
//	system("cls");
//	vector<Graph> new_array;
//
//	for (int i = 0; i < array.size() + 1; i++)
//	{
//		if (i <= a_cur)
//			new_array.push_back(array[i]);
//		else if (i == a_cur + 1)
//		{
//			Graph new_graph = CreateGraph();
//			new_array.push_back(new_graph);
//		}
//		else if (i > a_cur + 1)
//			new_array.push_back(array[i - 1]);
//	}
//
//	return new_array;
//}
//
//vector<Graph> DeleteFromArray(vector<Graph> array, int a_cur)
//{
//	vector<Graph> new_array;
//
//	for (int i = 0; i < array.size(); i++)
//	{
//		if (i < a_cur)
//			new_array.push_back(array[i]);
//		else if (i == a_cur)
//		{
//			array[i].delete_graph();
//		}
//		else  if (i >= a_cur)
//			new_array.push_back(array[i]);
//	}
//
//	return new_array;
//}

int main()
{
	Graph g = CreateGraph();
	g.add_vertex(5);
	g.add_vertex(9);
	g.add_vertex(7);
	g.add_vertex(1);
	g.add_vertex(3);

	g.add_edge(1, 9, 6);
	g.add_edge(1, 7, 3);
	g.add_edge(3, 2, 2);
	g.add_edge(5, 1, 8);
	g.add_edge(7, 1, 7);
	g.add_edge(7, 9, 1);
	g.add_edge(7, 3, 4);
	g.add_edge(9, 7, 1);

	g.print();
	/*int a_cur = 0;
	vector<Graph> array;

	while (true)
	{
		system("cls");
		cout << "Hello, this is the laba 1 by Zamotohina Maria" << endl;

		if (array.size() > 0)
		{
			array[a_cur].print();
			cout << "\nnumber of this tree = " << a_cur + 1 << endl;
			cout << "number of all trees = " << array.size() << endl;
		}
		else
		{
			system("cls");
			printf("List of trees is empty\n");
			a_cur = -1;
		}

		int m1 = menu1();
		if (m1 == 27) break;
		switch (m1)
		{
		case 75:
			if (a_cur > 0) a_cur--;
			break;
		case 77:
			if (a_cur < array.size() - 1) a_cur++;
			break;
		case 49:
			array = InsertInArray(array, a_cur);
			a_cur += 1;
			system("pause");
			break;
		case 50:
			while (true)
			{
				system("cls");
				if (array.size() == 0)
				{
					cout << "Trees is not exist" << endl;
					break;
				}
				else
				{
					array[a_cur].print();
					int x;
					int m2 = menu2();
					if (m2 == 27) break;
					switch (m2)
					{
					case 49:
						cout << "Input value ";
						x = InputValue();
						array[a_cur].insert(x);
						break;
					case 50:
						cout << "Input value ";
						x = InputValue();
						array[a_cur].erase(x, array[a_cur].GetRoot());
						break;
					}
				}
			}
			system("pause");
			break;
		case 51:
			system("cls");
			if (array.size() == 0) cout << "Trees is not exist" << endl;
			else
			{
				array = DeleteFromArray(array, a_cur);
				if (a_cur == array.size()) a_cur -= 1;
			}
			system("pause");
			break;
		case 52:
			system("cls");
			
			system("pause");
			break;			
		}
	}*/
	return 0;
}