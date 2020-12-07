#include <string.h>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
#include<algorithm>b
#include <cstdlib> 
#include <ctime> 
using namespace std;
struct node{  //存取每个节点的信息 
	int a[1024];//邻域值 
	int sumNumber;//邻域个数 
};
struct node2{
	int a[9];
	int conflict_num;
};
struct node3{ //用来计算冲突数 
	vector<int> v;
	int color;
};
struct node k[1024];
struct node2 res[1024];

void readData(){ //读取邻域，从0开始存起 
	FILE *fp = fopen("data_9.txt", "r");
    char buf[10000];
    int num=0;
    while(fgets(buf, 10000, fp))
    {
    	int num2=0;
        char *p = strtok(buf, " ");
	    int res = 0;
	    while(p)
	    {
	        
	        k[num].a[num2++]=atoi(p)-1;
	        res++;
	        p = strtok(NULL, " ");
	        
	    }
//	    cout<<num<<":";
//	    for(int i=0;i<num2;i++){
//	    	cout<<k[num].a[i]<<" ";
//		}
		k[num].sumNumber=num2;
	//	cout<<"sumNum:"<<k[num].sumNumber<<endl;
		num++;
    }

}
void initData(){ //初始化十个种群的数据 
	unsigned seed;
	seed = time(0);
    srand(seed);
    for(int i=0;i<10;i++){
    	for(int j=0;j<9;j++){
    		res[i].a[j]=rand()%3;
		}
	}
} 
int conflict_num(int a1[]){//计算每个种子的冲突数 
	vector<int>::iterator it,it2; 
	int conNum=0;
	struct node3 con[1024]; 
	for(int i=0;i<9;i++){
		int s=a1[i];
		(con[s].v).push_back(i);
	}
	for(int i=0;i<3;i++){
		for(it=(con[i].v).begin();it!=(con[i].v).end();it++){
			for(it2=it+1;it2!=(con[i].v).end();it2++){
				for(int j=0;j<k[*it].sumNumber;j++){
					if(*it2==(k[*it].a[j])){
						conNum++;
						//cout<<*it<<"<->"<<*it2<<endl;
					} 
				}
			}
		}
	}
	return conNum;
}
bool  cmp(const node2 &x, const node2 &y)
{
	return x.conflict_num<y.conflict_num;//从小到大排冲突数 
}
bool printColor(){
	int number=1;
	while(1){
		cout<<"第"<<number++<<"次:"<<endl; 
		for(int i=0;i<10;i++){
			int num=conflict_num(res[i].a);
			for(int j=0;j<9;j++) cout<<res[i].a[j]<<" ";
			cout<<endl;					    
		    res[i].conflict_num=num;
		    cout<<"conflict_num: "<<num<<endl;
		    if(num==0) return true;
		}
		int b[10][10];
		sort(res,res+10,cmp);//选择冲突数最小的前五个 
		for(int i=0;i<5;i++){
			for(int j=0;j<9;j++){
				b[i][j]=res[i].a[j];
			}
		}
		int x_num=0;
		unsigned seed;
	    seed = time(0);
        srand(seed);
		while (x_num<2){//交叉产生结果 
			
            int x1,x2;
            int x_min,x_max;
            int d1[10]={0},d2[10]={0};
            x1=rand()%10;
            x2=rand()%10;
            x_min=rand()%9;
            x_max=rand()%9;
//            cout<<x1<<endl<<x2<<endl<<x_min<<endl<<x_max<<endl;
            if(x_min>x_max){
            	int temp=x_min;
            	x_min=x_max;
            	x_max=temp;
			}
			memcpy(d1, res[x1].a, sizeof(res[x1].a));
			memcpy(d2, res[x2].a, sizeof(res[x2].a));
			for(int i=x_min;i<=x_max;i++){
				int temp2=d1[i];
				d1[i]=d2[i];
				d2[i]=temp2;
			}
			
			for(int j=0;j<9;j++){
				b[5+2*x_num][j]=d1[j];
				b[5+2*x_num+1][j]=d2[j];
		}
		x_num++;
		}
		
		//变异 
		int d3[10]={0};
		int d3_num=rand()%10;//改变的种群号 
		int d3_loc=rand()%9;//改变种群的位置 
		int d3_cN=rand()%3; //变色
		res[d3_num].a[9] =d3_cN;
		memcpy(b[9], res[d3_num].a, sizeof(res[d3_num].a));
		
		for(int i=0;i<10;i++){
			for(int j=0;j<9;j++){
				res[i].a[j]=b[i][j];
			}
			//cout<<endl;
		}
		
	}
	return true;
	
}   
int main(){
	readData();
	initData();
	printColor();
	return 0;
}
