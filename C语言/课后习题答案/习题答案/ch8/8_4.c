/* 8_4
�õ����ķ������Fibonacci  �е�ǰ20�ÿ�����8������
 fn = fn-1 + fn-2	( n >= 2 )
 f0=0, f1=1
*/
# include <stdio.h>
int main ( )
{  
    int a1 =1,a2=1, i=1;
	 
	printf("%5d %5d\n",a1,a2);

  for(i=1; i<10; i++)
	{	
		a1=a1+a2;
		a2=a2+a1;
		printf("%5d %5d ",a1,a2);

        if(i%4==0) 
			printf("\n");		
	}
    
    
    return 0;
}

 