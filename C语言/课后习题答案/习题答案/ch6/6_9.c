/*6_9
 ��̼���������ƽ���ٶ� */
#include<stdio.h>

int main()
{     
	 int iStartPost,iEndPost;
	 int iStartHour, iStarMinute, iStarSecond ;
	 int iEndHour, iEndMinute, iEndSecond ;
	 int iElapsedTS,iElapsedHour,iElapsedMinute,iElapsedSecond ;
	 double dElapsedTime,dVelocity;

	 printf( "������������Ϊ����\n" 
			 "��ʼ��̣�\n");     
   scanf("%d",&iStartPost) ;
   printf( "��ʼʱ�䣨ʱ���֣��룩��\n") ;     
   scanf("%d:%d:%d",&iStartHour,&iStarMinute ,&iStarSecond );
     
	 printf( "������̣�\n" );
     scanf("%d",&iEndPost);
     printf("����ʱ�䣨ʱ���֣��룩��\n") ;   
	 scanf("%d:%d:%d",&iEndHour,&iEndMinute ,&iEndSecond) ;
    
	 /*������ʻʱ�䣨�룩*/
	iElapsedTS = ( iEndHour * 3600 + iEndMinute * 60 + iEndSecond )
		 - ( iStartHour * 3600 + iStarMinute * 60 + iStarSecond ) ;
	/*ת����Сʱ/����/��*/ 
	iElapsedHour = iElapsedTS / 3600 ;
	iElapsedMinute = iElapsedTS % 3600 / 60 ;
	iElapsedSecond = iElapsedTS % 60 ;
    /* ת����Сʱ(С��)*/
	dElapsedTime = iElapsedHour + iElapsedMinute / 60.0 
		               + iElapsedSecond / 3600.0 ;
	/*����ƽ���ٶȣ�����/Сʱ��*/  
	dVelocity = (iEndPost - iStartPost) / dElapsedTime ;

   	printf( "������ʻ��%d����\n" ,iEndPost - iStartPost);
    printf( "����ʱ��%dСʱ%d��%d��,ƽ���ٶ�:%f����/Сʱ\n " ,
		     iElapsedHour,iElapsedMinute ,iElapsedSecond,dVelocity);

	return 0;
}

