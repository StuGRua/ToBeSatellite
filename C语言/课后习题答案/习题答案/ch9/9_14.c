#include <stdio.h>
#define N 3
int x,y,exist=0;
int isrmax(int a[N][N])
{
int i;
for(i=0;i<N;i++)
if(a[x][y]<a[x][i])
return 0;
return 1;
}

int iscmin(int a[N][N])
{
int i;
for(i=0;i<N;i++)
if(a[x][y]>a[i][y])
return 0;
return 1;
}

void scanarray(int a[N][N])
{
int i,j;
for(i=0;i<N;i++)
{
printf("��%d�У�",i+1);
for(j=0;j<N;j++)
scanf("%d",&a[i][j]);
}
printf("\n");
}

void printarray(int a[N][N])
{
int i,j;
for(i=0;i<N;i++)
{
for(j=0;j<N;j++)
printf("%5d",a[i][j]);
printf("\n");
}
}

main()
{
int a[N][N];
printf("�����������Ԫ�ص�ֵ��\n");
scanarray(a);
printf("�����������Ϊ��\n");
printarray(a);
for(x=0;x<N;x++)
for(y=0;y<N;y++)
if(isrmax(a)&&iscmin(a))
{
printf("���㣺%d����%d�У���%d�С�\n",a[x][y],x+1,y+1);
exist=1;
}
if(!exist)
printf("�����в����ڰ��㣡\n");
}