#include<stdio.h>
#include<math.h>
float distance(float x1,float y1,float x2,float y2)
{
	float l;
	l=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return l;


}
int main()
{
	float a,b,c,d,l;
	printf("�����������꣺");
	scanf("%f,%f,%f,%f",&a,&b,&c,&d);
	l=distance(a,b,c,d);
	printf("�������Ϊ%f",l);
	return 0;


}