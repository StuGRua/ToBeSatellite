
4
#include <stdio.h>
#include <stdlib.h>
int main ()
{
	unsigned int a, i;
	int a1, a2, a3;
	float ave;
	float *p;
	printf("��������\n");
	scanf("%d",&a);
	p = (float*)malloc(a*sizeof(float));
	for (i = 0, ave = 0; i < a; i ++)
	{
		printf("�����%d���˵ĳɼ�\n",i);
		scanf("%d%d%d",&a1,&a2,&a3);
		ave = (float)((a1 + a2 + a3)/3.0);
		p[i] = ave;
	}
	for (i = 0; i < a; i ++)
		printf("��%d���˵ĳɼ�%f",p[i]);
	return 0;
}
