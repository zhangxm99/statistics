#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

//输入整句
int gets_all(char* ch){
	scanf("%c",ch + i);
	while(getchar() != '\n')
		continue;
	return 1;
}
//链表输入
int arr_input(struct chain* chain){
	int i = 0;
	while(scanf("%f",&chain->num) == 1){
		i++;
		struct chain* ptr = (struct chain*)malloc(sizeof(struct chain));
		chain->next = ptr;
		ptr->next = NULL;
		chain = ptr;
	}
	getchar();
	getchar();
	return i;
}

//链表给数组赋值
void assign(struct chain* chain,float* arr){
	for(int i = 0;chain->next != NULL;i++){
		arr[i] = chain->num;
		chain = chain->next;
	}
}

//数组冒泡排序
void sort(float* arr,int num){
	for(int x = 0;x < num - 1;x++){
		for(int i = 0;i < num - 1 - x;i++){
			float p;arr[i] > arr[i+1]?(p = arr[i],arr[i]=arr[i+1],arr[i+1]=p):1;
		}
	}
}

//平均数
float mean(float* arr,int num){float sum = 0; for(int i = 0;i < num;i++) sum += arr[i]; return sum/num;}

//众数*****可用 待改进
float mode(float* arr,int num){
	int store[num]; for(int i = 0;i < num;i++) store[i] = 1;
	int p = 0; for(int i = 0;i < num;i++) arr[i] == arr[i+1]?store[p]++:p++;
	int q = 0; for(int i;i < num - 1;i++) store[q] > store[i+1]? :(q = i + 1);
	return arr[q];
}

//方差
float variance(float* arr,int num,float mean){
	float sum = 0; 
	for(int i = 0;i < num;i++) sum += (arr[i]-mean)*(arr[i]-mean);
	return sum/(num - 1);
}

//四分位数
float qtl(float* arr,int num,int where){
	float dot = where*(num + 1.0)/4.0;
	float pst = (float)dot - (int)dot;
	return arr[(int)dot - 1]*(1-pst) + arr[(int)dot]*pst;
}

//偏态系数
float skew(float* arr,int num,float mean,float std_dvt){
	float sum = 0;
	for(int i = 0;i < num;i++){
		float p = (arr[i] - mean);
		sum += p*p*p;
	}
	return num*sum/((num - 1)*(num - 2)*std_dvt*std_dvt);
}

//峰态系数
float kurtosis(float* arr,int num,float mean,float std_dvt){
	float sum1,sum2 = 0;
	float std4 = std_dvt*std_dvt*std_dvt*std_dvt*std_dvt;
	for(int i = 0;i < num;i++){
		float p = arr[i] - mean;
		p = p*p;
		sum1 += p*p; sum2 += p;
	}
	return (num*(num + 1)*sum1 - 3*sum2*sum2*(num - 1)) / (num - 1)*(num - 2)*(num - 3)*std4;
}
