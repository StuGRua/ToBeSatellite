#include <stdio.h>

int main()
{ 
 int a[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
 int b[20][2];
 int i,j,k;
 j = 0;
 k = 0;
 for(i=0; i<20; i++)
 {
  if(a[i]%2==0)  /*�����ż��������ڵ�0��*/
   b[j++][0] = a[i];
  else               /*���������������ڵ�1��*/
   b[k++][1] = a[i];
 }
   for(i=0; i<10; i++)
 printf("%d  ",b[i][0]);

   printf("\n");

for(i=0; i<10; i++)
 printf("%d  ",b[i][1]);

    printf("\n");
 return 0;
}