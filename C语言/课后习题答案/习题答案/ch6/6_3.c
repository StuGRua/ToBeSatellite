/*6_3
 ��������С�����жϲ�������е����ֵ����Сֵ��
 */
#include<stdio.h>
 
int main()
{     
	  
	 float fa, fb,fc,fMin, fMax;
	 printf(" ��������С��\n") ;     
     scanf("%f%f%f",&fa,&fb ,&fc );
	 fMax = (fa>fb)?fa:fb;
	 fMax = (fMax>fc)?fMax:fc;
	 fMin = (fa<fb)?fa:fb;
	 fMin = (fMin<fc)?fMin:fc;
     
	 printf("min=:%.2f\n",fMin  );
     printf("max=:%.2f\n",fMax );
	return 0;
}

