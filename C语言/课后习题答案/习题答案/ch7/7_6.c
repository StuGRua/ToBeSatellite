/*7-6��
   ���һ�������ƶ������ε����������
*/
#include <stdio.h>
#include <math.h>
int main() 
{
     float fa, fb,fc,fArea,fs,ft;
	printf( "����������\n") ;     
     scanf("%f%f%f",&fa,&fb ,&fc );
	 if(fa<fb)
	{   ft=fa;	fa=fb;	fb=ft;	}  
    
	if(fa<fc)
    {  	ft=fa;	fa=fc;	fc=ft;	}      
   
    if(fb<fc)
   {   	ft=fb;	fb=fc;	fc=ft;    }  
	
	printf("%f,%f,%f\n", fa, fb,fc);

	if(fa==fb && fb==fc)
	{
		printf("�ȱ�������");
		fArea = sqrt(3)*fa*fa/2;
	}
	else if( fa*fa==fb*fb+fc*fc)
	{
		printf("ֱ��������");
		fArea = fb*fc/2;
	}
	else
	{
		printf("�����ַ�������");
		fs = (fa+fb+fc)/2;
	   fArea = sqrt((fs)*(fs-fa)*(fs-fb)*(fs-fc));
	}
	printf("\n���Ϊ%f\n",fArea);
	return 0;
}