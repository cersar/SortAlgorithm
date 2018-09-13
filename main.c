
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
				//这里忽略min序号变更的操作统计
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
		for (j = i - 1; j >= start&&a[j] > key; --j) {
			cntDect++;
			a[j + 1] = a[j];
			cntSwap++;
		}
		a[j + 1] = key;
		cntSwap++;
	}
	//循环里统计的cntSwap为元素的移动次数，这里折算为swap次数时减半
	cntSwap /= 2;
}


//shell排序
void shellSort(int a[], int start, int end, long &cntDect, long &cntSwap) {
	int key;
	int i, j,step=1;
	
	while(step<=end-start) step=step*3+1;
	step=(step-1)/3;
	while(step>=1){
		for (i = start+step; i <= end; i++) {
			key = a[i];
			for (j = i - step; j >= start&&a[j] > key; j-=step) {
				cntDect++;
				a[j + step]=a[j];
				cntSwap++;
			}
			a[j+step]=key;
			cntSwap++;
		}
		step=(step-1)/3;
	}
	
}

void merge(int a[], int b[], int start, int end, int mid, long &cntDect, long &cntSwap) {
	for (int i = start; i <= mid; ++i) {
		cntDect++;
		b[i] = a[i];
		cntSwap++;
	}
	b[mid + 1] = INT_MAX;

	for (int i = mid+1; i <= end; ++i) {
		cntDect++;
		b[i+1] = a[i];
		cntSwap++;
	}
	b[end + 2] = INT_MAX;

	int i = start, j = mid + 2;
	for (int k = start; k <= end;++k) {
		cntDect++;
		if (b[i] < b[j]) {
			a[k] = b[i++];
			cntSwap++;
		}
		else {
			a[k] = b[j++];
			cntSwap++;
		}
	}
}

//归并排序
void mergeSort(int a[], int b[], int start, int end, long &cntDect, long &cntSwap) {
	if (start < end) {
		int mid = (start + end) / 2;
		mergeSort(a, b, start, mid, cntDect, cntSwap);
		mergeSort(a, b, mid+1, end, cntDect, cntSwap);
		merge(a, b, start, end, mid, cntDect, cntSwap);
	}

}

int partation(int a[],int start,int end, long &cntDect, long &cntSwap){
	int p = start-1,q=end+1,key=a[start];
	while(1){
		do{
			p++;
		}while(a[p]<key);
		do{
			q--;
		}while(a[q]>key);
		if(p<q){
			swap(&a[p],&a[q]);
		}else{
			//这里选q作为分割点，原因是结束时q∈[start,end),保证q+1和q不超出[start,end],防止死循环 
			//证明q∈[start,end):
			// 1)证明q>=start：注意到，每执行一次swap，意味着将小于等于key的值置于q之前，执行swap的次数>=0,
			//当循环结束时执行swap次数>0时，则循环结束之前，q的前面至少有一个小于key的值，循环结束时必有q>=start;
			//当循环结束时执行swap的次数为0时，说明外层while循环只执行一次，此时p=start=q,q>=start也成立
			//综上，q>=start 
			//2)证明q<end：(反证法)首先，显然q<=end,假设q=end，即外层while循环执行一次便跳出
			//此时p=start&&p>=q,则q=start=end,这与start<end矛盾，故q<end; 
			return q;
		}
	}
}

//快速排序
void quickSort(int a[], int start, int end, long &cntDect, long &cntSwap) {
	if(start<end){
		int p = partation(a,start,end,cntDect,cntSwap);
		quickSort(a,start,p,cntDect,cntSwap);
		quickSort(a,p+1,end,cntDect,cntSwap);		
	}	
}


int main() {
	clock_t startTime, endTime;
	double  duration;
	long cntDect = 0, cntSwap = 0;
	int a[9] = { 9,8,7,6,5,4,3,2,1 },b[11];
	startTime = clock();

//      bubbleSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      slectSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      insertSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      mergeSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      shellSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);

	endTime = clock();
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	printArray(a, 0, sizeof(a) / sizeof(int) - 1);

	printf("%f seconds\n", duration);
	printf("Total detection times: %d\n", cntDect);
	printf("Total swap times: %d\n", cntSwap);
	return 0;
}
