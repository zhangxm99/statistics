#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "functions.h"

int main(void){
	puts("Simple statistics tools,the following functions are contained:");
	puts("\033[32mwrite the data in -> r\033[0m");
	puts("\033[32mdescriptive statistics -> d\033[0m");
	puts("\033[32mparameter estimation -> p\033[0m");
	puts("\033[32mcontingency table -> c\033[0m");
	puts("Type \"q\" to leave");
	
	char ch[NAME_LENTH];
	int row = 0;
	while(printf(">>>")&&gets_all(ch,NAME_LENTH)){
		struct collection *collect_arr;

		if(ch[0] == 'r'){
			struct collection *collect = (struct collection*)malloc(sizeof(struct collection));
			struct collection *head = collect;
			row = readline(collect);
			if(row == 0){
				puts("\033[31mNo data wrote in, please check the data file\033[0m");
				continue;
			}
			collect_arr = (struct collection*)malloc(sizeof(struct collection)*row);
			collection_to_arr_assign(head,collect_arr);

			puts("Data have been written in successfully");
		}

		else if(ch[0] == 'd'){
			if(row == 0){
				puts("\033[31mNo data stored, please check the data file,then input \"r\" to write data in\033[0m");
				continue;
			}
			printf("Input the name of the array, input \"a\" to display all\n>");
			gets_all(ch,NAME_LENTH);
			if(strcmp(ch,"a") == 0){
				for(int i = 0;i < row;i++){
					printf("\033[2;7;1m%s\n\033[2;7;0m",collect_arr[i].name);					//输出白底字体
					dscrp_statistics(collect_arr[i].data_ptr,collect_arr[i].data_num);
				}	
			}	
			else{
				int i;
				if((i = search_name(ch,collect_arr,row)) != -1)
					dscrp_statistics(collect_arr[i].data_ptr,collect_arr[i].data_num);
				else puts("\033[31mNo such array in data file\033[0m");
			}
			
		}
		else if(ch[0] == 'p'){
			if(row == 0){
				puts("\033[31mNo data stored, please check the data file,then input \"r\" to write data in\033[0m");
				continue;
			}
			printf("single(s) or double(d)\n>");
			gets_all(ch,NAME_LENTH);
			if(ch[0] == 's'){
				printf("Input the name of the array\n>");
				gets_all(ch,NAME_LENTH);
				
				int position;
				if((position=search_name(ch,collect_arr,row)) != -1){
					printf("Input the alpha level(0.1 or 0.05 or 0.01)\n>");
					float alpha; scanf("%f",&alpha);while(getchar() != '\n') continue;
					if(alpha!=0.1&&alpha!=0.05&&alpha!=0.01&&collect_arr[position].data_num == 1){
						puts("\033[31mSorry,only support 0.1,0.05,0.01 alpha level ,and the number should be at least 2\033[0m");continue;
					}
					printf("\033[2;7;1m%s\n\033[2;7;0m",collect_arr[position].name);
					single_esti(collect_arr[position],alpha);
				}
				else puts("\033[31mNo such array in data file\033[0m");
			}
			else if(ch[0] == 'd'){
				printf("Input the name of the first array\n>");
				gets_all(ch,NAME_LENTH);
				int position1 = search_name(ch,collect_arr,row);
				printf("Input the name of the second array\n>");
				gets_all(ch,NAME_LENTH);
				int position2 = search_name(ch,collect_arr,row);
				if(position1 != -1&&position2 != -1){
					printf("independent(i) or matched(m)\n>");
					gets_all(ch,NAME_LENTH);
					if(ch[0] == 'i'){
						printf("Input the alpha level(0.1 or 0.05 or 0.01)\n>");
						float alpha; scanf("%f",&alpha);while(getchar() != '\n') continue;
						int num1 = collect_arr[position1].data_num;
						int num2 = collect_arr[position2].data_num;
						float mean1 = mean(collect_arr[position1].data_ptr,num1);
						float mean2 = mean(collect_arr[position2].data_ptr,num2);
						float variance1 = variance(collect_arr[position1].data_ptr,num1,mean1);
						float variance2 = variance(collect_arr[position2].data_ptr,num2,mean2);
						float m_rg;
						if(num1 >= 30&&num2 >= 30){
							m_rg = z(alpha)*sqrt(variance1/num1+variance2/num2);
						}
						else{
							printf("population's variance equal(y) or not(n)n>");
							gets_all(ch,NAME_LENTH);
							if(ch[0] == 'y'){
								float sp2 = ((num1-1)*variance1+(num2-1)*variance2)/(num1+num2-2);
								m_rg = t(alpha,num1+num2-2)*sqrt(sp2*(1/num1+2/num2));
							}
							else if(ch[0] == 'n'){
								float some1 = variance1/num1;
								float some2 = variance2/num2;
								float v1 = (some1+some2)*(some1+some2);
								float v2 = some1*some1/(num1-1) + some2*some2/(num2-1);
								float v = v1/v2;
								m_rg = t(alpha,(int)v+1)*sqrt(variance1/num1+variance2/num2);
							}
							else puts("\033[31mInvalid input\033[0m");
						}
						printf("\033[2;7;1m%s||%s\n\033[2;7;0m",collect_arr[position1].name,collect_arr[position2].name);
						printf("Mean confidence Interval: (%f,%f)\n",mean1-mean2-m_rg,mean1-mean2+m_rg);
							/********************方差，要处理F表的问题***************/
					}
					else if(ch[0] == 'm'){
						if(collect_arr[position1].data_num != collect_arr[position2].data_num){
							puts("\033[31mThey don't have same numbers, please check the data file\033[0m");
							continue;
						}
						else{
							printf("Input the alpha level(0.1 or 0.05 or 0.01)\n>");
							float alpha; scanf("%f",&alpha);while(getchar() != '\n') continue;
							float arr_diff[collect_arr[position1].data_num];
							for(int i = 0;i < collect_arr[position1].data_num;i++){
								arr_diff[i] = collect_arr[position1].data_ptr[i] - collect_arr[position2].data_ptr[i];
							}
							struct collection new = collect_arr[position1];
							new.data_ptr = arr_diff;
							printf("\033[2;7;1m%s<->%s\n\033[2;7;0m",collect_arr[position1].name,collect_arr[position2].name);
							single_esti(new,alpha);
						}
					}
					else puts("\033[31mInvalid input\033[0m");
				}
				else puts("\033[31mNo such array in data file\033[0m");
			}
			else puts("\033[31mInvalid input\033[0m");
		}
		else if(ch[0] == 'c'){

		}
		else puts("\033[31mInvalid input\033[0m");
	}
	return 0;
}
