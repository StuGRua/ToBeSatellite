/*5.3
��д����ʵ�ֻ����¶Ⱥ������¶ȵ�ת��������һ�������¶�F��Ҫ����������¶�C��
������Ҫ������˵����ȡС�����4λ���֡�ת����ʽΪ��c=5����F-32��/9 
*/
#include<stdio.h>
 
int main()
{
	float dCentigrade,dFahrenheit;/*�����¶ȣ������¶�*/	
 
	printf("�����뻪���¶�F��");
	scanf("%f",&dFahrenheit);
	
	dCentigrade = 5*(dFahrenheit-32)/9;

	printf("�����¶�Ϊ%.4f\n",dCentigrade);
 

}
