
#include<stdio.h>
void main()
{
	int n,i=2;
	printf("please input a number:\n");
	scanf("%d",&n);
		printf("%d=",n);
			while(i!=n)
			{
				if(n%i==0)					//�ҵ����Ӳ����
				{
					printf("%d*",i);
					n=n/i;
				}
				else i++;
			}
		
				printf("%d\n",n);

}
