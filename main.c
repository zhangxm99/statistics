#include<stdio.h>
#include<math.h>
#include "functions.h"

int main(void){
	puts("Simple statistics tools,the following functions are contained:");
	puts("general_discribing -> g");
	puts("Type \"quit\" or \"q\"to leave");
	
	char ch[4];
	while(printf(">>>")&&gets_all(ch)&&ch[0] != 'q'){
		if(ch[0] == 'g'){
			struct chain input;
			puts("input the data, ! to end: ");
			int num = arr_input(&input);
			if(num == 0){
				puts("invalid input");
				continue;
			}
			float arr[num];
			assign(&input,arr);						//链表给数组赋值
			sort(arr,num);							//从小到大排序
								
				
			float mean_ = mean(arr,num);  				//均值
			float mid_ = qtl(arr,num,2);					//中位数
			float mode_ = mode(arr,num);					//众数
			float variance_ = variance(arr,num,mean_);  		//方差
			float std_dvt_ = sqrt(variance_);				//标准差
			float qtl_up_ = qtl(arr,num,3);				//上四分位数
			float qtl_low_ = qtl(arr,num,1);				//下四分位数
			float qtl_rg_ = qtl_up_ - qtl_low_;				//四分位差
			float cv_ = std_dvt_/mean_;					//离散系数
			float skew_ = skew(arr,num,mean_,std_dvt_);		//偏态系数
			float kurtosis_ = kurtosis(arr,num,mean_,std_dvt_); 	//峰态系数
			
			printf("cv: %f\nvariance (n-1): %f\nkurtosis: %f\n",cv_,variance_,kurtosis_);
		}
		else{
			puts("invalid input");
		}
	}
	return 0;
}
