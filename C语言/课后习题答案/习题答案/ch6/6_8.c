/*6_8
 ��д����Ԥ��ϵ�������¶ȡ�
 ������ʾ�û�����ʱ�䣬��������Сʱ�ͷ��ӱ�ʾ��
 ��Ҫ����ת��Ϊ�����͵�Сʱ���������ʱ���¶�ֵ��С�����2λ��Ч���֣���
 */
#include<stdio.h>

int main()
{     
	 int iHour, iMinute, iSecond ;
	 double dTime,dTempreature;
	 printf( "�ϵ�ʱ�䣨ʱ,��,��\n") ;     
     scanf("%d,%d,%d",&iHour,&iMinute ,&iSecond );
	 dTime =  iHour+iMinute/60.0 + iSecond/3600.0;

	 dTempreature = 4*dTime*dTime/(dTime+2)-20;
	 if( dTempreature>30)  /*��������Ϊ30��*/
		dTempreature=30;
	 printf("�����¶�Ϊ:%.2f\n",dTempreature);

	return 0;
}

