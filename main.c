#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

int main(void){
	puts("Simple statistics tools,the following functions are contained:");
	puts("write the data in -> r");
	puts("descriptive statistics -> d");
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
				puts("\033[31mNo data wrote in,please check the data file\033[0m");
				continue;
			}
			collect_arr = (struct collection*)malloc(sizeof(struct collection)*row);
			collection_to_arr_assign(head,collect_arr);

			puts("Data have been written in successfully");
		}

		else if(ch[0] == 'd'){
			if(row == 0){
				puts("\033[31mNo data stored,please check the data file,then input \"r\" to write data in\033[0m");
				continue;
			}
			puts("Input the name of the array, input \"a\" to display all");
			gets_all(ch,NAME_LENTH);
			if(strcmp(ch,"a") == 0){
				for(int i = 0;i < row;i++){
					printf("\033[2;7;1m%s\n\033[2;7;0m",collect_arr[i].name);					//输出白底字体
					prt_dscrp(dscrp_statistics(collect_arr[i].data_ptr,collect_arr[i].data_num),collect_arr[i].data_num);
				}	
			}	
			else{
				int i; for(i = 0;i < row;i++)
					strcmp(ch,collect_arr[i].name) == 0?prt_dscrp(dscrp_statistics(collect_arr[i].data_ptr,collect_arr[i].data_num),collect_arr[i].data_num):i++;
				i == row?puts("\033[31mNo such array in data file\033[0m"):1;
			}
			
		}
		else{
			puts("\033[31mInvalid input\033[0m");
		}
	}
	return 0;
}
