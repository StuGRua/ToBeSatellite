/*��ѧ������ģ��*/
/*ɸ������*/
#include<stdio.h>
int main()
{
    /*׼�����ݿռ�*/
    int i,j,number=0,a[101];
    /*��ȡ����*/
    for(i=1;i<=100;i++)
		a[i]=i;
	/*ɸ������*/
    for(i=2;i<=50;i++)
		if(a[i]!=0)
			for(j=2;i*j<=100;j++)
			    a[i*j]=0;
    /*�������*/
    printf("���������\n");
    for(i=2;i<=100;i++)
	{
	    if(a[i]!=0)
		{
			printf("%4d",a[i]);
            number++;
		    if(number%5==0)
			    printf("\n");
		}
	}
    return 0;
}