#include<stdio.h>
#define N 8
int main()
{
    int  a[N]={3,2,-6,4,7,-3,5,-2},i,j;
    int sum;/*��ǰλ�õĺ�*/  
    int max;/*ĿǰΪֹ�����������*/  
    int left,right;/*�������λ��*/  
    int t1;/*���������ʱ��λ��*/  
    /*��ʼ��*/  
    sum=max=a[0];  
    left=right=t1=0;  
    for(i=1;i<N;i++)
	{  
        sum+=a[i];            
        if(sum<0)
		{  
             sum=0;/*�����Ϊ���ˣ���Ӧ�����¼���*/  
             t1=i+1;/*t1Ҳ����һ��λ�ÿ�ʼ*/  
             continue;  
        }  
        if(sum>max)
		{/*�����ǰ�ͱ�ԭ�ȵ����ֵ����*/  
           max=sum;/*���ֵ���ڵ�ǰֵ  */
           left=t1;/*��������ҲҪ������Ӧ��*/  
           right=i;  
        }  
    }  
    for(i=left;i<=right;i++)  
       printf("%d ",a[i]);  
    return 0;
}
 