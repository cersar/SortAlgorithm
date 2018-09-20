#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int match(int a[],int start,int end,int key) {
	for (int i = start; i <= end; ++i) {
		if (a[i] == key)
			return i;
	}
	return -1;
}

int partation(int a[], int start, int end, int p) {
	swap(&a[p], &a[end]);
	int j = start - 1;
	int key = a[end];
	for (int i = start; i < end; ++i) {
		if (a[i] < key)
			swap(&a[++j], &a[i]);
	}
	swap(&a[++j], &a[end]);
	return j;
}

void MatchJug(int red[],int blue[],int start,int end) {
	if (start <= end) {
		time_t t;
		srand((unsigned)time(&t));
		int i = rand() % (end - start + 1) + start;
		int j = match(blue, start, end, red[i]);
		printf("(%d,%d)\n", red[i], blue[j]);
		int p = partation(red, start, end, i);
		int q = partation(blue, start, end, j);
		assert(p == q);
		MatchJug(red, blue, start, p - 1);
		MatchJug(red, blue, p + 1, end);
	}
}

int main() {
	int red[] = { 1,3,2,5,4 };
	int blue[] = { 3,4,5,2,1 };
	MatchJug(red, blue, 0, sizeof(red) / sizeof(int) - 1);
	return 0;
}
