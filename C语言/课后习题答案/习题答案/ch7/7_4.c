  /*��������˷�*/ 
   #include <stdio.h>
  
   void main()
   { 
     double  dFreight;           /*���˷�t*/ 
     double  dPrice ;           /*�˷ѵ���p*/ 
     double  dWeight =100 ;     /*��������w*/ 
     double  dDistance =100;   /*���˾���s*/ 
 
	 printf( "Please input weight( ton ) an distsnce( kilometre )  : " );
      scanf( "%f,%f",&dWeight ,&dDistance );

    if ( dDistance < 100 )       /*s<100*/
    {
  	   dPrice = 30 ;
    } 
    else if ( dDistance < 200 )  /*100<=s<200*/
   {
 		 dPrice = 27.5 ;
   }
 	else if ( dDistance < 300 )  /*200<=s<300*/
   {
  	dPrice = 25 ;
   }
   else if ( dDistance < 400 )  /*300<=s<400*/
  {
  	 dPrice = 22.5 ;
   }
   else                         /*s>=100*/
   {
	 	dPrice = 20 ;
   }

   dFreight = dPrice * dWeight * dDistance ;        /*�����˷�*/ 
   printf("���˷�Ϊ%7.2f$ \n",dFreight) ;               /*�����ҵ�λ����ʽ���*/ 

 }
