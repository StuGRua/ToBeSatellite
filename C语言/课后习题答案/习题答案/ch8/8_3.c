/*8_3
 �ֱ�����ٷ��͵��������������������Լ����
�� ������������m��n����������ǵ����Լ����*/
#include <stdio.h>
int main()
{ 
   int m , n , i, min;
   int a , b , r ;
   printf("input two integers :" );	
   scanf( "%d%d", &m, &n);
  
  /*��ٷ�-���Լ��*/
	min =(m<n)?m:n;

   for( i = min; i>1 ; i-- )
	   if( m%i==0 && n%i==0 ) break;
   printf( "Greatest common divisor is %d \n", i) ;
	
 
   /*շת�����*/
   r = a % b ;	/*����*/
   
  while ( r != 0 )
  {	
     a = b ;			
     b = r ; 
	 r = a % b ;	
  }
  printf( "Greatest common divisor is %d \n", i) ;

   return 0;
}