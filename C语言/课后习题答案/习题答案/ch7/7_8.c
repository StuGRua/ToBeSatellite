/*7_8
��д�����ж������Ƿ���Ч���û������������ݣ��ꡢ�º��գ��������Ӧ�жϽ����
*/#include <stdio.h>
void main( ) 
{   
   int Month, Day, Year;
   int DaysInMonth;   /*ÿ���������*/
   	int DaysInFebruary; 
   printf( "Please supply a date (yyyy mm dd ): ");
   scanf("%d%d%d", & Year, &Month,&Day ) ;      
	  
   if(Year<0)
   {
	   printf("Invalid year!\n");
	   return 0;
   }
   else /*����ÿ������*/
   {
	  
	  switch (Month)
	  {
        case 1:  case 3:  case 5:  case 7:
		case 8:  case 10: case 12: 
			DaysInMonth = 31;
            break;

		 case 4: case 6: case 9: case 11:
			DaysInMonth = 30;	
            break;

		case 2:
			DaysInMonth =  28; 
            break;
		default:
		    printf("Invalid month\n");
			return;
	  }

	  /*����2�µ�����*/
	  if(Month==2 && Day>28)
	  {
		
		if ((Year % 4) != 0)  
			DaysInMonth = 28;
		else if ((Year % 400) == 0) 
			DaysInMonth= 29;
		else if ((Year % 100) == 0)  
			DaysInMonth = 28;
		else 
			DaysInMonth = 29; 
	  }

	  /*�ж������յ���Ч��*/ 
	 if ((Day < 1) || (Day > DaysInMonth)) 
	 {
		  printf( "Invalid day of day\n");
	 }
     else
     {
		printf("%d/%d/%d", Month , Day , Year);	

	 }
   }
}

