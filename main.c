
#include<stdio.h>
#include<time.h>

#define MAX 100


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

//第二个while循环结束时，循环不变式:
//1）a[start~(p-1)]<=key
//2）a[(q+1)~end]>=key
//3）a[p]>=key
//4）a[q]<=key
//5）p∈[start,end)
//6）q∈[start,end)
//循环不变式1）2）3）4）显然成立
//由循环不变式1）2）3）4）,可知交换a[p]和a[q]之后每一次循环开始都有a[start~p]<=key，a[q~end]>=key
//证明6）：
//1.q<end
//即证明q至少自减两次（反证法)
//如果q只自减一次，则有p+1=q-1，即start=end，与前提矛盾
//2.q>=start：
//由于p(k+1)>=start，且等号仅在p(1)时成立，当k>1时有p(k)>start
//第一次迭代时，由于a[p(1)]=key,q(1)>=p(1)=start
//第k>1次迭代，q(k)>=p(k)-1>=start
//证明5）：
//p>=start显然成立，下面证明p<end
//1）第一次循环，显然有p(1)<end
//2）假设第k次，有p(k)<end
//则第k+1次循环开始时a[start~p(k+1)]<=key，a[q(k+1)~end]>=key
//则p(k+1)<=q(k+1)<end

//循环结束时，p>=q，由循环不变式a[start~(p-1)]<=key，a[(q+1)~end]>=key，a[p]>=key，a[q]<=key
//可知a[start~q]<=key,a[(q+1)~end]>=key
//又q∈[start,end),可以保证子问题的规模不断减小，不会发生死循环
int partation(int a[], int start, int end) {
	int p = start - 1, q = end + 1, key = a[start];
	while (1) {
		do {
			p++;
		} while (a[p] < key);
		do {
			q--;
		} while (a[q] > key);
		if (p < q) {
			swap(a[p], a[q]);
		}
		else {
			return q;
		}
	}
}

//循环不变式：
//1）start<=p(k)<=q(k)<=end
//2）a[start~p(k)]<=key
//3）a[(q(k)+1)~end]>=key
//4）key=a[start]

//证明：
//由于内层while循环的限制，循环不变式1）显然成立
//第一次迭代时，key = array[start]，p(1)自增或者不变，
//如果p(1)自增，则之后a[start]不会跟任何元素交换，key = array[start]始终成立
//如果p(1)不变，由array[p(2)]=array[p(1)]=array[start]=key,则必有p(2)==q(2)，此时key自身互换，
//第二次迭代while判断时，依然有key = array[start],并且此时循环结束
//循环不变式4）成立
//下面证明2）3）：
//1）第1次迭代，显然有a[start~p(1)]=a[start]<=key，a[(q(k)+1)~end]=Φ>=key
//2）假设第k次迭代开始，有a[start~p(k)]<=key，a[(q(k)+1)~end]>=key
//由p(k)<q(k)，可知第一个while之后有a[q(k+1)] < key，a[start~(q(k+1)-1)]>=key
//第二个while之后，a[start~(p(k+1)-1)]<=key
//交换a[p(k+1)]，a[q(k+1)]之后，可知a[start~p(k+1)]<=key,a[start~(q(k+1)-1)]>=key，即循环不变式2）3）成立

//由循环不变式，可知a[p]<=key，当p<q时，p至少自增1，故一定可以达到p==q使得循环终止
//循环终止时有，a[start~p]<=key，a[(p+1)~end]=a[(q+1)~end]>=key
//此时，交换array[p]和key(array[start])，key划分达成

int partation2(int* array, int start, int end)
{
	int p = start;
	int q = end;
	int key = array[start];
	while (p < q)
	{
		while (p < q && array[q] >= key)
		{
			--q;
		}
		while (p < q && array[p] <= key)
		{
			++p;
		}
		swap(array[p], array[q]);
	}
	//交换时要保证a[start~(p)]<=key
	swap(array[p], array[start]);
	return p;
}


//循环不变式
//1）p(k)<=q(k)
//2）a[p(k)]=key
//3）a[start~(p(k)-1)]<=key
//4）a[(q(k)+1)~end]>=key
//证明:
//1）k=1时，p(1)=start，q(1)=end,a[p(1)]=key,显然有：a[start~(p(1))]<=key,a[(q(1)+1)~end]>=key
//2）假设第k轮迭代有：p(k)<q(k),a[p(k)]=key,a[start~(p(k)-1)]<=key,a[(q(k)+1)~end]>=key
//则第一个while循环结束时，有两种情况，都有a[(q(k+1)+1)~end]>=key：
//a）p(k)<q(k+1)&&a[q(k+1)]<key，此时a[q(k+1)]和a[p(k)]进行交换，有a[q(k+1)]=key
//b）p(k)=q(k+1)&&a[q(k+1)]=key，此时a[q(k+1)]和a[p(k)]进行交换，有a[p(k)]=a[q(k+1)]=key
//即a[q(k+1)]=key，a[(q(k+1)+1)~end]>=key
//进入第二个while循环，第二个while循环结束时，也有两种情况，这两种情况都有a[start~(p(k+1)-1)]<=key：
//aa）p(k+1)<q(k+1)&&a[p(k+1)]>key
//bb）p(k+1)=q(k+1)&&a[p(k+1)]=key
//同理再次交换a[p(k+1)]和a[q(k+1)]后，有a[p(k+1)]=key
//综上第k+1此迭代开始时，有：p(k+1)<=q(k+1),a[p(k+1)]=key，a[start~(p(k+1)-1)]<=key，a[(q(k+1)+1)~end]>=key，循环不变式依然成立

//若第一次while循环没有达到循环终止条件，即进入第二次while时有p<q，a[p]<key，则第二次while循环p一定会执行自增
//即要么在第一次循环q自减达到p>=q，要么在第二次while执行p自增
//即每一次迭代p和q必定有一个增加后减小，可知循环终止条件p>=q一定会达到
//循环结束时有p=q，a[p]=key，a[start~(p-1)]<=key，a[(p+1)~end]=a[(q+1)~end]>=key，即将a[start~end]使用a[p]=key划分成两部分，左侧<=key，右侧>=key
int partation3(int* array, int start, int end)
{
	int p = start;
	int q = end;
	int key = array[p];
	while (p < q)
	{
		//a[p]==key
		while (p < q && array[q] >= key)
		{
			--q;
		}
		swap(array[p], array[q]);
		//此时a[q]==key
		while (p < q && array[p] <= key)
		{
			++p;
		}
		swap(array[p], array[q]);
		//此时a[p]==key
	}
	return p;
}

//快速排序
void quickSort(int a[], int start, int end, long &cntDect, long &cntSwap) {
	if(start<end){
		//由于p∈[start,end)，则1=<p-start+1<end-start+1
		//同理，由于p+1∈(start,end],则1=<end-(p+1)+1<end-start+1
		//即每一轮迭代排序数组的范围在减小，故对于所有的递归分支，一定可以达到start>=end，使得递归结束
		int p = partation(a,start,end,cntDect,cntSwap);
		quickSort(a,start,p,cntDect,cntSwap);
		quickSort(a,p+1,end,cntDect,cntSwap);		
	}	
}

void max_heapify(int a[],int heapsize,int ind,long &cntDect, long &cntSwap){
	int left = 2*ind+1,right=2*ind+2,maxInd = ind;
	if(ind<heapsize){
		cntDect++;
	    if(left<heapsize&&a[left]>a[maxInd]){
	    	maxInd = left; 
		}	
		if(right<heapsize&&a[right]>a[maxInd]){
	    	maxInd = right; 
		}
		if(ind!=maxInd){
			swap(&a[ind],&a[maxInd]);
			cntDect++;
		    max_heapify(a,heapsize,maxInd,cntDect,cntDect);	
		}
		
	}
	
} 

void build_maxheap(int a[],int len,long &cntDect, long &cntSwap){
	for(int i=len/2-1;i>=0;--i){
		max_heapify(a,len,i,cntDect,cntSwap);
	}
} 

void heapSort(int a[],int len,long &cntDect, long &cntSwap){
	build_maxheap(a,len,cntDect,cntSwap);
	while(len>1){
		swap(&a[0],&a[len-1]);
		cntSwap++;
		len--;
		max_heapify(a,len,0,cntDect,cntSwap);
	}
}

//计数排序（100以内的非负整数)
void countSort(int a[], int b[],int start, int end,int c[],int M) {
	for (int i = start; i <= end; ++i) {
		c[a[i]]++;
	}
	for (int i = 1; i <= M; ++i) {
		c[i] += c[i - 1];
	}

	for (int i = end; i >= start; --i) {
		b[c[a[i]]-1]=a[i];
		c[a[i]]--;
	}
}


int maxbit(int data[], int start, int end)
{
	int d = 1; //保存最大的位数
	int p = 10;
	for (int i = start; i <= end; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}

//基数排序
void radixSort(int a[], int b[], int start, int end) {
	int c[BASE] = { 0 };
	int d = maxbits(a,start,end);
	int radix = 1,key;
	for (int i = 0; i < d; ++i) {
		for (int j = 0; j < BASE; ++j) {
			c[j] = 0;
		}
		for (int j = start; j <= end; ++j) {
			key = (a[j] / radix) % 10;
			c[key]++;
		}
		for (int j = 1; j < BASE; ++j) {
			c[j] += c[j - 1];
		}

		for (int j = end; j >= start; --j) {
			key = (a[j] / radix) % 10;
			b[c[key] - 1] = a[j];
			c[key]--;
		}
		for (int j = start; j <= end; ++j) {
			a[j] = b[j];
		}
		radix *= 10;
	}

}

int main() {
	clock_t startTime, endTime;
	double  duration;
	long cntDect = 0, cntSwap = 0;
	int a[9] = { 1,8,7,6,5,4,3,2,1 },b[11],c[MAX+1] = { 0 };
	startTime = clock();

//      bubbleSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      slectSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      insertSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      mergeSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      shellSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      quickSort(a, 0, sizeof(a) / sizeof(int) - 1, cntDect, cntSwap);
//      heapSort(a,sizeof(a) / sizeof(int),cntDect,cntSwap);
//      countSort(a,b, 0, sizeof(a) / sizeof(int) - 1, c,MAX);
//      radixSort(a,b, 0, sizeof(a) / sizeof(int) - 1);
	
	endTime = clock();
	duration = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	printArray(a, 0, sizeof(a) / sizeof(int) - 1);

	printf("%f seconds\n", duration);
	printf("Total detection times: %d\n", cntDect);
	printf("Total swap times: %d\n", cntSwap);
	return 0;
}
