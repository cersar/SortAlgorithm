/*
 * main1.c
 *
 * 冒泡变体
 *  Created on: Sep 6, 2016
 *      Author: yangsen
 */

#include<stdio.h>

void bubble(int *array,int num)
{
	int i,j,temp;
	for(i=0;i<num-1;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(array[i]>array[j])
			{
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
			}
		}
	}
}

int main()
{
	int array[]={84, 45, 95,15, 78, 51, 24, 12};
	bubble(array,8);
	int i;
	for(i=0;i<sizeof(array)/sizeof(int);i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
	return 0;
}


