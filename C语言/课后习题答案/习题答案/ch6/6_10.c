#include<stdio.h>

int main()
{     
	 float total,pay,unit,bonus;/*�����롢�������ʡ���ɡ�����*/
	 int number;  /*̨��*/
	 printf("����������ʣ�");
	 scanf("%f",&pay);
	 printf("\n��������̨����");
	 scanf("%d",&number);
     total=pay+1000*number+(10800*number>100000?10800*number*0.02:0);
     printf("\n�����ܶ�Ϊ��%f",total);
	 return 0;
}