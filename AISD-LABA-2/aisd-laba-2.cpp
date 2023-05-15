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

int Random_Number()
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(-999, 999); // distribute results between -99999 and 99999 inclusive.

	return dist(gen);
}

template <class T>
T InputValue()
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

int menu_example()
{
	cout << "Press 1 to use vastavki sort" << endl;
	cout << "Press 2 to use fast sort" << endl;
	cout << "Press 3 to to use merge sort" << endl;

	cout << "\nPress Esc to back to the man menu" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 27)) return key;
	}
}

int menu_sorts()
{
	cout << endl << "This is main menu" << endl;
	cout << "Press 1 to research random vector" << endl;
	cout << "Press 2 to research sorted vector" << endl;
	cout << "Press 3 to research reversed vector" << endl;
	cout << "Press 4 to times of sorts" << endl;
	cout << "Press 5 to use your vector" << endl;

	cout << "\nPress Esc to finish the program" << endl;
	while (true)
	{
		int key = getkey();
		if ((key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 27)) return key;
	}
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

template <class T>
void CreateArr(vector<T>& arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << i + 1 << " = ";
		arr.push_back(InputValue<T>());
	}
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

//------------------------------------------------------------------------------------------------------------

template <class T>
void Create_Random_Vector(vector<T>& v, int n)
{
	for (int i = 0; i < n; i++)
	{
		T x = Random_Number();
		v.push_back(x);
	}
}

template <class T>
void Revers_Vector(vector<T>& v, int n) 
{
	for (int i = 0; i < n / 2; i++) {
		T tmp = v[i];
		v[i] = v[(n - 1) - i];
		v[(n - 1) - i] = tmp;
	}
}

template <class T>
void Research_Random_Vector(int* nums)
{
	ofstream out; 
	out.open("research.txt", ios_base::app);

	cout << "results for random vector" << endl;
	out << "results for random vector\n\n";

	for (int j = 0; j < 13; j++)
	{
		stats s_vs, s_fs, s_ms;
		vector<T> arr;

		int n = nums[j];
		cout << endl << n << endl;
		out << n << endl;
		for (int i = 0; i < 100; i++)
		{
			stats vs;
			Create_Random_Vector(arr, n);
			vs = Vstavki(arr, n);
			s_vs.comparison_count += vs.comparison_count;
			s_vs.copy_count += vs.copy_count;
			if (n >= 25000)
				cout << n << " - rand vs - " << i << endl;
			arr.clear();
		}

		out << "Count of copies in vstavki sort = " << s_vs.copy_count / 100 << "; Count of comparison in vstavki sort = " << s_vs.comparison_count / 100 << endl;
		cout << "Count of copies in vstavki sort = " << s_vs.copy_count / 100 << "; Count of comparison in vstavki sort = " << s_vs.comparison_count / 100 << endl;

		for (int i = 0; i < 100; i++)
		{
			stats fs;
			Create_Random_Vector(arr, n);

			Fast_Sort(arr, 0, n - 1, &fs);
			s_fs.comparison_count += fs.comparison_count;
			s_fs.copy_count += fs.copy_count;
			if (n >= 25000)
				cout << n << " - rand fs - " << i << endl;
			arr.clear();
		}

		out << "Count of copies in fast sort = " << s_fs.copy_count / 100 << "; Count of comparison in fast sort = " << s_fs.comparison_count / 100 << endl;
		cout << "Count of copies in fast sort = " << s_fs.copy_count / 100 << "; Count of comparison in fast sort = " << s_fs.comparison_count / 100 << endl;

		for (int i = 0; i < 100; i++)
		{
			stats ms;
			Create_Random_Vector(arr, n);

			Merge_Sort(arr, 0, n - 1, n, &ms);
			s_ms.comparison_count += ms.comparison_count;
			s_ms.copy_count += ms.copy_count;
			if (n >= 25000)
				cout << n << " - rand ms - " << i << endl;
			arr.clear();
		}

		out << "Count of copies in merge sort = " << s_ms.copy_count / 100 << "; Count of comparison in merge sort = " << s_ms.comparison_count / 100 << endl;
		cout << "Count of copies in merge sort = " << s_ms.copy_count / 100 << "; Count of comparison in merge sort = " << s_ms.comparison_count / 100 << endl;
		
		out << endl;
		cout << endl;
	}
	out.close();

}

template <class T>
void Research_Sorted_Vector(int* nums)
{
	ofstream out; 
	out.open("research.txt", ios_base::app);

	
	cout << "results for sorted vector" << endl;
	out << "results for sorted vector\n\n";

	for (int i = 0; i < 13; i++)
	{
		vector<T> arr;
		stats vs, fs, ms, f;

		int n = nums[i];
		cout << endl << n << endl;
		out << n << endl;

		Create_Random_Vector(arr, n);
		Fast_Sort(arr, 0, n - 1, &f);

		vs = Vstavki(arr, n);
		Fast_Sort(arr, 0, n - 1, &fs);
		Merge_Sort(arr, 0, n - 1, n, &ms);

		cout << "Count of copies in vstavki sort = " << vs.copy_count << "; Count of comparison in vstavki sort = " << vs.comparison_count << endl;
		//cout << "Count of copies in fast sort = " << fs.copy_count<< "; Count of comparison in fast sort = " << fs.comparison_count<< endl;
		cout << "Count of copies in merge sort = " << ms.copy_count<< "; Count of comparison in merge sort = " << ms.comparison_count << endl;
		cout << endl;

		out << "Count of copies in vstavki sort = " << vs.copy_count << "; Count of comparison in vstavki sort = " << vs.comparison_count << endl;
		//out << "Count of copies in fast sort = " << fs.copy_count << "; Count of comparison in fast sort = " << fs.comparison_count << endl;
		out << "Count of copies in merge sort = " << ms.copy_count<< "; Count of comparison in merge sort = " << ms.comparison_count << endl;
		out << endl;

		arr.clear();
	}
	out.close();
}

template <class T>
void Research_Reversed_Vector(int* nums)
{
	ofstream out; 
	out.open("research.txt", ios_base::app);


	cout << "results for reversed vector" << endl;
	out << "results for reversed vector\n\n";

	for (int i = 0; i < 13; i++)
	{
		vector<T> arr;
		stats vs, fs, ms, f;

		int n = nums[i];
		cout << endl << n << endl;
		out << n << endl;

		Create_Random_Vector(arr, n);
		Fast_Sort(arr, 0, n - 1, &f);
		Revers_Vector(arr, n);

		vs = Vstavki(arr, n);
		//Fast_Sort(arr, 0, n - 1, &fs);
		Merge_Sort(arr, 0, n - 1, n, &ms);

		cout << "Count of copies in vstavki sort = " << vs.copy_count << "; Count of comparison in vstavki sort = " << vs.comparison_count << endl;
		//cout << "Count of copies in fast sort = " << fs.copy_count << "; Count of comparison in fast sort = " << fs.comparison_count << endl;
		cout << "Count of copies in merge sort = " << ms.copy_count << "; Count of comparison in merge sort = " << ms.comparison_count << endl;
		cout << endl;

		out << "Count of copies in vstavki sort = " << vs.copy_count << "; Count of comparison in vstavki sort = " << vs.comparison_count << endl;
		//out << "Count of copies in fast sort = " << fs.copy_count << "; Count of comparison in fast sort = " << fs.comparison_count << endl;
		out << "Count of copies in merge sort = " << ms.copy_count << "; Count of comparison in merge sort = " << ms.comparison_count << endl;
		out << endl;

		arr.clear();
	}
	out.close();
}

template <class T>
void Research_Times()
{
	ofstream out;
	out.open("research.txt", ios_base::app);
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	double average_t;

	cout << "times of sorts (microseconds)" << endl;
	out << "times of sorts (microseconds)\n\n";

	for (int n = 1000; n <= 10000; n += 1000)
	{
		vector<T> arr;

		cout << endl << n << endl;
		out << n << endl;

		average_t = 0;
		for (int i = 0; i < 100; i++)
		{
			stats vs;
			Create_Random_Vector(arr, n);
			start = chrono::steady_clock::now();
			vs = Vstavki(arr, n);
			end = chrono::steady_clock::now();
			average_t += double(chrono::duration_cast<chrono::microseconds>(end - start).count());
			arr.clear();
		}
		cout << "average time of vstavki sort = " << average_t / 100 << endl;
		out << "average time of vstavki sort = " << average_t / 100 << endl;

		average_t = 0;
		for (int i = 0; i < 100; i++)
		{
			stats fs;
			Create_Random_Vector(arr, n);
			start = chrono::steady_clock::now();
			Fast_Sort(arr, 0, n - 1, &fs);
			end = chrono::steady_clock::now();
			average_t += double(chrono::duration_cast<chrono::microseconds>(end - start).count());
			arr.clear();
		}
		cout << "average time of fast sort = " << average_t / 100 << endl;
		out << "average time of fast sort = " << average_t / 100 << endl;

		average_t = 0;
		for (int i = 0; i < 100; i++)
		{
			stats ms;
			Create_Random_Vector(arr, n);
			start = chrono::steady_clock::now();
			Merge_Sort(arr, 0, n - 1, n, &ms);
			end = chrono::steady_clock::now();
			average_t += double(chrono::duration_cast<chrono::microseconds>(end - start).count());
			arr.clear();
		}
		cout << "average time of merge sort = " << average_t / 100 << endl;
		out << "average time of merge sort = " << average_t / 100 << endl;

		out << endl;
		cout << endl;
	}
	out.close();
}

template <class T>
void Example()
{
	while(true)
	{
		system("cls");
		vector<T> arr;
		stats s;
		int n;
		cout << "Insert number of elements > 0" << endl;
		n = InputValue<int>();
		while (n <= 0)
		{
			cout << "Insert correct value" << endl;
			n = InputValue<int>();
		}
		CreateArr(arr, n);
		PrintArr(arr, n);
		int m = menu_example();
		switch (m)
		{
		case 49:
			Vstavki(arr, n);
			break;
		case 50:
			Fast_Sort(arr, 0, n - 1, &s);
			break;
		case 51:
			Merge_Sort(arr, 0, n - 1, n, &s);
			break;
		case 27:
			return;
		}
		PrintArr(arr, n);
		system("pause");

	}

}


int main()
{
	cout << "HELLO, THIS IS THE SECOND LAB BY ZAMOTOHINA MARIA" << endl;
	ofstream out;
	out.open("research.txt", ios_base::trunc);
	int n[13] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000};
	//int n[4] = { 1000, 2000, 3000, 4000};
	while(true)
	{
		system("cls");
		int m = menu_sorts();

		switch (m)
		{
		case 49:
			system("cls");
			Research_Random_Vector<int>(n);
			system("pause");
			break;
		case 50:
			system("cls");
			Research_Sorted_Vector<int>(n);
			system("pause");
			break;
		case 51:
			system("cls");
			Research_Reversed_Vector<int>(n);
			system("pause");
			break;
		case 52:
			system("cls");
			Research_Times<int>();
			system("pause");
			break;
		case 53:
			system("cls");
			Example<int>();
			system("pause");
			break;
		case 27:
			return 0;
		}
	}

	return 0;
}