
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

//循环不变式:
//1）a[start~p]<=key
//2）a[q~end]>=key
//3）start=<p<q<=end
//循环结束时，p>=q，a[start~q]<=key，a[(q+1)~end]>=key，a[start~(p-1)]<=key，a[p~end]>=key
//1.若key = a[start]，则第一次循环执行完之后一定有p=start，且跳出循环时一定有q∈[start,end)，p∈[start,end]此时应该返回q
//证明q∈[start,end):
	// 1)证明q>=start：注意到，每执行一次swap，意味着将小于等于key的值置于q之前，执行swap的次数>=0,
	//当循环结束时执行swap次数>0时，则循环结束之前，q的前面至少有一个小于key的值，循环结束时必有q>=start;
	//当循环结束时执行swap的次数为0时，说明外层while循环只执行一次，此时p=start=q,q>=start也成立
	//综上，q>=start 
	//2)证明q<end：(反证法)首先，显然q<=end,假设q=end，即外层while循环执行一次便跳出
	//此时p=start&&p>=q,则q=start=end,这与start<end矛盾，故q<end; 
//此时选q作为分割点，原因是结束时q∈[start,end),保证q+1和q不超出[start,end],防止死循环
//2.若key = a[end]，则第一次循环执行完之后一定有q=end，且跳出循环时一定有p∈(start,end]，q∈[start,end]此时应该返回p
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
			return q;
		}
	}
}

//循环不变式（当迭代次数k>1时）：
//1）p(k)<q(k)
//2）a[start~p(k)]<=key
//3）a[q(k)~end]>=key
//循环结束时，均有p==q：
//a）若key=array[q]，且p先自增，q再自减，则循环结束时有a[p]==a[q]>=key，a[start~(p-1)]<=key,a[p~end]==a[q~end]>=key
//此时key和a[p]互换，将原a[p]>=key置于最右侧，将key置于p位置，互换之后有a[start~(p-1)]<=key，a[(p+1)~end]>=key，a[p]=key，达成区域的划分目标
//证明：
//1)当循环结束时的迭代次数k>1时，循环开始时有a[p(k)]<=key,a[q(k)]>=key,p(k)<right(k)，则跳出第一个while循环时，要么由于p(k+1)=q(k),要么array[p(k+1)]>key
//由于p(k+1)=q(k)时，array[p(k+1)]=array[q(k)]>=key，综上，跳出第一个while循环时都有array[p(k+1)]>=key，而跳出第二个while循环时有p(k+1)==q(k+1),故循环
//结束时有a[p]==a[q]>=key
//2）当循环结束时迭代次数k=1时，循环开始时有a[q(1)]=key,p(1)<q(1),则跳出第一个while循环时，要么由于p(2)=q(1),要么array[p(2)]>key,即array[p(2)]>=key
//而跳出第二个while循环时有p(2)==q(2),故循环结束时有a[p]==a[q]>=key
//b）若key=array[p]，且q先自减，p再自增，则循环结束时有a[p]==a[q]<=key(证明同上)，a[start~(q+1)]>=key,a[(q+1)~end]==a[(p+1)~end]>=key
//此时key和a[q]互换，将原a[q]<=key置于最左侧，将key置于q位置，互换之后有a[start~(q-1)]<=key，a[(q+1)~end]>=key，a[q]=key，达成区域的划分目标

//1.key=array[p]，且p先自增，q再自减。
//不能使用,原因：
//1）当循环结束时的迭代次数k>1时，a[p]==a[q]>=key
//2）当循环结束时迭代次数k=1时，a[p]>=key和a[p]<=key(key之后的所有元素都小于等于key)都有可能出现
//2.key=array[q]，且q先自减，p再自增
//原因同上
int partation2(int* array, int start, int end)
{
	int p = start;
	int q = end;
	int key = array[end];
	while (p < q)
	{
		while (p < q && array[p] <= key)
		{
			++p;
		}
		while (p < q && array[q] >= key)
		{
			--q;
		}
		swap(array[p], array[q]);
	}
	swap(array[p], array[end]);
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
