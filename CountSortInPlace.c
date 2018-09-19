#include<stdio.h>
#define MAX 5

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//算法正确性：
//证明while循环中的循环不变量：每次循环开始时，都有[i+1,end]已经放置在正确的位置
//证明如下：
//1)循环开始时i=end,[i+1,end]为空，循环不变量成立。
//2)假设当i<=k时,循环不变量成立，即[k+1,end]区间的元素已经放置在正确的位置。
//则进行循环体处理，分两种情况：
//(a)k<position[a[k]]，即a[k]已经落入正确的区间[position[a[k]-1],position[a[k]]),(注：这里k不可能小于position[a[k]-1],原因是:
//若k<position[a[k]-1],则位置k处应该放置的元素值为a[k]-1,说明[k+1,end]区间内为所有>=a[k]的元素，而a[k]=a[k]显然矛盾。)
//此时有[k,end]区间的元素已经放置在正确的位置。
//(b)k>=position[a[k]]，说明此时k处应该放置a[k]+1,由于[k+1,end]区间的元素已经放置在正确的位置，则在[0,k]区间内定会存在某个元素等于a[k]+1
//此时不断将a[k]与[0,k)中的正确位置进行交换，直至k<position[a[k]]，从而使[k,end]区间的元素放置在正确的位置。
//3）由于每次交换均将一个元素放置在正确的位置，可知循环可以在n-1次遍历后结束，期间最多进行n-1次交换，
//循环结束时i=start,可知[start+1,end]区间内元素放置正确位置，即所有元素均放置在正确位置，问题得解。
//算法复杂度：o(n+MAX)
void countSortInPlaceV1(int a[],int start,int end) {
	int c[MAX+1] = { 0 };
	int position[MAX + 1] = { 0 };
	for (int i = start; i <= end; ++i) {
		c[a[i]]++;
	}
	position[0] = c[0];
	for (int i = 1; i <= MAX; ++i) {
		c[i] += c[i-1];
		position[i] = c[i];
	}
	int i = end,cnt=0;
	while ( i>start ) {
		int key = a[i];
		if (i<position[a[i]]) {
			//当i<position[a[i]]时，将所有值为a[i]的元素放入正确的位置的操作，
			//均是通过交换该区间内值不为a[i]的元素，直到该区间内所有元素均正确放置
			//所以，当i<position[a[i]]时，并不需要对c[a[i]]的值进行调整
			--i;
		}
		else {
			cnt++;
			swap(&a[i], &a[c[a[i]] - 1]);
			c[key]--;
		}

	}
	printf("总共进行%d次交换\n", cnt);
}

//另一个版本，区别是i从头开始遍历
void CountingSortInPlaceV2(int A[], int size) {
	int counts[MAX + 1];
	int positions[MAX + 1];

	for (int i = 0; i <= MAX; i++) {
		counts[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		counts[A[i]]++;
	}

	for (int i = 1; i <= MAX; i++) {
		counts[i] += counts[i - 1];
	}

	for (int i = 0; i <= MAX; i++) {
		positions[i] = counts[i];
	}

	int i = 0;
	while (i < size) {
		int key = A[i];
		bool placed = (positions[key - 1] <= i && i < positions[key]);

		if (placed) {
			i++;
		}
		else {
			swap(&A[i], &A[counts[key] - 1]);
			counts[key]--;
		}
	}
}


int main() {
	int a[] = {  1,3,2,4,3,5,3,1 };
	countSortInPlaceV1(a,0,sizeof(a) / sizeof(int)-1);
	for (int i = 0; i <= sizeof(a) / sizeof(int)-1; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
	return 0;
}
