#include <stdio.h>
#include <iostream>

using namespace std;

void print_all_mas(int* mas, int len) {
	for (int i = 0; i < len; i++) cout << mas[i] <<" ";
	cout << endl;
}
//
//
//
int linear_search(int*mas, int len, int num) {
	int i = 0;
	while (i < len) {
		if (mas[i] == num) return i;
		i++;
	}
	return -1;
}

template <class T>
int bin_search(int left, int right, T* mas, T num) {
	int l = left, r = right;
	while (l < r) {
		int med = (r + l) / 2;
		if (num < mas[med]) r = med;
		else l = med + 1;
	}
	r--;
	return r;
}

int interpol_search(int left, int right, int* mas, int num) {
	bool found = false;
	int x = 0;
	int l = left, r = right;
	while ((!found) && (mas[l] < num) && (num < mas[r])) {
		x = (num - mas[l]) * (r - l);
		x /= (mas[r] - mas[l]);
		x += l;
		if (mas[x] < num) {
			l = x + 1;
		}
		else if (mas[x] > num) {
			r = x - 1;
		}
		else {
			found = true;
		}
	}
	return x;
}
//
//
//
template <class T>
void inserts_sort(T* mas, int len) {
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j > 0 && mas[j - 1] > mas[j]; j--) {
			T tmp = mas[j];
			mas[j] = mas[j - 1];
			mas[j - 1] = tmp;
		}
	}
}

template <class T>
void bubble_sort(T* mas, int len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (mas[j] > mas[j + 1]) {
				T tmp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = tmp;
			}
		}
	}
}

template <class T>
void bin_inserts_sort(T* mas, int len) {
	for (int i = 1; i < len; i++) {
		int index = bin_search(0, i-1, mas, mas[i]) + 1;
		for (int j = i; j > index; j--) {
			T tmp = mas[j];
			mas[j] = mas[j - 1];
			mas[j - 1] = tmp;
		}
	}
}

template <class T>
void shell_sort(T* mas, int len) {
	int step = 0, i = 0, j = 0;
	for (step = len / 2; step > 0; step /= 2) {
		for (i = step; i < len; i++) {
			T tmp = mas[i];
			for (j = i; j >= step; j -= step) {
				if (tmp < mas[j - step]) {
					mas[j] = mas[j - step];
				}
				else break;
			}
			mas[j] = tmp;
		}
	}
}

template <class T>
void shaker_sort(T* mas, int len) {
	int l = 0, r = len, swap_flag = 1;
	while ((l < r) && (swap_flag > 0)) {
		swap_flag = 0;
		for (int i = l; i < r; i++) {
			if (mas[i] > mas[i + 1]) {
				T tmp = mas[i];
				mas[i] = mas[i + 1];
				mas[i + 1] = tmp;
				swap_flag = 1;
			}
		}
		r--;
		for (int i = r; i > l; i--) {
			if (mas[i] < mas[i - 1]) {
				T tmp = mas[i];
				mas[i] = mas[i - 1];
				mas[i - 1] = tmp;
				swap_flag = 1;
			}
		}
		l++;
	}
}

template <class T>
void change_sort(T* mas, int len) {
	int min_index = 0;
	for (int i = 0; i < len; i++) {
		min_index = i;
		for (int j = i+1; j < len; j++) {
			if (mas[j] < mas[min_index]) min_index = j;
		}
		T tmp = mas[i];
		mas[i] = mas[min_index];
		mas[min_index] = tmp;
	}
}

template <class T>
void fast_sort(T* mas, int left, int right) {
	T perm = mas[left];
	int l = left, r = right;
	while (left < right) {
		while ((mas[right] >= perm) && (left < right)) 
			right--;
		if (left != right) {
			mas[left] = mas[right];
			left++;
		}
		while ((mas[left] <= perm) && (left < right)) 
			left++;
		if (left != right) {
			mas[right] = mas[left];
			right--;
		}
	}
	
	mas[left] = perm;
	perm = left;
	left = l;
	right = r;
	if (left < perm) fast_sort(mas, left, perm - 1);
	if (right > perm) fast_sort(mas, perm + 1, right);

}

template <class T>
void merge(T* mas, int first, int last) {
	int middle = (first + last) / 2;
	int start = first;
	int final = middle + 1;

	T* help_mas = new T[100];
	for (int j = first; j <= last; j++) {
		if ((start <= middle) && ((final > last) || (mas[start] < mas[final]))) {
			help_mas[j] = mas[start];
			start++;
		}
		else {
			help_mas[j] = mas[final];
			final++;
		}
	}

	for (int j = first; j <= last; j++) mas[j] = help_mas[j];
	delete[] help_mas;
}

template <class T>
void merge_sort(T* mas, int first, int last) {
	if (first < last) {
		merge_sort(mas, first, (first + last) / 2);
		merge_sort(mas, (first + last) / 2 + 1, last);
		merge(mas, first, last);
	}
}

void main() {
	int a1 = 5, b1 = 10;
	int mas[10] = { 10,4,5,2,3,6,8,7,9,1 };
	print_all_mas(mas, 10);

	//inserts_sort(mas, 10);
	//bin_inserts_sort(mas, 10);
	//shell_sort(mas, 10);
	//shaker_sort(mas, 9);
	//change_sort(mas, 10);
	//fast_sort(mas, 0, 9);
	merge_sort(mas, 0, 9);


	print_all_mas(mas, 10);
	cout << linear_search(mas, 9, 3) << endl;
	cout << bin_search(0, 9, mas, 3) << endl;
	cout << interpol_search(0, 9, mas, 3);
}