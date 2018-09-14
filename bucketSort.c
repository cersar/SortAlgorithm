#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	double val;
	Node *next = NULL;
}Node,* List;

void printList(const Node *p) {
	while (p != NULL) {
		printf("%.2f\t", p->val);
		p = p->next;
	}
	printf("\n");
}

void listAdd(List *l,double val) {
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->val = val;
	newNode->next = NULL;
	if (*l == NULL) {
		*l = newNode;
	}
	else {
		Node *p = *l;
		p->next = newNode;
	}
}

void makeList(List *l, double a[], int n) {
	Node *p;
	for (int i = 0; i < n; ++i) {
		Node * newNode = (Node*)malloc(sizeof(Node));
		newNode->val = a[i];
		newNode->next = NULL;

		if (*l == NULL) {
			*l = newNode;
			p = *l;
		}
		else {
			p->next = newNode;
			p = p->next;
		}
	}
}

void freeList(List *l) {
	Node *p = *l,*tmp;
	while (p!=NULL) {
		tmp = p->next;
		free(p);
		p = tmp;
	}
	*l = NULL;
}

void insertSortForList(List *l) {
	Node* p = *l, *q = *l,*pPre=NULL,*qPre=NULL,*tmp=NULL;
	while (p != NULL) {
		//当p->val<q->val时,将q向后移动
		while (p->val > q->val) {
			qPre = q;
			q = q->next;
		}
		
		if (q != p) {
			//删除p
			pPre->next = p->next;
			//tmp储存待插入的元素
			tmp = p;
			//p位置后移
			p = p->next;
			//将tmp插入到q之前
			if (qPre == NULL) {
				//插入到链表头
				*l = tmp;
			}
			else {
				//插入到qPre之后
				qPre->next = tmp;
			}
			tmp->next = q;
		}
		else {
			//当p及p之前的元素均有序时，pPre直接取原来p的位置（存在元素插入时pPre位置不变），并将p直接后移
			pPre = p;
			p = p->next;
		}
		//q置位链表头
		q = *l;
		qPre = NULL;
	}
}

void bucketSort(double a[], int start, int end) {
	int N = end - start + 1;
	if (N > 0) {
		List *b = (List *)malloc(sizeof(List)*N);
		Node *p;
		for (int i = 0; i < N; ++i) {
			b[i] = NULL;
		}

		for (int i = start; i <=end; ++i) {
			listAdd(&b[int(a[i]*N)],a[i]);
		}

		int i = 0;
		for (int j = 0; i<N&&j < N;++j) {
			insertSortForList(&b[j]);
			p = b[j];
			while (p != NULL) {
				a[i] = p->val;
				i++;
				p = p->next;
			}
		}

		for (int i = 0; i < N; ++i) {
			freeList(&b[i]);
		}
		free(b);
		b = NULL;
	}
}

int main() {
	double a[] = { 0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42 };
	bucketSort(a, 0, sizeof(a) / sizeof(double) - 1);
	for (int i = 0; i < sizeof(a) / sizeof(double); ++i) {
		printf("%f\t", a[i]);
	}
	printf("\n");
	return 0;

}
