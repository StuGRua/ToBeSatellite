#include<stdio.h>
#define N 10
#define M 3
int main()
{
    int  a[N]={1,2,3,4,5,6,7,8,9,10};
	int i,temp;
	int b[3];
	/*���ߺ�M����b��*/
	for(i=0;i<M;i++)
	  b[i]=a[N-M]+i;
	/*ǰ��N-M��ƽ��*/
	for(i=N-M-1;i>=0;i--)
	  a[i+M]=a[i];
     /*b��M���Ƶ�a��*/
	for(i=0;i<M;i++)
	  a[i]=b[i];
    for(i=0;i<10;i++)
		printf("%d ",a[i]);
    return 0;
}
 