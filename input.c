#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"

//输入命令
int gets_all(char* ch,int size){
	int i = -1;
	do{
		i++;
		scanf("%c",&ch[i]);
	}while(i < size&&ch[i] != '\n');
	if(ch[0] == 'q') return 0;
	else if(ch[i] == '\n') ch[i] = '\0';
	else while(getchar() != '\n') continue;

	return 1;
}

//按行输入
int readrow(struct collection *head){
	struct collection *collection = head;
	FILE *fp = fopen("data","r");
	int row = 0;
	for(int trash;fscanf(fp,"%d",&trash) != EOF;){
		if((trash = fgetc(fp)) == '/'){while(fgetc(fp) != '\n') continue;}  //如果行开头为“/”，这一行就是注释
		else ungetc(trash,fp);

		int i;
		for(i = 0;((collection->name)[i]=fgetc(fp)) != ':'&&i < 20;i++){
			if((collection->name)[i] == EOF){
				fclose(fp);
				return row;
			}
			else continue;
		}
		(collection->name)[i] = '\0';

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
	fclose(fp);
	return row;
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
		free(tmp);							//释放链表
	}
}
int search_name(char *ch,struct collection *collect_arr,int row){
	for(int i = 0;i < row;i++)
		if(strcmp(ch,collect_arr[i].name) == 0) return i;
	return -1;
}