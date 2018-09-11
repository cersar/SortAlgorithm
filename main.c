#include<stdio.h>
#include<time.h>


void swap(int *i, int *j) {
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

void bubbleSort(int a[], int start, int end) {
	clock_t startTime, endTime;
	startTime = clock();
	double  duration;
	int flag;
	long cntDect = 0, cntSwap = 0;
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
	endTime = clock();
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);
	printf("Total detection times: %d\n", cntDect);
	printf("Total swap times: %d\n", cntSwap);
}

void selectSort(int a[],int start,int end) {
	clock_t startTime, endTime;
	startTime = clock();
	double  duration;
	int min;
	long cntDect = 0, cntSwap = 0;
	for (int i = start; i <= end-1; ++i) {
		min = i;
		for (int j = i+1; j <= end; j++) {
			cntDect++;
			if (a[min] > a[j]) {
				min = j;
			}
		}
		swap(&a[i], &a[min]);
		cntSwap++;
		
	}
	endTime = clock();
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);
	printf("Total detection times: %d\n", cntDect);
	printf("Total swap times: %d\n", cntSwap);

}

void printArray(int a[], int start, int end) {
	for (int i = start; i <= end; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}

int main() {
	int a[] = { 1,9,2,8,3,7,4,6 };
//	bubbleSort(a, 0, sizeof(a) / sizeof(int) - 1);
//	SelectSort(a, 0, sizeof(a) / sizeof(int) - 1);
	printArray(a, 0, sizeof(a) / sizeof(int) - 1);
	return 0;
}
