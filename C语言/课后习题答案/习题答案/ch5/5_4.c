/*5.4
  ����һ��Сд��ĸ�������Ӧ�Ĵ�д��ĸ��
*/
#include<stdio.h>
 
int main()
{
	char c;
 
	printf("����������һ��Сд��ĸ��");
	scanf("%c",&c);
    if(c>='a' &&c<='z')
	   printf("��Ӧ�Ĵ�д��ĸΪ%c\n",c-32); 

}