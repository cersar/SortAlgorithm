
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
		cntDect++;
		for (int j = start; j <= end - 1 - i; j++) {
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
		cntDect++;
		for (int j = i + 1; j <= end; j++) {
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

void copy(int a[],int b[],int start,int end){
	for(int i=start;i<=end;++i){
		b[i]=a[i];
	}
}

void merge(int a[],int b[],int start,int end,int mid,long &cntDect,long &cntSwap){
	int i=start,j=mid+1; 
	 for(int k=start;k<=end;k++)
		if(i>mid){
			copy(a,b,j,end);
			break;
		}
		if(j>end){
			copy(a,b,i,end);
			break;
		}
		
	    if(a[i]<a[j]){
	    	cntSwap++;
	    	b[k]=a[i++]; 
		}else{
			cntSwap++;
			b[k++]=a[j++];
		}		
	}
	
	copy(b,a,start,end); 
	
}

//归并排序
void mergeSort(int a[], int tmp[],int start, int end, long &cntDect,long &cntSwap){
	if(start<end){
		int mid = (start+end)/2;
		mergeSort(a,tmp,start,mid,cntDect,cntSwap);
		mergeSort(a,tmp,mid+1,end,cntDect,cntSwap);
		merge(a,tmp,start,end,mid,cntDect,cntSwap);
	}
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
