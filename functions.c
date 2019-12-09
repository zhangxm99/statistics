#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include<math.h>

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
struct mode_retrn mode(float* arr,int num){
	struct mode_retrn indicate;
	indicate.num = 1;
	int store[num]; for(int i = 0;i < num;i++) store[i] = 1;
	int p = 0; for(int i = 0;i < num - 1;i++) arr[i] == arr[i+1]?store[p]++:(p = i+1);
	int q = 0; for(int i = 0;i < num - 1;i++) store[q] > store[i+1]? :(q = i + 1);
	if(store[q] != 1){
		indicate.num = arr[q];
		indicate.ch = 'Y';
		return indicate;
	}
	else{
		indicate.ch = 'N';
		return indicate;
	}
	
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
	return (num*(num + 1)*sum1 - 3*sum2*sum2*(num - 1)) / ((num - 1)*(num - 2)*(num - 3)*std4);
}

//描述统计
void dscrp_statistics(float *arr,int num){										
	sort(arr,num);															//从小到大排序
	
	struct mode_retrn mode_ = mode(arr,num);								//众数
	float mean_ = mean(arr,num);  											//均值
	float variance_ = variance(arr,num,mean_);  							//方差
	float std_variance_ = sqrt(variance_);									//标准差
	float qtl_up_ = qtl(arr,num,3);											//上四分位数
	float qtl_low_ = qtl(arr,num,1);										//下四分位数

	printf("\033[33mTotal number:\033[0m %d\n",num);
	if(mode_.ch != 'N')	printf("\033[33mMode:\033[0m %f\n",mode_.num);
	else printf("\033[33mMode:\033[0m None\n");
	printf("\033[33mMean:\033[0m %f\n",mean_);
	printf("\033[33mMidian:\033[0m %f\n",qtl(arr,num,2));
	printf("\033[33mVariance:\033[0m %f\n",variance_);
	printf("\033[33mStandart Variance:\033[0m %f\n",std_variance_);
	printf("\033[33mUpper Quartile:\033[0m %f\n",qtl_up_);
	printf("\033[33mLower Quartile:\033[0m %f\n",qtl_low_);
	printf("\033[33mQuartile Deviation:\033[0m %f\n",qtl_up_-qtl_low_);
	printf("\033[33mCoefficient of Dispersion:\033[0m %f\n",std_variance_/mean_);
	printf("\033[33mSkew:\033[0m %f\n",skew(arr,num,mean_,std_variance_));
	printf("\033[33mKurtosis:\033[0m %f\n",kurtosis(arr,num,mean_,std_variance_));
	printf("\033[33mRange:\033[0m %f\n",arr[num - 1] - arr[0]);
}

//z分数双尾
float z(float alpha){
	if(alpha == 0.1) return 1.64;
	else if(alpha == 0.05) return 1.96;
	else if(alpha == 0.01) return 2.58;
	return -1;
}
//t分数双尾
float t(float alpha,int df){
	float t[3][30] = {{6.314,2.92,2.353,2.132,2.015,1.943,1.895,1.86,1.833,1.812,1.796,1.782,1.771,1.761,1.753,1.746,1.74,1.734,1.729,1.725,1.721,1.717,1.714,1.711,1.708,1.706,1.703,1.701,1.699,1.697},
					{12.706,4.303,3.182,2.776,2.571,2.447,2.365,2.306,2.262,2.228,2.201,2.179,2.16,2.145,2.131,2.12,2.11,2.101,2.093,2.086,2.08,2.074,2.069,2.064,2.06,2.056,2.052,2.048,2.045,2.042},
					{63.657,9.925,5.841,4.604,4.032,3.707,3.499,3.355,3.25,3.169,3.106,3.055,3.012,2.977,2.947,2.921,2.898,2.878,2.861,2.845,2.831,2.819,2.807,2.797,2.787,2.779,2.771,2.763,2.756,2.75}};
	if(alpha/2.0f == 0.05f) if(df > 30) return t[0][29]; return t[0][df-1];
	if(alpha/2.0f == 0.025f) if(df > 30) return t[1][29]; return t[1][df-1];
	if(alpha/2.0f == 0.005f) if(df > 30) return t[2][29]; return t[2][df-1];
	return -1;
}
//Chi-sqrt双尾
float chi_sqrt(float alpha,int df){
	float chi[6][30] = {{3.84,5.99,7.81,9.49,11.07,12.59,14.07,15.51,16.92,18.31,19.68,21.03,22.36,23.68,25,26.3,27.59,28.87,30.14,31.41,32.67,33.92,35.17,36.42,37.65,38.89,40.11,41.34,42.56,43.77},
						{5.02,7.38,9.35,11.14,12.83,14.45,16.01,17.53,19.02,20.48,21.92,23.34,24.74,26.12,27.49,28.85,30.19,31.53,32.85,34.17,35.48,36.78,38.08,39.36,40.65,41.92,43.19,44.46,45.72,46.98},
						{7.88,10.6,12.84,14.86,16.75,18.55,20.28,21.96,23.59,25.19,26.76,28.3,29.82,31.32,32.8,34.27,35.72,37.16,38.58,40,41.4,42.8,44.18,45.56,46.93,48.29,49.64,50.99,52.34,53.67},
						{0.001,0.1,0.35,0.71,1.15,1.64,2.17,2.73,3.33,3.94,4.57,5.23,5.89,6.57,7.26,7.96,8.67,9.39,10.12,10.85,11.59,12.34,13.09,13.85,14.61,15.38,16.15,16.93,17.71,18.49},
						{0.005,0.02,0.22,0.48,0.83,1.24,1.69,2.18,2.7,3.25,3.82,4.4,5.01,5.63,6.27,6.91,7.56,8.23,8.91,9.59,10.28,10.98,11.69,12.4,13.12,13.84,14.57,15.31,16.05,16.79},
						{0.005,0.01,0.07,0.21,0.41,0.68,0.99,1.34,1.73,2.16,2.6,3.07,3.57,4.07,4.6,5.14,5.7,6.26,6.84,7.43,8.03,8.64,9.26,9.89,10.52,11.16,11.81,12.46,13.12,13.79}};

	if(alpha/2.0f == 0.05f) return chi[0][df-1];
	if(alpha/2.0f == 0.025f) return chi[1][df-1];
	if(alpha/2.0f == 0.005f) return chi[2][df-1];
	if(alpha/2.0f == 0.95f) return chi[3][df-1];
	if(alpha/2.0f == 0.975f) return chi[4][df-1];
	if(alpha/2.0f == 0.995f) return chi[5][df-1];
	
	return -1;	
}
void single_esti(struct collection collect_arr,float alpha){
	float num = collect_arr.data_num;
	float mean_ = mean(collect_arr.data_ptr,num);
	float variance_ = variance(collect_arr.data_ptr,num,mean_);
						
	float m_rg;
	if(num >= 30) m_rg = z(alpha)*sqrt(variance_/num);
	else m_rg = t(alpha,num - 1)*sqrt(variance_/num);

	printf("Mean confidence Interval: (%f,%f)\n",mean_ - m_rg,mean_ + m_rg);
	printf("Variance confidence Interval: (%f,%f)\n",((num-1)*variance_)/chi_sqrt(alpha,num),((num-1)*variance_)/chi_sqrt(1-alpha,num));

}