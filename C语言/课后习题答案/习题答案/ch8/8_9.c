/*8_9
��1��2��3��4�����֣�����ɶ��ٸ�������ͬ�����ظ����ֵ���λ�������Ƕ��٣�
*/
#include<stdio.h>
int main()
{
	int i,j,k,n;
	n=0;
	for(i=1;i<=4;i++)
	{
		for(j=1;j<=4;j++)
		{
			for(k=1;k<=4;k++)
			{
				if(k!=i&&k!=j&&j!=i)         //�ж������Ƿ��ظ�
				{
					printf("%d%d%d\n",i,j,k);
					n=n+1;					//������
				}
			}
		}
	}
	printf("sum=%d\n",n);
}
