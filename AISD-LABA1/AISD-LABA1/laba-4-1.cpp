#include <iostream>
#include <fstream>
#include "ClassTree.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <vector>


#define Treelevel 3

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

//����� �������� ��������
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
	cout << "Press 2 to delete tree on the screen" << endl;
	cout << "Press 3 to find average times" << endl;
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

int menu2()
{
	cout << "Press 1 to find average time for 1000 elements" << endl;
	cout << "Press 2 to find average time for 10000 elements" << endl;
	cout << "Press 3 to find average time for 100000 elements" << endl;
	cout << "Press Esc to return to the main menu" << endl;

	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 27) || (key == 77) || (key == 75)) return key;
	}
}

void Research(int k)
{
	ClassTree* tree, t;
	//vector<int> v;

	clock_t start, end;
	long double* insert_time = new long double[100];
	long double* delete_time = new long double[100];
	long double* poisk_time = new long double[100];
	size_t x;
	long double av_t, av_d;

	ofstream out;   // ����� ��� ������
	string name;
	if (k == 1000) name = "insert1000-10000.txt";
	if (k == 10000) name = "insert10000-100000.txt";
	if (k == 100000) name = "insert100000-1000000.txt";
	out.open(name);      // ��������� ���� ��� ������
	
	for (int q = 0; q < 100; q++)
	{
		tree = new ClassTree(int(lcg()));
		t = *tree;

		for (int j = 0; j < k+q*(k/10); j++)
		{
			x = lcg();
			while (t.contains(x) == true) x = lcg();
			t.insert(x);
		}
		/*for (int j = 0; j < k + q * (k / 10); j++)
		{
			x = lcg();
			while ((find(v.begin(), v.end(), x) != v.end())== true) x = lcg();
			v.push_back(x);
		}*/

		/*for (int i = 0; i < 100; i++)
		{
			tree = new ClassTree(int(lcg()));
			t = *tree;

			for (int j = 0; j < k; j++)
			{
				start = clock();
				t.insert(lcg());
				end = clock();
				average_time[j][i] = (double(end - start)) / (double(CLOCKS_PER_SEC));
			}

			if (i != 99) t.Delete(t.GetRoot());
		}

		double sum;
		for (int i = 0; i < k; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				start = clock();
				t.insert(lcg());
				end = clock();
				average_time[j][i] = (double(end - start)) / (double(CLOCKS_PER_SEC));
			}
			if (out.is_open())
			{
				out << sum / 100 << std::endl;
			}
		}
		cout << endl << "Time of filling tree by " << k << " elements = " << average_time << endl;
		out.close();*/

		if (out.is_open())
		{
			out << k + q * (k / 10) << '\t';
		}

		av_t = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while (t.contains(x) == false) x = lcg();
			start = clock();
			t.Poisk(x, t.GetRoot());
			end = clock();
			av_t += (double(end - start)) / (double(CLOCKS_PER_SEC));
		}
		av_t /= 1000;
		poisk_time[q] = av_t;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << "Time of find random number in the tree of " << k + q * (k / 10) << " elements = " << av_t << endl;

		av_t = av_d = 0;
		for (int i = 0; i < 1000; i++)
		{
			x = lcg();
			while (t.contains(x) == true) x = lcg();
			start = clock();
			t.insert(x);
			end = clock();
			av_t += (double(end - start)) / (double(CLOCKS_PER_SEC));

			start = clock();
			t.erase(x, t.GetRoot());
			end = clock();
			av_d += (double(end - start)) / (double(CLOCKS_PER_SEC));
		}
		av_t /= 1000;
		insert_time[q] = av_t;
		av_d /= 1000;
		delete_time[q] = av_d;
		if (out.is_open())
		{
			out << av_t << '\t';
		}
		cout << endl << "Time of insert random number in the tree of " << k + q * (k / 10) << " elements = " << av_t << endl;
		if (out.is_open())
		{
			out << av_d << endl;
		}
		cout << endl << "Time of delete random number in the tree of " << k + q * (k / 10) << " elements = " << av_t << endl;

		t.Delete(tree->GetRoot());
		//v.clear();
	}

	out.close();
	delete[] insert_time;
	delete[] delete_time;
	delete[] poisk_time;
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
	int a_size = 0; //������ ������������� �������
	int a_cur = 0; //������� �������
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
			system("cls");
			if (a_size == 0) cout << "Trees is not exist" << endl;
			else 
			{
				array = DeleteTree(array, a_cur, &a_size);
				if (a_cur == a_size) a_cur -= 1;
			}
			system("pause");
			break;
		case 51:
			while (true)
			{
				system("cls");
				int m2 = menu2();
				if (m2 == 27) break;
				switch (m2)
				{
				case 49:
					Research(1000);
					break;
				case 50:
					Research(10000);
					break;
				case 51:
					Research(100000);
					break;
				}
				system("pause");
			}
			break;
		case 52:
			system("cls");
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