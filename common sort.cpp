#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<time.h>



//1.选择排序 
void select_sort (int arr[],int n)
{
	int i,j,min,temp;
	for(i=0;i<n-1;i++)
	{
		min=i;                        //min纪录最小值的位置，先假设为第一个 
		for(j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
			   min=j;                //遍历，如果后面的值小就更新min的位置 
		}
		if(min!=i)
		{
		temp=arr[i]	;
		arr[i]=arr[min];
		arr[min]=temp;                //交换
		}
	}
}


//2.归并排序 
//归并排序函数 
void merge (int arr[],int tempArr[],int left, int mid, int right) 
{
	int l_pos = left;                               //标记左半区第一个未排序的元素 
	int r_pos = mid+1;                              //标记右半区第一个未排序的元素
	int pos = left;                                 //临时数组元素的下标
	//比较左右序列第一个元素的大小进行合并
	while (l_pos<=mid && r_pos<=right) 
	{
		if(arr[l_pos]<arr[r_pos])
		   tempArr[pos++]=arr[l_pos++];              //左半区第一个元素小 就赋值给临时数组 
		else
		   tempArr[pos++]=arr[r_pos++];
	}
	//合并左半区剩余元素
	 while(l_pos<=mid)
	 {
	 	tempArr[pos++]=arr[l_pos++];
	 }
	 
	 //合并右半区剩余元素
	 while(r_pos<=right)
	 {
	 	tempArr[pos++]=arr[r_pos++];
	 }
	 
	 // 把临时数组中合并后的元素复制回原来的数组
    while (left <= right)
    {
        arr[left] = tempArr[left];
        left++;
    }
}

//归并排序
void msort(int arr[],int tempArr[],int left,int right)
{
	 
	if (left<right)                                  //如果只有一个元素，那么不需要继续划分；只有一个元素的区域，本生就是有序的，只需要被归并即可           
	{
		int mid = (left+right)/2;
		//递归划分左半区和右半区 
		msort(arr,tempArr,left,mid);
		msort(arr,tempArr,mid+1,right);
		//合并左右两个有序序列 
		merge(arr,tempArr,left,mid,right); 		
	}	
}

//归并排序入口
void merge_sort(int arr[],int n) 
{
	
	
	int *tempArr = (int *)malloc(n * sizeof(int));   //分配辅助数组
	if(tempArr)
	{
		msort(arr,tempArr,0,n-1);
		free(tempArr);
	}
	else{
		printf("error:failed to allocate ");
	}
		 	
}

//3.快速排序
void quicksort(int arr[],int p,int r)
{
	int i,j,x,temp;
	x = arr[r];  //设置最后一个元素为主元，基准元素
	i = p-1;
	
	//j用来遍历比较大小 
	//p到i放小于主元的值
	//i+1到j-1是大于主元的值 	
	if(p<r)
	{
		for(j=p;j<r;j++)
	    {	
		   //如果当前元素小，则需要要交换位置，否则不用 
		   if(arr[j]<=x)
		   {	
			   i=i+1;
			   //交换arr[i]和arr[j] 
			   temp = arr[i];
			   arr[i] = arr[j];
			   arr[j] = temp; 	
		   }
	    }   
	    //遍历结束，确定主元的最终位置，交换arr[i+1]与主元
	    temp = arr[i+1];
	    arr[i+1] = arr[r];
	    arr[r] = temp; 	
	}
	else{
		return ;
	}
	
    //再递归左右两个序列 
	quicksort(arr,p,i);
	quicksort(arr,i+2,r);		
}


//4.希尔排序 
void Shellsort(int *arr,int n)
{
	int gap,i,j,temp,flag;
	//外循环以不同的gap值对形成的序列进行排序，直到gap=1 
	for(gap=n/2;gap>=1;gap=gap/2)
	{
		//对各个子序列进行冒泡排序 
		do{
			flag = 0; 
			for(i=0; i<n-gap; i++)
		    {
	           j = i+gap;
			   if(arr[i]>arr[j])
			   {
				  temp = arr[i];
				  arr[i] = arr[j];
				  arr[j] = temp;
				  flag = 1;
			   }	
		    }		
		}while(flag);
	}	
}


//5.基数排序--借助桶 
void radixsort(int *arr,int n)
{
	int num,max ;          	
	//int temp[n];  //当数据规模大时 不能生成数组，要用malloc分配内存空间 
	int* temp = (int*)malloc(sizeof(int)*n);
	//找出数组中的最大值
	max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max){
			max = arr[i];
		}
	}			
	//从个位开始，循环次数为最大数的位数 
	for(int base=1;max/base >0;base *= 10) 
	{
		int bucket[10] = {0};     //桶初始值附0
		//统计桶编号对应的数据个数 
		for(int i=0;i<n;i++) 
		{
			//取个位十位百位...上的数字,也是桶编号 
			num = arr[i]/base%10;
			bucket[num]++;		
		}	
		//累加,最后桶的值代表数据排第几 
		for(int i=1;i<10;i++){
			bucket[i]=bucket[i-1]+bucket[i];
		}	
		//从后往前放到临时数组
		for(int i=n-1;i>=0;i--)
		{
			int k ;                 
			num = arr[i]/base%10;
			//数据放的位置，即临时数组下标 
			k = bucket[num]-1;        
			temp[k] = arr[i];
			bucket[num]--;	
		} 	
	    //把第一遍排序结果拷贝回原数组 
		for (int i = 0; i < n; i++){
			arr[i] = temp[i];
		}
	}
	free(temp);		
}




//生成指定长度的随机数组 
int* random_arr(int n,int max)

{ 
  int i,*a;

  a=(int*)malloc(n*sizeof(n));

  srand(time(0));               //用当前时间来设定rand函数所用的随机数产生演算法的种子值

  for(i=0; i<n; i++)
    a[i]=rand()%(max+1);       //随机生成1到max之间的数 

  return a;
}

//辅助函数：打印数组

void print_arr(int arr[],int n) 
{
	for (int i=0;i<n;i++)
	    printf("%d ",arr[i]);
	putchar('\n');
}


//计时，随机实验10次的平均运行时间
void time_use(int n) 
{
	int *arr, max=1000000;
	clock_t start,end;     //函数原型clock_t clock(void)
	double time_use=0;
	
	//1.选择排序计时 
	if(n<1000000){
		for(int i=0;i<10;i++)
	   {
		//生成随机数组 
		arr = random_arr(n, max);
	    //开始时间 
	    start=clock();
	    //排序 
	    select_sort (arr,n);
	    //结束时间 
	    end=clock();
	    //用时 
	    time_use += (double)(end-start);		
 	   }
	    //平均时间 
	    time_use = time_use/10; 
	    printf("选择排序t1= %.2f ms\n",time_use);	
	}
	else{
		printf("选择排序t1= ---\n");
	}
	
	
	//2.归并排序计时 
	time_use = 0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    merge_sort (arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("归并排序t2= %.2f ms\n",time_use/10);
	
	//3.快速排序计时 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    quicksort (arr,0,n-1);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("快速排序t3= %.2f ms\n",time_use/10);
	
	//4.希尔排序计时 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    Shellsort(arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("希尔排序t4= %.2f ms\n",time_use/10);
	
	//5.基数排序计时 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    radixsort (arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("基数排序t5= %.2f ms\n",time_use/10);
	putchar('\n');
			
}
 

int main(){
//	printf("输入规模n=100,平均运行时间\n");
//	time_use(100);
	printf("输入规模n=1000,平均运行时间\n");
	time_use(1000);
	printf("输入规模n=10000,平均运行时间\n");
	time_use(10000);
	printf("输入规模n=100000,平均运行时间\n");
	time_use(100000);
//	printf("输入规模n=200000,平均运行时间\n");
//	time_use(200000);
	printf("输入规模n=1000000,平均运行时间\n");
	time_use(1000000);

}
