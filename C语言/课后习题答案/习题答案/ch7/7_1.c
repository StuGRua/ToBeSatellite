 /* 7_1
   �Ӽ���������������������С�����˳�����*/
#include<stdio.h>
void main()
{
     int a,b,c,t ;
     scanf("%d,%d,%d",&a,&b,&c);
	 
	 if(a>b)
	{   /* ʵ��a��b�Ļ��� */
		t=a;
		a=b;
		b=t;
	}  
    
	if(a>c)
    {  /* ʵ��a��c�Ļ��� */
		t=a;
		a=c;
		c=t;
	}      
   
    if(b>c)
   {   /* ʵ��b��c�Ļ��� */
		t=b;
		b=c;
		c=t;
    }     
   printf("%d,%d,%d\n", a, b,c);

   /*����2*/
	if( a < b )
	{    
		if  ( b < c )
			printf("%d,%d,%d\n", a, b,c);
    else  if  ( a< c )  
			printf("%d,%d,%d\n", a, c,b);
    else 
			printf("%d,%d,%d\n", c, a,b);
	}
	// a>=b
   else if  ( a < c )  
        printf("%d,%d,%d\n",  b,a,c); 
   else  if  ( b < c )  
		printf("%d,%d,%d\n",  b,c,a);
   else  
	    printf("%d,%d,%d\n", c,b,a );
     
}