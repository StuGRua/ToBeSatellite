#include <stdio.h>
int main()
{
	float fHemline,fHigh,fArea;  /*�ף��ߣ����*/	 
    printf("����׺͸ߣ�\n");		/*��ʾ����*/
	scanf("%f%f",&fHemline,&fHigh) ;
	fArea=fHemline*fHigh/2; 
	printf("���Ϊ��%f\n",fArea); 
	return 0;
}