#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

//输入命令
int gets_all(char* ch){
	scanf("%c",ch);
	while(getchar() != '\n')
		continue;
	return 1;
}

//按行输入
int readline(struct collection *collection){
	FILE *fp = fopen("data","r");
	int row = 0;
	for(int trash;fscanf(fp,"%d",&trash) != EOF;){
		int i;
		for(i = 0;((collection->name)[i]=fgetc(fp)) != ':'&&i < 20;i++){
			if((collection->name)[i] == EOF){
				fclose(fp);
				return row;
			}
			else{
				continue;
			}
		}
		(collection->name)[i+1] = '\0';

		struct chain *chain = (struct chain*)malloc(sizeof(struct chain));
		struct chain *head = chain;

		int num = 0;
		while(fscanf(fp,"%f",&chain->num) == 1){
			num++;
			struct chain* ptr = (struct chain*)malloc(sizeof(struct chain));
			chain->next = ptr;
			ptr->next = NULL;
			chain = ptr;
		}
		while(fgetc(fp) != '\n')
			continue;
		collection->data_num = num;
		
		float *arr = (float*)malloc(sizeof(float)*num);
		chain_to_arr_assign(head,arr);
		collection->data_ptr = arr;

		struct collection *ptr = malloc(sizeof(struct collection));
		ptr->next = NULL;
		collection->next = ptr;
		collection = ptr;
		row++;
	}
}

//链表给数组赋样本值
void chain_to_arr_assign(struct chain* chain,float* arr){
	for(int i = 0;chain->next != NULL;i++){
		arr[i] = chain->num;
		struct chain* tmp = chain;
		chain = chain->next;
		free(tmp);							//释放链表
	}
}

//链表给数组赋值
void collection_to_arr_assign(struct collection* coll,struct collection *arr){
	for(int i = 0;coll->next != NULL;i++){
		arr[i] = *coll;
		struct collection *tmp = coll;
		coll = coll->next;
		free(tmp);
	}
}