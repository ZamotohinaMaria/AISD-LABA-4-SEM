#include <iostream>
#include <fstream>
#include "ClassTree.h"
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <vector>


#define Treelevel 1

using namespace std;

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

int InputValue()
{
	int num = 0;
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

void PrintTree(const ClassTree& t)
{
	t.print(t.GetRoot(), Treelevel);
}

ClassTree CreateTree()
{
	cout << "Input number of elements in the tree: ";
	int n = InputValue();
	while (n < 1)
	{
		cout << "Input the correct value" << endl;
		n = InputValue();
	}

	cout << "Input root value: ";
	int x = InputValue();
	ClassTree t(x);

	while (n <= 0)
	{
		cout << "Input correct value (n > 0)" << endl;
		n = InputValue();
	}
	for (int i = 0; i < n - 1; i++)
	{
		cout << "Input new value " << i + 1 << ":" << endl;
		x = InputValue();
		while (t.insert(x) == false)
		{
			cout << "This value is exist. Please, input new value" << endl;
			x = InputValue();
		}
	}
	return t;
}

//после текущего элемента
ClassTree* InsertInArray(ClassTree* array, int a_cur, int* a_size)
{
	system("cls");
	ClassTree* new_array = new ClassTree[*a_size + 1];

	for (int i = 0; i < *a_size + 1; i++)
	{
		if (i <= a_cur)
			new_array[i] = array[i];
		else if (i == a_cur + 1)
			new_array[i] = CreateTree();
		else if (i > a_cur + 1)
			new_array[i] = array[i - 1];
	}
	//(array[a_cur + 1]).print((array[a_cur + 1]).GetRoot(), Treelevel);
	*a_size += 1;
	return new_array;
}

ClassTree* DeleteTree(ClassTree* array, int a_cur, int* a_size)
{
	ClassTree* new_array = new ClassTree[*a_size - 1];

	for (int i = 0; i < *a_size; i++)
	{
		if (i < a_cur)
			new_array[i] = array[i];
		else if (i == a_cur)
		{
			array[i].Delete(array[i].GetRoot());
		}
		else  if (i >= a_cur)
			new_array[i - 1] = array[i];
	}
	*a_size -= 1;
	return new_array;
}

int menu1()
{
	cout << endl << "This is main menu" << endl;
	cout << "Press 1 to create new tree" << endl;
	cout << "Press 2 to change tree on the screen" << endl;
	cout << "Press 3 to delete tree on the screen" << endl;
	cout << "Press 4 to find average times" << endl;
	cout << "Press 5 to do the task" << endl;

	cout << "\nNavigation:" << endl;
	cout << "\tNext tree ->" << endl; //77
	cout << "\tPrev tree <-" << endl; //75
	cout << "\nPress Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 27) || (key == 77) || (key == 75)) return key;
	}
}

int menu2()
{
	cout << "Press 1 to insert value in the tree" << endl;
	cout << "Press 2 to delete value in the tree" << endl;
	cout << "Press Esc to return to the main menu" << endl;

	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 27) || (key == 77) || (key == 75)) return key;
	}
}

void Research()
{
	ClassTree* tree, t;
	vector<int> v;

	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	size_t x;
	long double av_t, av_d;

	ofstream out;   // поток для записи
	string name;
	out.open("research.txt");      // открываем файл для записи
	
	for (int k = 1000; k <= 100000; k*=10)
	{
		tree = new ClassTree(int(lcg()));
		t = *tree;

		for (int j = 0; j < k; j++)
		{
			x = lcg();
			while (t.contains(x) == true) x = lcg();
			t.insert(x);
		}

		if (out.is_open())
		{
			out << k << '\t';
		}

		av_t = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while (t.contains(x) == false) x = lcg();
			start = chrono::steady_clock::now();
			t.Poisk(x, t.GetRoot());
			end = chrono::steady_clock::now();
			av_t += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		}
		av_t /= 1000;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << "Time of find random number in the tree of " << k << " elements = " << av_t << endl;


		av_t = av_d = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while (t.contains(x) == true) x = lcg();
			start = chrono::steady_clock::now();
			t.insert(x);
			end = chrono::steady_clock::now();
			av_t += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());

			start = chrono::steady_clock::now();
			t.erase(x, t.GetRoot());
			end = chrono::steady_clock::now();
			av_d += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		}
		av_t /= 1000;
		av_d /= 1000;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << "Time of insert random number in the tree of " << k << " elements = " << av_t << endl;
		if (out.is_open())
		{
			out << av_d << endl;
		}
		cout << endl << "Time of delete random number in the tree of " << k << " elements = " << av_t << endl;
		cout << "-----------------------------------------------------" << endl;
		
		t.Delete(tree->GetRoot());
	}
	//------------------------------------------------------------------------------------------------
	if (out.is_open())
	{
		out << "------------------------------------------------------------------------------" << endl;
	}
	for (int k = 1000; k <= 100000; k *= 10)
	{
		for (int j = 0; j < k; j++)
		{
			x = lcg();
			while ((find(v.begin(), v.end(), x) != v.end()) == true) x = lcg();
			v.push_back(x);
		}

		if (out.is_open())
		{
			out << k << '\t';
		}

		av_t = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while ((find(v.begin(), v.end(), x) != v.end()) == false) x = lcg();
			start = chrono::steady_clock::now();
			find(v.begin(), v.end(), x) != v.end();
			end = chrono::steady_clock::now();
			av_t += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		}
		av_t /= 1000;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << " -- Time of find random number in the vector of " << k << " elements = " << av_t << endl;


		av_t = av_d = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while ((find(v.begin(), v.end(), x) != v.end()) == true) x = lcg();
			start = chrono::steady_clock::now();
			v.push_back(x);
			end = chrono::steady_clock::now();
			av_t += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());

			start = chrono::steady_clock::now();
			v.erase(v.end() - 1);
			end = chrono::steady_clock::now();
			av_d += long double(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
		}
		av_t /= 1000;
		av_d /= 1000;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << " -- Time of insert random number in the vector of " << k << " elements = " << av_t << endl;
		if (out.is_open())
		{
			out << av_d << endl;
		}
		cout << endl << " -- Time of delete random number in the vector of " << k << " elements = " << av_t << endl;
		cout << "-----------------------------------------------------" << endl;
		v.clear();
	}
	out.close();
}

void RoundTRee(Tree* root, ClassTree* t, int** arr, int* i, bool flag)
{
	if (root)
	{
		if (root)
		{
			RoundTRee(root->left, t,  arr, i, flag);
			if (flag == true)
			{
				if (t->contains(root->data) == true)
				{
					(*arr)[*i] = root->data;
					(*i) += 1;
				}
			}
			else
			{
				if (t->contains(root->data) == false)
				{
					(*arr)[*i] = root->data;
					(*i) += 1;
				}
			}
			RoundTRee(root->right, t, arr, i, flag);
		}
	}
}

int Choise(int a, int b)
{
	int x = InputValue();
	while (x < a || x > b)
	{
		cout << "Input the correct number" << endl;
		x = InputValue();
	}
	return x;
}

int* Zadanie(ClassTree* a, ClassTree* b, int* n_answ)
{
	cout << "Press 1, to find summ and 2 to find difference of two trees" << endl;
	int x = Choise(1, 2);
	bool flag;
	if (x == 1) flag = true;
	else flag = false;

	int* answ = new int[100];
	*n_answ = 0;
	RoundTRee(a->GetRoot(), b, &answ, n_answ, flag);
	return answ;
}

int main()
{
	int a_size = 0; //размер динамического массива
	int a_cur = 0; //текущий элемент
	ClassTree* array = new ClassTree[a_size];


	while (true)
	{
		system("cls");
		cout << "Hello, this is the laba 1 by Zamotohina Maria" << endl;

		if (a_size > 0)
		{
			PrintTree(array[a_cur]);
			cout << "\nnumber of this tree = " << a_cur + 1 << endl;
			cout << "number of all trees = " << a_size << endl;
		}
		else
		{
			system("cls");
			printf("List of trees is empty\n");
			a_size = 0;
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
			if (a_cur < a_size - 1) a_cur++;
			break;
		case 49:
			array = InsertInArray(array, a_cur, &a_size);
			a_cur += 1;
			system("pause");
			break;
		case 50:
			while (true)
			{
				system("cls");
				if (a_size == 0)
				{
					cout << "Trees is not exist" << endl;
					break;
				}
				else
				{
					PrintTree(array[a_cur]);
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
			if (a_size == 0) cout << "Trees is not exist" << endl;
			else 
			{
				array = DeleteTree(array, a_cur, &a_size);
				if (a_cur == a_size) a_cur -= 1;
			}
			system("pause");
			break;
		case 52:
			system("cls");
			Research();
			system("pause");
			break;
		case 53:
			system("cls");
			if (a_size == 0)
			{
				cout << "Trees is not exist" << endl;
				system("pause");
				break;
			}
			int n1, n2, n;
			cout << "Input number of two trees to to the task (number of all trees = " << a_size <<  "):" << endl;
			cout << "1 tree: ";
			n1 = Choise(0, a_size - 1);
			cout << "2 tree: ";
			n2 = Choise(0, a_size - 1);

			n = 0;
			int* arr = Zadanie(&array[n1], &array[n2], &n);
			cout << "\nAnswer:" << endl;
			for (int i = 0; i < n; i++) cout << arr[i] << endl;
			system("pause");
		}
	}
	return 0;
}