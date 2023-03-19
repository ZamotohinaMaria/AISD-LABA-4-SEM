#include <iostream>
#include "ClassTree.h"
#include <stdio.h>
#include <conio.h>

#define Treelevel 3

using namespace std;

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

//void IncreaseArray (ClassTree** array, int* a_max)
//{
//	ClassTree* new_array = new ClassTree(*(a_max) + 10);
//	
//	for (int i = 0; i < *a_max; i++)
//		new_array[i] = (*array)[i];
//	delete[](*array);
//	(*array) = new_array;
//	(*a_max) += 10;
//}

ClassTree CreateTree()
{
	cout << "Input root value: ";
	int x;
	x = InputValue();
	ClassTree t(x);

	cout << "Input number of elements in the tree: ";
	int n;
	cin >> n;
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
	//(*array[i]).print((*array[i]).GetRoot(), Treelevel);
	system("pause");
	return t;
}

//после текущего элемента
ClassTree* InsertInArray(ClassTree* array, int a_cur, int* a_size)
{
	system("cls");
	ClassTree* new_array = new ClassTree[*a_size + 1];

	for (int i = 0; i < *a_size + 1; i++)
	{
		if (i <=  a_cur)
			new_array[i] = array[i];
		else if (i > a_cur + 1)
			new_array[i] = array[i - 1];
	}

	*a_size += 1;
	return new_array;
}

void DeleteTree(ClassTree** array, int a_cur, int* a_size)
{
	ClassTree* new_array = new ClassTree[*a_size - 1];

	for (int i = 0; i < *a_size; i++)
	{
		if (i < a_cur)
			new_array[i] = *array[i];
		else if (i == a_cur)
		{
			ClassTree tmp = *array[i];
			while (tmp.GetRoot())
			{
				tmp.erase((tmp.GetRoot())->data, tmp.GetRoot());
			}
			delete &tmp;
		}
		else  if (i >= a_cur)
			new_array[i] = *array[i + 1];
	}

	*array = new_array;
	*a_size -= 1;
}

int menu1()
{
	cout << endl << "This is main menu" << endl;
	cout << "Press 1 to create new tree" << endl;
	cout << "Press 2 to delete tree on the screen" << endl;

	cout << "Navigation:" << endl;
	cout << "\tNext tree ->" << endl; //77
	cout << "\tPrev tree <-" << endl; //75
	cout << "Press Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 27) || (key == 77) || (key == 75)) return key;
	}
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
			*(array + a_cur) = CreateTree();
			
			//cout << array[0].GetRoot()->data;
			//array[0].print(array[0].GetRoot(), Treelevel);
			system("pause");
			break;
		case 50:
			system("cls");
			if (a_size == 0) cout << "Trees is not exist";
			DeleteTree(&array, a_cur, &a_size);
			if (a_cur == a_size) a_cur -= 1;
			system("pause");
			break;
		}
	}
	/*cout << "Input root value: ";
	int x;
	x = InputValue();

	ClassTree t(x);

	for (int i = 0; i < 10; i++)
	{
		cout << "Input new value, № " << i << endl;
		x = InputValue();
		while (t.insert(x) == false)
		{
			cout << "This value is exist. Please, input new value" << endl;
			x = InputValue();
		}
	}

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