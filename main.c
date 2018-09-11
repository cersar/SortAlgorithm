
#include<stdio.h>
#include<time.h>


void swap(int *i, int *j) {
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

void printArray(int a[], int start, int end) {
	for (int i = start; i <= end; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}


//冒泡排序
void bubbleSort(int a[], int start, int end, long &cntDect,long &cntSwap) {
	int flag;
	for (int i = start; i <= end - 1; ++i) {
		flag = false;
		for (int j = start; j <= end - 1 - i; j++) {
			cntDect++;
			if (a[j] > a[j + 1]) {
				swap(&a[j], &a[j + 1]);
				cntSwap++;
				flag = true;
			}
		}
		if (flag == false) break;

	}
}

//选择排序
void selectSort(int a[], int start, int end, long &cntDect, long &cntSwap) {
	int min;
	for (int i = start; i <= end - 1; ++i) {
		min = i;
		for (int j = i + 1; j <= end; j++) {
			cntDect++;
			if (a[min] > a[j]) {
				min = j;
			}
		}
		swap(&a[i], &a[min]);
		cntSwap++;

	}

}

//插入排序
void insertSort(int a[], int start, int end, long &cntDect, long &cntSwap) {
	int key;
	int i, j;
	for (i = start+1; i <= end; ++i) {
		key = a[i];
		cntDect++;
		for (j = i - 1; j >= start&&a[j] > key; --j) {
			a[j + 1] = a[j];
			cntSwap++;
		}
		a[j + 1] = key;
		cntSwap++;
	}
	//循环里统计的cntSwap为元素的移动次数，这里折算为swap次数时减半
	cntSwap /= 2;
}

int main() {
	clock_t startTime, endTime;
	double  duration;
	long cntDect = 0, cntSwap = 0;
	int a[] = { 9,8,7,6,5,4,3,2,1 };
	startTime = clock();

//      bubbleSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      slectSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      insertSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);

	endTime = clock();
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	printArray(a, 0, sizeof(a) / sizeof(int) - 1);

	printf("%f seconds\n", duration);
	printf("Total detection times: %d\n", cntDect);
	printf("Total swap times: %d\n", cntSwap);
	return 0;
}
