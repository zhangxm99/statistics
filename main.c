#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

int main(void){
	puts("Simple statistics tools,the following functions are contained:");
	puts("general_discribing -> g");
	puts("Type \"q\" to leave");
	
	char ch;
	while(printf(">>>")&&gets_all(&ch)&&ch != 'q'){
		struct collection *collect_arr;
		if(ch == 'r'){
			struct collection *collect = (struct collection*)malloc(sizeof(struct collection));
			struct collection *head = collect;
			int row = readline(collect);
			if(row == 0){
				puts("no data wrote in");
				continue;
			}
			collect_arr = (struct collection*)malloc(sizeof(struct collection)*row);
			collection_to_arr_assign(head,collect_arr);

			puts("datas have been written in successfully");
			printf("%f\n",gnrl_statistics(collect_arr[0].data_ptr,collect_arr[0].data_num).skew_);
		}
		else{
			puts("invalid input");
		}
	}
	return 0;
}
