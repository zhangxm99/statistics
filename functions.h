#define NAME_LENTH 20
struct chain{												//链表
	float num;
	struct chain* next;
};
struct mode_retrn{											//mode函数返回多值
	float num;
	char ch;
};
struct collection{											//样本信息
	char name[NAME_LENTH];
	float *data_ptr;
	int data_num;
	struct collection* next;
};
//输入与数据结构处理
int gets_all(char* ch,int size);
int readline(struct collection *collection);
void chain_to_arr_assign(struct chain* chain,float* arr);
void collection_to_arr_assign(struct collection* coll,struct collection *arr);
int search_name(char *ch,struct collection *collect_arr,int row);
//基本统计函数
void sort(float* arr,int num);
float mean(float* arr,int num);
struct mode_retrn mode(float* arr,int num);
float variance(float* arr,int num,float mean);
float qtl(float* arr,int num,int where);
float skew(float* arr,int num,float mean,float std_dvt);
float kurtosis(float* arr,int num,float mean,float std_dvt);

void dscrp_statistics(float *arr,int num);
//参数估计
float z(float alpha);
float t(float alpha,int df);
float chi_sqrt(float alpha,int df);
void single_esti(struct collection collect_arr,float alpha);



