#include <stdio.h>
int main() 
{
	char c;
	scanf("%c",&c);
	if(c>=48 && c<=57) 
		printf("�����ַ�");
	else if(c>=65 && c<=90) 
		printf("��д��ĸ�ַ�");
	else if(c>=97 && c<=122) 
		printf("Сд��ĸ�ַ�");
	else
		printf("�����ַ�");
    return 0;
}