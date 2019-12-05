struct chain{												//链表
	float num;
	struct chain* next;
};
struct mode_retrn{											//mode函数返回多值
	float num;
	char ch;
};
struct information{											//统计信息
	float mean_;  								//均值
	float mid_;									//中位数
	float variance_;  							//方差
	float std_variance_;						//标准差
	float qtl_up_;								//上四分位数
	float qtl_low_;								//下四分位数
	float qtl_rg_;								//四分位差
	float cv_;									//离散系数
	float skew_;								//偏态系数
	float kurtosis_; 							//峰态系数
	float range_;								//全距
};
struct collection{											//样本信息
	char name[20];
	float *data_ptr;
	int data_num;
	struct collection* next;
};
//输入与数据结构处理
int gets_all(char* ch);
int readline(struct collection *collection);
void chain_to_arr_assign(struct chain* chain,float* arr);
void collection_to_arr_assign(struct collection* coll,struct collection *arr);
//基本统计函数
void sort(float* arr,int num);
float mean(float* arr,int num);
struct mode_retrn mode(float* arr,int num);
float variance(float* arr,int num,float mean);
float qtl(float* arr,int num,int where);
float skew(float* arr,int num,float mean,float std_dvt);
float kurtosis(float* arr,int num,float mean,float std_dvt);

struct information gnrl_statistics(float *arr,int num);


