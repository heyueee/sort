#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<time.h>



//1.ѡ������ 
void select_sort (int arr[],int n)
{
	int i,j,min,temp;
	for(i=0;i<n-1;i++)
	{
		min=i;                        //min��¼��Сֵ��λ�ã��ȼ���Ϊ��һ�� 
		for(j=i+1;j<n;j++)
		{
			if(arr[j]<arr[min])
			   min=j;                //��������������ֵС�͸���min��λ�� 
		}
		if(min!=i)
		{
		temp=arr[i]	;
		arr[i]=arr[min];
		arr[min]=temp;                //����
		}
	}
}


//2.�鲢���� 
//�鲢������ 
void merge (int arr[],int tempArr[],int left, int mid, int right) 
{
	int l_pos = left;                               //����������һ��δ�����Ԫ�� 
	int r_pos = mid+1;                              //����Ұ�����һ��δ�����Ԫ��
	int pos = left;                                 //��ʱ����Ԫ�ص��±�
	//�Ƚ��������е�һ��Ԫ�صĴ�С���кϲ�
	while (l_pos<=mid && r_pos<=right) 
	{
		if(arr[l_pos]<arr[r_pos])
		   tempArr[pos++]=arr[l_pos++];              //�������һ��Ԫ��С �͸�ֵ����ʱ���� 
		else
		   tempArr[pos++]=arr[r_pos++];
	}
	//�ϲ������ʣ��Ԫ��
	 while(l_pos<=mid)
	 {
	 	tempArr[pos++]=arr[l_pos++];
	 }
	 
	 //�ϲ��Ұ���ʣ��Ԫ��
	 while(r_pos<=right)
	 {
	 	tempArr[pos++]=arr[r_pos++];
	 }
	 
	 // ����ʱ�����кϲ����Ԫ�ظ��ƻ�ԭ��������
    while (left <= right)
    {
        arr[left] = tempArr[left];
        left++;
    }
}

//�鲢����
void msort(int arr[],int tempArr[],int left,int right)
{
	 
	if (left<right)                                  //���ֻ��һ��Ԫ�أ���ô����Ҫ�������֣�ֻ��һ��Ԫ�ص����򣬱�����������ģ�ֻ��Ҫ���鲢����           
	{
		int mid = (left+right)/2;
		//�ݹ黮����������Ұ��� 
		msort(arr,tempArr,left,mid);
		msort(arr,tempArr,mid+1,right);
		//�ϲ����������������� 
		merge(arr,tempArr,left,mid,right); 		
	}	
}

//�鲢�������
void merge_sort(int arr[],int n) 
{
	
	
	int *tempArr = (int *)malloc(n * sizeof(int));   //���丨������
	if(tempArr)
	{
		msort(arr,tempArr,0,n-1);
		free(tempArr);
	}
	else{
		printf("error:failed to allocate ");
	}
		 	
}

//3.��������
void quicksort(int arr[],int p,int r)
{
	int i,j,x,temp;
	x = arr[r];  //�������һ��Ԫ��Ϊ��Ԫ����׼Ԫ��
	i = p-1;
	
	//j���������Ƚϴ�С 
	//p��i��С����Ԫ��ֵ
	//i+1��j-1�Ǵ�����Ԫ��ֵ 	
	if(p<r)
	{
		for(j=p;j<r;j++)
	    {	
		   //�����ǰԪ��С������ҪҪ����λ�ã������� 
		   if(arr[j]<=x)
		   {	
			   i=i+1;
			   //����arr[i]��arr[j] 
			   temp = arr[i];
			   arr[i] = arr[j];
			   arr[j] = temp; 	
		   }
	    }   
	    //����������ȷ����Ԫ������λ�ã�����arr[i+1]����Ԫ
	    temp = arr[i+1];
	    arr[i+1] = arr[r];
	    arr[r] = temp; 	
	}
	else{
		return ;
	}
	
    //�ٵݹ������������� 
	quicksort(arr,p,i);
	quicksort(arr,i+2,r);		
}


//4.ϣ������ 
void Shellsort(int *arr,int n)
{
	int gap,i,j,temp,flag;
	//��ѭ���Բ�ͬ��gapֵ���γɵ����н�������ֱ��gap=1 
	for(gap=n/2;gap>=1;gap=gap/2)
	{
		//�Ը��������н���ð������ 
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


//5.��������--����Ͱ 
void radixsort(int *arr,int n)
{
	int num,max ;          	
	//int temp[n];  //�����ݹ�ģ��ʱ �����������飬Ҫ��malloc�����ڴ�ռ� 
	int* temp = (int*)malloc(sizeof(int)*n);
	//�ҳ������е����ֵ
	max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i] > max){
			max = arr[i];
		}
	}			
	//�Ӹ�λ��ʼ��ѭ������Ϊ�������λ�� 
	for(int base=1;max/base >0;base *= 10) 
	{
		int bucket[10] = {0};     //Ͱ��ʼֵ��0
		//ͳ��Ͱ��Ŷ�Ӧ�����ݸ��� 
		for(int i=0;i<n;i++) 
		{
			//ȡ��λʮλ��λ...�ϵ�����,Ҳ��Ͱ��� 
			num = arr[i]/base%10;
			bucket[num]++;		
		}	
		//�ۼ�,���Ͱ��ֵ���������ŵڼ� 
		for(int i=1;i<10;i++){
			bucket[i]=bucket[i-1]+bucket[i];
		}	
		//�Ӻ���ǰ�ŵ���ʱ����
		for(int i=n-1;i>=0;i--)
		{
			int k ;                 
			num = arr[i]/base%10;
			//���ݷŵ�λ�ã�����ʱ�����±� 
			k = bucket[num]-1;        
			temp[k] = arr[i];
			bucket[num]--;	
		} 	
	    //�ѵ�һ��������������ԭ���� 
		for (int i = 0; i < n; i++){
			arr[i] = temp[i];
		}
	}
	free(temp);		
}




//����ָ�����ȵ�������� 
int* random_arr(int n,int max)

{ 
  int i,*a;

  a=(int*)malloc(n*sizeof(n));

  srand(time(0));               //�õ�ǰʱ�����趨rand�������õ�������������㷨������ֵ

  for(i=0; i<n; i++)
    a[i]=rand()%(max+1);       //�������1��max֮����� 

  return a;
}

//������������ӡ����

void print_arr(int arr[],int n) 
{
	for (int i=0;i<n;i++)
	    printf("%d ",arr[i]);
	putchar('\n');
}


//��ʱ�����ʵ��10�ε�ƽ������ʱ��
void time_use(int n) 
{
	int *arr, max=1000000;
	clock_t start,end;     //����ԭ��clock_t clock(void)
	double time_use=0;
	
	//1.ѡ�������ʱ 
	if(n<1000000){
		for(int i=0;i<10;i++)
	   {
		//����������� 
		arr = random_arr(n, max);
	    //��ʼʱ�� 
	    start=clock();
	    //���� 
	    select_sort (arr,n);
	    //����ʱ�� 
	    end=clock();
	    //��ʱ 
	    time_use += (double)(end-start);		
 	   }
	    //ƽ��ʱ�� 
	    time_use = time_use/10; 
	    printf("ѡ������t1= %.2f ms\n",time_use);	
	}
	else{
		printf("ѡ������t1= ---\n");
	}
	
	
	//2.�鲢�����ʱ 
	time_use = 0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    merge_sort (arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("�鲢����t2= %.2f ms\n",time_use/10);
	
	//3.���������ʱ 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    quicksort (arr,0,n-1);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("��������t3= %.2f ms\n",time_use/10);
	
	//4.ϣ�������ʱ 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    Shellsort(arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("ϣ������t4= %.2f ms\n",time_use/10);
	
	//5.���������ʱ 
	time_use=0; 
	for(int i=0;i<10;i++)
	{
		arr = random_arr(n, max);
	    start=clock();
	    radixsort (arr,n);
	    end=clock();
	    time_use += (double)(end-start);		
	}
	printf("��������t5= %.2f ms\n",time_use/10);
	putchar('\n');
			
}
 

int main(){
//	printf("�����ģn=100,ƽ������ʱ��\n");
//	time_use(100);
	printf("�����ģn=1000,ƽ������ʱ��\n");
	time_use(1000);
	printf("�����ģn=10000,ƽ������ʱ��\n");
	time_use(10000);
	printf("�����ģn=100000,ƽ������ʱ��\n");
	time_use(100000);
//	printf("�����ģn=200000,ƽ������ʱ��\n");
//	time_use(200000);
	printf("�����ģn=1000000,ƽ������ʱ��\n");
	time_use(1000000);

}
