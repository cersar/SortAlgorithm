// VariableLengthSort.cpp : 定义控制台应用程序的入口点。
//

#include<stdio.h>
#include<stdlib.h>
#define MAX_LEN 6

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//获取数字的位数
int getDigitNum(int a) {
	int cnt = 0;
	while (a / 10) {
		cnt++;
		a /= 10;
	}
	cnt++;
	return cnt;
}

//获取数字的某一位
int getDigit(int a,int ind) {
	int cnt = 0;
	for (int i = 1; i < ind; ++i) {
		a /= 10;
	}
	return a % 10;
}

//以数字的位数进行计数排序(不稳定排序)
void countSortByDigitNum(int a[], int position[], int start, int end) {
	int c[MAX_LEN + 1] = { 0 };
	for (int i = start; i <= end; ++i) {
		c[getDigitNum(a[i])]++;
	}
	for (int i = 1; i <= MAX_LEN; ++i) {
		c[i] += c[i - 1];
		position[i] = c[i];
	}
	position[0] = c[0];
	int i = start,digitNum;
	while (i < end) {
		//getDigitNum(a[i])>=1
		digitNum = getDigitNum(a[i]);
		if (i >= position[digitNum - 1]) {
			i++;
		}
		else {
			swap(&a[i], &a[c[digitNum] - 1]);
			c[digitNum]--;
		}
	}
	

}

//以数字的某一位进行计数排序(稳定排序)
void countSortByDigit(int a[], int start, int end,int ind) {
	int *tmp = NULL;
	int c[10] = { 0 };
	if (start <= end) {
		tmp = (int *)malloc(sizeof(int)*(end - start + 1));
	}
	for (int i = start; i <= end; ++i) {
		c[getDigit(a[i],ind)]++;
	}
	for (int i = 1; i < 10; ++i) {
		c[i] += c[i - 1];
	}
	int digit;
	for (int i = end; i >= start; --i) {
		digit = getDigit(a[i], ind);
		tmp[c[digit] - 1] = a[i];
		c[digit]--;
	}

	if (tmp != NULL) {
		free(tmp);
		tmp = NULL;
	}

}


void radixSort(int a[], int start, int end,int digitNum) {
	if (start <= end) {
		for (int i = 1; i <= digitNum; ++i) {
			countSortByDigit(a, start, end, i);
		}
	}
}

int main()
{
	int a[] = { 100,10,12,1356 };
	int c[MAX_LEN + 1] = { 0 };
	int len = sizeof(a) / sizeof(int);
	//首先根据数字的位数进行排序o(n)
	countSortByDigitNum(a, c, 0, len - 1);
	//o(MAX_LEN*n)
	for (int i = 1; i <= MAX_LEN; ++i) {
		//对于位数相同的数字，进行基数排序
		radixSort(a, c[i - 1], c[i] - 1, i);
	}
	for (int i = 0; i < len; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
    return 0;
}

