#include<stdio.h>
int main()
{
   int a[10],i,sum=0;
   float aver;
   /*����Ԫ��*/
   for(i=0;i<10;i++)
	   scanf("%d",&a[i]);
   /*����ƽ��ֵ*/
   for(i=0;i<10;i++)
	   sum=sum+a[i];
   aver=sum/10.0;
   /*�������*/
   sum=0;
   for(i=0;i<10;i++)
	   if(a[i]>=aver)
		   sum++;
   printf("sum = %d", sum);
   return 0;
}