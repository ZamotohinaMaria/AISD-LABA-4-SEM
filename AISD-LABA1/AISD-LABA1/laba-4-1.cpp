#include <iostream>
#include "ClassTree.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>

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
	cout << "Input root value: ";
	int x = InputValue();
	ClassTree t(x);

	cout << "Input number of elements in the tree: ";
	int n = InputValue();
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
			/*while (array[i].GetRoot())
			{
				array[i].erase((array[i].GetRoot())->data, array[i].GetRoot());
				cout << "===============" << endl;
				array[i].print(array[i].GetRoot(), Treelevel);
			}*/
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

	cout << "Navigation:" << endl;
	cout << "\tNext tree ->" << endl; //77
	cout << "\tPrev tree <-" << endl; //75
	cout << "Press Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 27) || (key == 77) || (key == 75)) return key;
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
	clock_t start, end;
	double average_time = 0;
	size_t x;

	average_time = 0;
	for (int i = 0; i < 100; i += 1)
	{
		tree = new ClassTree(int(lcg()));
		t = *tree;

		start = clock();
		for (int j = 0; j < k; j++)
			t.insert(lcg());
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
		//cout << "average time = " <<average_time;

		if (i != 99) t.Delete(t.GetRoot());
	}
	//t.print(t.GetRoot(), Treelevel);
	average_time /= 100;
	cout << endl << "Time of filling tree by " << k << " elements = " << average_time << endl;

	average_time = 0;
	for (int i = 0; i < 1000; i++)
	{
		x = lcg();
		while (t.contains(x) == false) x = lcg();
		start = clock();
		t.Poisk(x, t.GetRoot());
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
		//cout << "average time = " << average_time;
	}
	average_time /= 100;
	cout << endl << "Time of find random number in the tree of " << k << " elements = " << average_time << endl;

	average_time = 0;
	for (int i = 0; i < 1000; i++)
	{
		x = lcg();
		while (t.contains(x) == true) x = lcg();
		start = clock();
		t.insert(x);
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
		//if (k == 100000) cout << "average time = " << average_time;
	}
	average_time /= 100;
	cout << endl << "Time of insert random number in the tree of " << k << " elements = " << average_time << endl;

	average_time = 0;
	for (int i = 0; i < 1000; i++)
	{
		x = lcg();
		while (t.contains(x) == false) x = lcg();
		start = clock();
		t.erase(x, t.GetRoot());
		end = clock();
		average_time += (double(end - start)) / (double(CLOCKS_PER_SEC));
		//cout << "average time = " << average_time;
	}
	average_time /= 100;
	cout << endl << "Time of deleting random number in the tree of " << k << " elements = " << average_time << endl;

	t.Delete(tree->GetRoot());
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
		}
	}
	
	/*int x;

	ClassTree t = CreateTree();
	cout << "===============" << endl;
	ClassTree p = CreateTree();
	t.print(t.GetRoot(), Treelevel);
	cout << "===============" << endl;
	p.print(p.GetRoot(), Treelevel);
	t = p;


	t.print(t.GetRoot(), Treelevel);
	cout << "--------------------------" << endl;
	cout << t.contains(5) << endl;
	cout << "Input element to delete it" << endl;
	x = InputValue();
	t.erase(x, t.GetRoot());
	t.print(t.GetRoot(), Treelevel);
	cout << "--------------------------" << endl;*/

	return 0;
}