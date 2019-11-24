struct chain{
	float num;
	struct chain* next;
};

int gets_all(char* ch);
int arr_input(struct chain* chain);
void assign(struct chain* chain,float* arr);
void sort(float* arr,int num);
float mean(float* arr,int num);
float mode(float* arr,int num);
float variance(float* arr,int num,float mean);
float qtl(float* arr,int num,int where);
float skew(float* arr,int num,float mean,float std_dvt);
float kurtosis(float* arr,int num,float mean,float std_dvt);

