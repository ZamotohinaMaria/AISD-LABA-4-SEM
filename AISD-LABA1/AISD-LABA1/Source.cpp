//#include <iostream>
//#include <stdio.h>
//#include <conio.h>
//
//using namespace std;
//
//int* insert(int* a, int af, int* size)
//{
//	int n = *size;
//	int* newa = new int[n+1];
//	for (int i = 0; i < n + 1; i++)
//	{
//		if (i <= af)
//			newa[i] = a[i];
//		else if (i == af + 1)
//		{
//			newa[i] = i + 100;
//		}
//		else if (i > af + 1)
//			newa[i] = a[i - 1];
//	}
//	*size = *size + 1;
//	return newa;
//}
//
//int main()
//{
//	int n = 3;
//	int* array = new int[3];
//	for (int i = 0; i < n; i++) array[i] = i + 1;
//	array = insert(array, 1, &n);
//	for (int i = 0; i < n; i++) cout << array[i] << endl;
//	return 0;
//}