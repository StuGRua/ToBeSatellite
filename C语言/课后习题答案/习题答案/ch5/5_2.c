/*5.2
��д������Բ��������ܳ���Բ����ı�����������
Ҫ������Բ���ĵ���ֱ���͸ߣ������������ȡС�����2λ���֡�
*/
#include<stdio.h>
#define PI 3.1415926
int main()
{
	double dDiameter,dHeight;			/*ֱ������*/
	double dCircleGirth ,dCircleArea ;	/*Բ�ܳ������*/
    double fColumnArea = 0;			    /*Բ�������*/
	
	/*��������*/
	printf("������Բ�������뾶�͸ߣ�");
	scanf("%lf %lf",&dDiameter,&dHeight);
	
	/*�������*/
	dCircleGirth = 2 * PI * (dDiameter/2);			
	dCircleArea = PI * (dDiameter/2) * (dDiameter/2);
	fColumnArea = 2 * dCircleArea + dCircleGirth * dHeight;
	
	/*������*/
	printf("Բ���������ܳ�Ϊ%.2f\n",dCircleGirth);
	printf("Բ��������Ϊ%.2f\n",fColumnArea);
	printf("Բ�������Ϊ%.2f\n",dCircleArea * dHeight);

}
