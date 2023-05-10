// 1-2-1
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

int RandomNumber()
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(-999, 999); // distribute results between -99999 and 99999 inclusive.

	return dist(gen);
}

template <class T>
void PrintArr(vector<T> &arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << '\t';
	}
	cout << endl;
}

//int* VstavkiNotOptimaise(int* arr, int n)
//{
//	int* res = new int[n];
//	res[0] = arr[0];
//	int res_n = 1;
//	for (int i = 1; i < n; i++)
//	{
//		int j = res_n;
//		int tmp = arr[i];
//		for (int j = res_n; j >= 0; j--)
//		{
//			if (tmp > res[j - 1])
//			{
//				res[j] = tmp;
//				break;
//			}
//			else
//			{
//				res[j] = res[j - 1];
//				res[j - 1] = tmp;
//			}
//		}
//		res_n += 1;
//		PrintArr(res, res_n);
//	}
//
//	return res;
//}


template <class T>
stats Vstavki(vector<T> &arr, int n)
{
	stats s;
	for (int i = 1; i < n; i++)
	{
		int j = i;
		while (j >= 1 && arr[j] < arr[j - 1])
		{
			swap(arr[j], arr[j - 1]);
			j -= 1;
			s.comparison_count++;
			s.copy_count++;
		}
		//PrintArr(arr, n);
	}
	return s;
}


template <class T>
void Fast_Sort(vector<T>& arr, int left, int right, stats* s)
{
	if (right > left) {
		T separator = arr[right];
		int id_seperetor = left;
		for (int i = left; i < right; i++)
		{
			if (arr[i] <= separator)
			{
				swap(arr[i], arr[id_seperetor]);
				id_seperetor++;
				s->comparison_count++;
				s->copy_count++;
			}
		}

		swap(arr[id_seperetor], arr[right]);
		s->copy_count++;
		Fast_Sort(arr, left, id_seperetor - 1, s);
		Fast_Sort(arr, id_seperetor + 1, right, s);
	}
}

template <class T>
void merge(vector<T>& arr, int left, int right, int n, stats* s) {
	int middle = (left + right) / 2;
	int start_l = left;
	int start_r = middle + 1;

	vector<T> tmp_arr(n);
	for (int i = left; i <= right; i++) {
		if ((start_l <= middle) && ((start_r > right) || (arr[start_l] < arr[start_r]))) {
			tmp_arr[i] = arr[start_l];
			start_l++;
			s->comparison_count++;
			s->copy_count++;
		}
		else {
			tmp_arr[i] = arr[start_r];
			s->comparison_count++;
			s->copy_count++;
			start_r++;
		}
	}

	for (int i = left; i <= right; i++)
	{
		arr[i] = tmp_arr[i];
		s->copy_count++;
	}
	tmp_arr.clear();
}

template <class T>
void Merge_Sort(vector<T>& arr, int left, int right, int n, stats* s) {
	if (left < right) {
		Merge_Sort(arr, left, (left + right) / 2, n, s);
		Merge_Sort(arr, (left + right) / 2 + 1, right, n, s);
		merge(arr, left, right, n, s);
	}
}

int getkey()
{
	int key = getch();
	if ((key == 0) || (key == 224)) key = getch();
	return key;
}

int menu_sorts()
{
	cout << endl << "This is main menu" << endl;
	cout << "Press 1 to vstavki sort" << endl;
	cout << "Press 2 to fast sort" << endl;
	cout << "Press 3 to merge sort" << endl;

	cout << "\nPress Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 27)) return key;
	}
}

int main()
{
	int n = 10;
	vector<int> arr;
	for (int i = 0; i < n; i++) {
		int x = int(RandomNumber());
		arr.push_back(x);
	}
	stats vs;
	stats fs;
	stats ms;

	PrintArr(arr, n);
	cout << "----------------" << endl;

	int m1 = menu_sorts();
	if (m1 == 27)
		return 0;
	switch (m1)
	{
	case 49:
		vs = Vstavki(arr, n);
		cout << "vstavki copy = " << vs.copy_count << "; vstavki comprasion = " << vs.comparison_count << endl;
		break;
	case 50:
		Fast_Sort(arr, 0, n - 1, &fs);
		cout << "fast sort copy = " << fs.copy_count << "; fast sort comprasion = " << fs.comparison_count << endl;
		break;
	case 51:
		Merge_Sort(arr, 0, n - 1, n, &ms);
		cout << "merge sort copy = " << ms.copy_count << "; merge sort comprasion = " << ms.comparison_count << endl;
		break;
	}

	PrintArr(arr, n);
	
	return 0;
}