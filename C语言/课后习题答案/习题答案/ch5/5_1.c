/* �� 5.1
  ��д�����������������ĺ͡�����ƽ��ֵ��������������ֵ��������
*/
#include<stdio.h>
 
int main()
{
   int iA, iB, iC;
   int iSum, iPro;
  
   scanf("%d%d%d",&iA,&iB,&iC);
   iSum = iA + iB+ iC;
   iPro = iA * iB *iC; /*���ܻ����*/
 
   printf("sum = %d\nproduct=%d\n", iSum, iPro);
   printf("ave = %f\n",  iSum/3.0);

   return 0;

}
 