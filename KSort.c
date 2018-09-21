#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//o(n/k)
int Partation(int a[], int start, int end, int k) {
	int j = start - k;
	int key = a[start];
	for (int i = start; i <= end; i+=k) {
		if (a[i] <= key) {
			j += k;
			swap(&a[j], &a[i]);
		}
	}
	swap(&a[j], &a[start]);
	return j;
}

//o(n/k*lg(n/k))
void QuickSortK(int a[], int start, int end, int k) {
	if (start <= end) {
		int q = Partation(a, start, end, k);
		QuickSortK(a, start, q - 1, k);
		QuickSortK(a, q+1, end, k);
	}
}

//k排序o(n*lg(n/k))
void SortK(int a[], int start, int end, int k) {
	for (int i = 1; i <= k; ++i) {
		QuickSortK(a, start + i - 1, end, k);
	}
}


int main() {
	int a[] = { 9,8,6,4,5,7,1,3,2 };
	int len = sizeof(a) / sizeof(int);
	SortK(a, 0, len - 1, 1);
	for (int i = 0; i < len; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
	return 0;
}
