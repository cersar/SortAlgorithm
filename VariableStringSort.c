//《算法导论》 8-3-b
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 10

int getIndex(char s) {
		if (s < 'a') {
			return s - 'A';
		}
		else {
			return s - 'a';
		}
}

void countSortByLength(char **str, int start, int end, int group[]) {
	if (start <= end) {
		if (start <= end) {
			char **tmp = (char **)malloc(sizeof(char *)*(end - start + 1));
			int c[MAX_LEN+1] = { 0 };
			for (int i = start; i <= end; ++i) {
				c[strlen(str[i])]++;
			}
			for (int i = 1; i <= MAX_LEN; ++i) {
				c[i] += c[i - 1];
				group[i] = c[i];
			}
			group[0] = c[0];
			int j;
			for (int i = end; i >= start; --i) {
				j = strlen(str[i]);
				tmp[c[j] - 1] = str[i];
				c[j]--;
			}
			for (int i = start; i <= end; ++i) {
				str[i] = tmp[i - start];
			}
			free(tmp);
		}
	}
}

void countSort(char **str,int start,int end,int ind){
	if (start <= end) {
		char **tmp = (char **)malloc(sizeof(char *)*(end - start + 1));
		int c[26] = { 0 };
		for (int i = start; i <= end; ++i) {
			c[getIndex(str[i][ind])]++;
		}
		for (int i = 1; i < 26; ++i) {
			c[i] += c[i - 1];
		}
		int j;
		for (int i = end; i >= start; --i) {
			j = getIndex(str[i][ind]);
			tmp[c[j] - 1] = str[i];
			c[j]--;
		}
		for (int i = start; i <= end; ++i) {
			str[i] = tmp[i - start];
		}
		free(tmp);
	}
}

void main() {
	char* str[] = { "abc","d","ef","a" };
	int len = sizeof(str) / sizeof(char*);
	int group[MAX_LEN + 1] = {0};

	//首先以字符串的长度排序(两个作用：1、分组；2、保证了相同前缀的字符串，短的排在前面)，短的在前，长的在后,o(n)
	countSortByLength(str, 0, len - 1, group);
	//o(n*MAX_LEN)
	for (int i = MAX_LEN; i > 0; --i) {
		//对于长度>=i的字符串，执行位置为i-1的计数排序，时间复杂度o(n-group[i-1])
		countSort(str, group[i-1], len - 1, i-1);
	}

	for (int i = 0; i < len; ++i) {
		printf("%s\n", str[i]);
	}
}
