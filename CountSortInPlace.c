#include<stdio.h>
#define MAX 4

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
//(a)k<b[a[k]]，即a[k]已经落入正确的区间[b[a[k]-1],b[a[k]]),(注：这里k不可能小于b[a[k]-1],原因是:
//若k<b[a[k]-1],则位置k处应该放置的元素值为a[k]-1,说明[k+1,end]区间内为所有>=a[k]的元素，而a[k]=a[k]显然矛盾。)
//此时有[k,end]区间的元素已经放置在正确的位置。
//(b)k>=b[a[k]]，说明此时k处应该放置a[k]+1,由于[k+1,end]区间的元素已经放置在正确的位置，则在[0,k]区间内定会存在某个元素等于a[k]+1
//此时不断将a[k]与[0,k)中的正确位置进行交换，不存在重复交换的情况下（对c[key]的自减避免了重复交换），
//最多交换k-1次，便可将a[k]+1放置在正确的位置，从而使[k,end]区间的元素放置在正确的位置。
//3）由于不存在重复的交换，且每次交换均将一个元素放置在正确的位置，可知循环可以在n-1次遍历后结束，期间最多进行n-1次交换，
//循环结束时i=start,可知[start+1,end]区间内元素放置正确位置，即所有元素均放置在正确位置，问题得解。
//算法复杂度：o(n+MAX)
void countSort(int a[],int start,int end) {
	int c[MAX+1] = { 0 };
	int b[MAX + 1] = { 0 };
	for (int i = start; i <= end; ++i) {
		c[a[i]]++;
	}
	b[0] = c[0];
	for (int i = 1; i <= MAX; ++i) {
		c[i] += c[i-1];
		b[i] = c[i];
	}
	int i = end,cnt=0;
	while ( i>start ) {
		int key = a[i];
		if (i<b[a[i]]) {
			--i;
			//这里c[key]不应该自减，防止同一个位置进行两次自减操作
			//（有可能交换进行一次自减，再次遍历时进行一次自减）
			c[key]=i+1;
		}
		else {
			cnt++;
			swap(&a[i], &a[c[a[i]] - 1]);
			c[key]--;
		}

	}
	printf("总共进行%d次交换\n", cnt);
}



int main() {
	int a[] = { 3,2,1,2,1,0,4,0,2 };
	countSort(a, 0, sizeof(a) / sizeof(int)-1);
	for (int i = 0; i <= sizeof(a) / sizeof(int)-1; ++i) {
		printf("%d\t", a[i]);
	}
	printf("\n");
	return 0;
}
