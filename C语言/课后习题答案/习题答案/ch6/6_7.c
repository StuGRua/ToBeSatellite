/*6_7
 ���������ε����߳��������������ǵ����Ǻ���
 */
#include<stdio.h>
#include<math.h>
int main()
{     
	  
	 float fa, fb,fc,fSin, fCos, fMax;
	 printf( "����������\n") ;     
     scanf("%f%f%f",&fa,&fb ,&fc );
	 fMax = (fa>fb)?fa:fb;
	 fMax = (fMax>fc)?fMax:fc;
	 if(fMax>=fa+fb+fc-fMax)
	 {
		 printf("Error\n");
		 return 1;
	 }
     fCos = (fa*fa + fb*fb +fc*fc - 2*fMax*fMax)*fMax/(2*fa*fb*fc);
	 printf("cos=:%.2f\n",fCos );
     printf("sin=:%.2f\n",sqrt(1- fCos* fCos));
	return 0;
}

